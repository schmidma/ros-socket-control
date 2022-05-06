#include "control_data.hpp"

void ControlData::update(std::vector<VelocityCommand> value) {
  std::unique_lock<std::mutex> lock(data_mutex);
  data = std::move(value);
  is_updated = true;
  condition_variable.notify_all();
}

auto ControlData::has_new_data() const -> bool {
  std::unique_lock<std::mutex> lock(data_mutex);
  return is_updated;
}

auto ControlData::get_new_data() -> std::vector<VelocityCommand> {
  std::unique_lock<std::mutex> lock(data_mutex);
  condition_variable.wait(lock, [this] { return is_updated; });
  is_updated = false;
  return data;
}
