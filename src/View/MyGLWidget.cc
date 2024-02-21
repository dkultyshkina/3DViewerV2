#include "MyGLWidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      vertices_(),
      edges_(),
      vertex_opt_(),
      edge_opt_(),
      canva_opt_() {
  SetDefaultSettings();
}

void MyGLWidget::SetDrawData(const std::vector<double> &vertices,
                             const std::vector<unsigned int> &lines) {
  vertices_ = &vertices;
  edges_ = &lines;
}

void MyGLWidget::SetVertexColor(QColor color) { vertex_opt_.SetColor(color); }

void MyGLWidget::SetEdgeColor(QColor color) { edge_opt_.SetColor(color); }

void MyGLWidget::SetCanvaBGColor(QColor color) { canva_opt_.SetBGColor(color); }

void MyGLWidget::SetVertexSize(double size) { vertex_opt_.SetSize(size); }

double MyGLWidget::GetVertexSize() { return vertex_opt_.GetSize(); }

void MyGLWidget::SetEdgeSize(double size) { edge_opt_.SetSize(size); }

double MyGLWidget::GetEdgeSize() { return edge_opt_.GetSize(); }

void MyGLWidget::SetVertexType(viewer::VertexSetting::VertexType type) {
  vertex_opt_.SetType(type);
}

viewer::VertexSetting::VertexType MyGLWidget::GetVertexType() {
  return vertex_opt_.GetType();
}

void MyGLWidget::SetEdgeType(viewer::EdgeSetting::EdgeType type) {
  edge_opt_.SetType(type);
}

viewer::EdgeSetting::EdgeType MyGLWidget::GetEdgeType() {
  return edge_opt_.GetType();
}

void MyGLWidget::SetCanvaProjection(viewer::CanvaSetting::ProjectionType type) {
  canva_opt_.SetProjectionType(type);
}

viewer::CanvaSetting::ProjectionType MyGLWidget::GetCanvaProjection() {
  return canva_opt_.GetProjectionType();
}

void MyGLWidget::SaveSettings() {
  QSettings settings("viewer", "3DViewerV2");
  settings.setValue("test_value", 1);

  vertex_opt_.SaveSettings(settings);
  edge_opt_.SaveSettings(settings);
  canva_opt_.SaveSettings(settings);
}

void MyGLWidget::LoadSettings() {
  QSettings settings("viewer", "3DViewerV2");

  // Проверка на существование настроек
  if (settings.value("test_value").toInt() == 1) {
    vertex_opt_.LoadSettings(settings);
    edge_opt_.LoadSettings(settings);
    canva_opt_.LoadSettings(settings);
  }
}

void MyGLWidget::SetDefaultSettings() {
  vertex_opt_.SetDefaultSettings();
  edge_opt_.SetDefaultSettings();
  canva_opt_.SetDefaultSettings();
}

void MyGLWidget::reDraw() {
  //  paintGL();
  update();
}

void MyGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  QColor bg_color = canva_opt_.GetBGColor();
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(), 1.0f);
}

void MyGLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
}

void MyGLWidget::paintGL() {
  // Установка цвета очистки
  QColor bg_color = canva_opt_.GetBGColor();
  glClearColor(bg_color.redF(), bg_color.greenF(), bg_color.blueF(), 1.0f);
  // Очистка буфера текущим цветом очистки
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Настройка параметров проекции
  double left = -2.0;
  double right = 2.0;
  double bottom = -2.0;
  double top = 2.0;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Параметры проекции, зависящие от типа и положения камеры
  if (canva_opt_.GetProjectionType() ==
      viewer::CanvaSetting::ProjectionType::kParalel) {
    glOrtho(left, right, bottom, top, 5.0, 12.0);
    glTranslatef(0, 0, -10.0);
  } else if (canva_opt_.GetProjectionType() ==
             viewer::CanvaSetting::ProjectionType::kCentral) {
    double near = 40.0;
    double far = 100.0;

    glFrustum(left, right, bottom, top, near, far);
    glTranslatef(0, 0, -50.f);  // Смещение камеры
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  PaintVertex();
  PaintEdges();

  // std::cerr << "(MYWIDGET) Redraw "
  //           << ((vertices_ == nullptr) ? 0.0 : (*vertices_)[0]) << std::endl;
}

void MyGLWidget::PaintEdges() {
  glEnableClientState(GL_VERTEX_ARRAY);

  // Устновка размера отрисовываемой линии
  glLineWidth(edge_opt_.GetSize());

  if (edge_opt_.GetType() == viewer::EdgeSetting::EdgeType::kSolid) {
    glDisable(GL_LINE_STIPPLE);
  } else if (edge_opt_.GetType() == viewer::EdgeSetting::EdgeType::kDotted) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
  }

  if (edges_ != nullptr) {
    // Установка цвета рисования границ
    QColor edge_color = edge_opt_.GetColor();
    glColor3d(edge_color.redF(), edge_color.greenF(), edge_color.blueF());
    // Отрисовка границ
    glDrawElements(GL_LINES, edges_->size(), GL_UNSIGNED_INT, edges_->data());
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyGLWidget::PaintVertex() {
  glEnableClientState(GL_VERTEX_ARRAY);

  if (vertex_opt_.GetType() == viewer::VertexSetting::VertexType::kNone) {
    glPointSize(0.00001);
  } else {
    glPointSize(vertex_opt_.GetSize());
  }

  if (vertex_opt_.GetType() == viewer::VertexSetting::VertexType::kRounded) {
    glEnable(GL_POINT_SMOOTH);
  } else if (vertex_opt_.GetType() ==
             viewer::VertexSetting::VertexType::kSquare) {
    glDisable(GL_POINT_SMOOTH);
  }

  if (vertices_ != nullptr) {
    // Установка цвета рисования вершин
    QColor vertex_color = vertex_opt_.GetColor();
    glColor3d(vertex_color.redF(), vertex_color.greenF(), vertex_color.blueF());
    // Указание OpenGL на массив вершин
    glVertexPointer(3, GL_DOUBLE, 0, vertices_->data());
    // Отрисовка вершин
    glDrawArrays(GL_POINTS, 0, vertices_->size() / 3);
    glFlush();
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyGLWidget::UpdateCanva() {}
