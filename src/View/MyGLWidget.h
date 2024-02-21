#ifndef SRC_VIEW_viewer_MYGLWIDGET_H_
#define SRC_VIEW_viewer_MYGLWIDGET_H_

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QSettings>
#include <iostream>

#include "../Model/OffsetScene.h"
#include "Setting.h"
#include "View.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  MyGLWidget(QWidget *parent = nullptr);
  ~MyGLWidget() = default;

  void SetDrawData(const std::vector<double> &vertices,
                   const std::vector<unsigned int> &lines);

  void SetVertexColor(QColor color);
  void SetEdgeColor(QColor color);
  void SetCanvaBGColor(QColor color);

  void SetVertexSize(double size);
  double GetVertexSize();
  void SetEdgeSize(double size);
  double GetEdgeSize();

  void SetVertexType(viewer::VertexSetting::VertexType type);
  viewer::VertexSetting::VertexType GetVertexType();
  void SetEdgeType(viewer::EdgeSetting::EdgeType type);
  viewer::EdgeSetting::EdgeType GetEdgeType();
  void SetCanvaProjection(viewer::CanvaSetting::ProjectionType type);
  viewer::CanvaSetting::ProjectionType GetCanvaProjection();

  void SaveSettings();
  void LoadSettings();
  void SetDefaultSettings();

  void reDraw();

 protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

 private:
  void PaintVertex();
  void PaintEdges();
  void UpdateCanva();
  const std::vector<double> *vertices_;
  const std::vector<unsigned int> *edges_;
  viewer::VertexSetting vertex_opt_;
  viewer::EdgeSetting edge_opt_;
  viewer::CanvaSetting canva_opt_;
};

#endif  // SRC_VIEW_viewer_MYGLWIDGET_H_
