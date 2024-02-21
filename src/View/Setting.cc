#include "Setting.h"

namespace viewer {

VertexSetting::VertexSetting(VertexType type, double size, QColor color)
    : type_vertex_(type), size_(size), color_(color) {}

void VertexSetting::SaveSettings(QSettings& instance) {
  instance.setValue("vertex_type", static_cast<int>(type_vertex_));

  instance.setValue("vertex_size", size_);

  instance.setValue("vertex_color_red", color_.redF());
  instance.setValue("vertex_color_green", color_.greenF());
  instance.setValue("vertex_color_blue", color_.blueF());
}

void VertexSetting::LoadSettings(QSettings& instance) {
  SetType(VertexType(instance.value("vertex_type").toInt()));
  SetSize(instance.value("vertex_size").toDouble());

  QColor load_color;
  load_color.setRedF(instance.value("vertex_color_red").toFloat());
  load_color.setGreenF(instance.value("vertex_color_green").toFloat());
  load_color.setBlueF(instance.value("vertex_color_blue").toFloat());

  SetColor(load_color);
}

void VertexSetting::SetDefaultSettings() {
  type_vertex_ = VertexType::kNone;
  size_ = 5;
  color_ = Qt::white;
}

EdgeSetting::EdgeSetting(EdgeType type, double size, QColor color)
    : type_edge_(type), size_(size), color_(color) {}

void EdgeSetting::SaveSettings(QSettings& instance) {
  instance.setValue("edge_type", static_cast<int>(type_edge_));
  instance.setValue("edge_size", size_);

  instance.setValue("edge_color_red", color_.redF());
  instance.setValue("edge_color_green", color_.greenF());
  instance.setValue("edge_color_blue", color_.blueF());
}

void EdgeSetting::LoadSettings(QSettings& instance) {
  SetType(EdgeType(instance.value("edge_type").toInt()));
  SetSize(instance.value("edge_size").toDouble());

  QColor load_color;
  load_color.setRedF(instance.value("edge_color_red").toFloat());
  load_color.setGreenF(instance.value("edge_color_green").toFloat());
  load_color.setBlueF(instance.value("edge_color_blue").toFloat());

  SetColor(load_color);
}

void EdgeSetting::SetDefaultSettings() {
  type_edge_ = EdgeType::kSolid;
  size_ = 1;
  color_ = Qt::white;
}

CanvaSetting::CanvaSetting(ProjectionType type, QColor back_ground)
    : type_proection_(type), bg_color_(back_ground) {}

void CanvaSetting::SaveSettings(QSettings& instance) {
  instance.setValue("canva_projection_type", static_cast<int>(type_proection_));

  instance.setValue("canva_bg_color_red", bg_color_.redF());
  instance.setValue("canva_bg_color_green", bg_color_.greenF());
  instance.setValue("canva_bg_color_blue", bg_color_.blueF());
}

void CanvaSetting::LoadSettings(QSettings& instance) {
  SetProjectionType(
      ProjectionType(instance.value("canva_projection_type").toInt()));

  QColor load_color;
  load_color.setRedF(instance.value("canva_bg_color_red").toFloat());
  load_color.setGreenF(instance.value("canva_bg_color_green").toFloat());
  load_color.setBlueF(instance.value("canva_bg_color_blue").toFloat());

  SetBGColor(load_color);
}

void CanvaSetting::SetDefaultSettings() {
  type_proection_ = ProjectionType::kCentral;
  bg_color_ = Qt::black;
}

};  // namespace viewer
