#ifndef MODEL_SETTINGS_STORAGE_H
#define MODEL_SETTINGS_STORAGE_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "settings.h"

namespace s21 {
class SettingsStore {
 public:
  SettingsStore() {}
  SettingsStore(std::string filename) : filename_(filename) { Load(filename_); }
  ~SettingsStore() { Save(filename_); }

  const Settings& GetStateRef() const { return state_; }

  void UpdateColorSetting(ColorConsumer consumer, QColor color);
  void UpdateDisplayTypeSetting(DisplayType type);
  void UpdateSizeSetting(SizeConsumer consumer, unsigned int size);
  bool Save(std::string& filename);
  bool Load(std::string& filename);

 private:
  std::string filename_;
  Settings state_;
};

}  // namespace s21

#endif  // MODEL_SETTINGS_STORAGE_H
