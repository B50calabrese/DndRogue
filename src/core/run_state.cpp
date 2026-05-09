#include "core/run_state.h"

#include <cstring>

namespace dnd_rogue::core {

RunState& RunState::Get() {
  static RunState instance;
  return instance;
}

void RunState::Initialize(uint64_t seed) {
  seed_ = seed;
  // Initialize other fields here in the future
}

std::vector<uint8_t> RunState::Serialize() const {
  std::vector<uint8_t> buffer(sizeof(seed_));
  std::memcpy(buffer.data(), &seed_, sizeof(seed_));
  return buffer;
}

void RunState::Deserialize(const std::vector<uint8_t>& data) {
  if (data.size() >= sizeof(seed_)) {
    std::memcpy(&seed_, data.data(), sizeof(seed_));
  }
}

}  // namespace dnd_rogue::core
