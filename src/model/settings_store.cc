#include "settings_store.h"

namespace s21 {
bool SettingsStore::Save(std::string& filename) {
  std::ofstream ofs(filename, std::ios::out | std::ios::binary);

  if (!ofs) {
    return false;
  }

  ofs.write((char*)&state_, sizeof(state_));

  return true;
}

bool SettingsStore::Load(std::string& filename) {
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);

  if (!ifs) {
    return false;
  }

  ifs.read((char*)&state_, sizeof(state_));

  return true;
}

void SettingsStore::UpdateColorSetting(ColorConsumer consumer, QColor color) {
  switch (consumer) {
    case ColorConsumer::kBackground:
      state_.color.background = color;
      break;
    case ColorConsumer::kLine:
      state_.color.line = color;
      break;
    case ColorConsumer::kVertex:
      state_.color.vertex = color;
      break;
  }
}

void SettingsStore::UpdateDisplayTypeSetting(DisplayType type) {
  switch (type) {
    case kParallelProjection:
      state_.type.projection = kParallel;
      break;
    case kCentralProjection:
      state_.type.projection = kCentral;
      break;
    case kSolidLine:
      state_.type.line = kSolid;
      break;
    case kDashLine:
      state_.type.line = kDash;
      break;
    case kNoneVertex:
      state_.type.vertex = kNone;
      break;
    case kCircleVertex:
      state_.type.vertex = kCircle;
      break;
    case kSquareVertex:
      state_.type.vertex = kSquare;
      break;
  }
}

void SettingsStore::UpdateSizeSetting(SizeConsumer consumer,
                                      unsigned int size) {
  switch (consumer) {
    case SizeConsumer::kLine:
      state_.size.line_size = size;
      break;
    case SizeConsumer::kVertex:
      state_.size.vertex_size = size;
      break;
  }
}

}  // namespace s21
