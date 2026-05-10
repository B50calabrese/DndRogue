#include "core/run_state.h"

#include <cstring>

namespace dnd_rogue::core {

RunState& RunState::Get() {
  static RunState instance;
  return instance;
}

void RunState::Initialize(uint64_t seed) {
  seed_ = seed;
  gold_ = 100;  // Default starting gold
  characters_.clear();
  combat_cards_.clear();
  items_.clear();

  // Add "test" items
  characters_.push_back({"Test Character"});
  combat_cards_.push_back({"Test Card"});
  items_.push_back({"Test Item"});
}

namespace {
// Helper functions for serialization
void WriteUint64(std::vector<uint8_t>& buffer, uint64_t value) {
  uint8_t bytes[8];
  std::memcpy(bytes, &value, 8);
  buffer.insert(buffer.end(), bytes, bytes + 8);
}

void WriteInt32(std::vector<uint8_t>& buffer, int32_t value) {
  uint8_t bytes[4];
  std::memcpy(bytes, &value, 4);
  buffer.insert(buffer.end(), bytes, bytes + 4);
}

void WriteString(std::vector<uint8_t>& buffer, const std::string& str) {
  WriteUint64(buffer, static_cast<uint64_t>(str.size()));
  buffer.insert(buffer.end(), str.begin(), str.end());
}

uint64_t ReadUint64(const std::vector<uint8_t>& data, size_t& offset) {
  if (offset + 8 > data.size()) return 0;
  uint64_t value;
  std::memcpy(&value, &data[offset], 8);
  offset += 8;
  return value;
}

int32_t ReadInt32(const std::vector<uint8_t>& data, size_t& offset) {
  if (offset + 4 > data.size()) return 0;
  int32_t value;
  std::memcpy(&value, &data[offset], 4);
  offset += 4;
  return value;
}

std::string ReadString(const std::vector<uint8_t>& data, size_t& offset) {
  uint64_t size = ReadUint64(data, offset);
  if (offset + size > data.size()) return "";
  std::string str(reinterpret_cast<const char*>(&data[offset]), size);
  offset += size;
  return str;
}
}  // namespace

std::vector<uint8_t> RunState::Serialize() const {
  std::vector<uint8_t> buffer;
  WriteUint64(buffer, seed_);
  WriteInt32(buffer, gold_);

  WriteUint64(buffer, static_cast<uint64_t>(characters_.size()));
  for (const auto& c : characters_) {
    WriteString(buffer, c.name);
  }

  WriteUint64(buffer, static_cast<uint64_t>(combat_cards_.size()));
  for (const auto& c : combat_cards_) {
    WriteString(buffer, c.name);
  }

  WriteUint64(buffer, static_cast<uint64_t>(items_.size()));
  for (const auto& i : items_) {
    WriteString(buffer, i.name);
  }

  return buffer;
}

void RunState::Deserialize(const std::vector<uint8_t>& data) {
  size_t offset = 0;
  seed_ = ReadUint64(data, offset);
  gold_ = ReadInt32(data, offset);

  uint64_t char_count = ReadUint64(data, offset);
  characters_.clear();
  for (uint64_t i = 0; i < char_count; ++i) {
    characters_.push_back({ReadString(data, offset)});
  }

  uint64_t card_count = ReadUint64(data, offset);
  combat_cards_.clear();
  for (uint64_t i = 0; i < card_count; ++i) {
    combat_cards_.push_back({ReadString(data, offset)});
  }

  uint64_t item_count = ReadUint64(data, offset);
  items_.clear();
  for (uint64_t i = 0; i < item_count; ++i) {
    items_.push_back({ReadString(data, offset)});
  }
}

}  // namespace dnd_rogue::core
