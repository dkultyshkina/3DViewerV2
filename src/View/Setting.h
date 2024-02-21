#ifndef SRC_VIEW_SETTING_H_
#define SRC_VIEW_SETTING_H_

#include <QColor>
#include <QSettings>
#include <iostream>

namespace viewer {

class BaseSetting {
 public:
  virtual void SaveSettings(QSettings& instance) = 0;
  virtual void LoadSettings(QSettings& instance) = 0;
  virtual void SetDefaultSettings() = 0;
};

class VertexSetting : BaseSetting {
 public:
  enum class VertexType : int { kNone = 0, kRounded, kSquare };

  VertexSetting() = default;
  VertexSetting(VertexType type, double size, QColor color);

  void SetSize(double size) { size_ = size; }
  void SetType(VertexType type) { type_vertex_ = type; }
  void SetColor(QColor color) { color_ = color; }

  double GetSize() { return size_; }
  VertexType GetType() { return type_vertex_; }
  QColor GetColor() { return color_; }

  void SaveSettings(QSettings& instance) override;
  void LoadSettings(QSettings& instance) override;
  void SetDefaultSettings() override;

 private:
  VertexType type_vertex_;
  double size_;
  QColor color_;
};

class EdgeSetting : BaseSetting {
 public:
  enum class EdgeType : int {
    kSolid = 0,
    kDotted,
  };
  EdgeSetting() = default;
  EdgeSetting(EdgeType type, double size, QColor color);

  void SetSize(double size) { size_ = size; }
  void SetType(EdgeType type) { type_edge_ = type; }
  void SetColor(QColor color) { color_ = color; }

  double GetSize() { return size_; }
  EdgeType GetType() { return type_edge_; }
  QColor GetColor() { return color_; }

  void SaveSettings(QSettings& instance) override;
  void LoadSettings(QSettings& instance) override;
  void SetDefaultSettings() override;

 private:
  EdgeType type_edge_;
  double size_;
  QColor color_;
};

class CanvaSetting : BaseSetting {
 public:
  enum class ProjectionType {
    kParalel = 0,
    kCentral,
  };
  CanvaSetting() = default;
  CanvaSetting(ProjectionType type, QColor back_ground);

  void SetProjectionType(ProjectionType type) { type_proection_ = type; }
  void SetBGColor(QColor color) { bg_color_ = color; }

  ProjectionType GetProjectionType() { return type_proection_; }
  QColor GetBGColor() { return bg_color_; }

  void SaveSettings(QSettings& instance) override;
  void LoadSettings(QSettings& instance) override;
  void SetDefaultSettings() override;

 private:
  ProjectionType type_proection_;
  QColor bg_color_;
};

};  // namespace viewer

#endif  // SRC_VIEW_SETTING_H_
