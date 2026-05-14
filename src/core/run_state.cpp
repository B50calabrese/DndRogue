#include "core/run_state.h"

#include <cstring>

namespace dnd_rogue::core {

RunState& RunState::Get() {
  static RunState instance;
  return instance;
}

void RunState::Initialize(uint64_t seed) {
  seed_ = seed;
  gold_ = 0;
  collection_.clear();
  deck_.clear();
  commanders_.clear();
}

namespace {
// Helper functions for serialization
void WriteUint64(std::vector<uint8_t>& buffer, uint64_t value) {
  size_t offset = buffer.size();
  buffer.resize(offset + sizeof(value));
  std::memcpy(buffer.data() + offset, &value, sizeof(value));
}

void WriteInt32(std::vector<uint8_t>& buffer, int32_t value) {
  size_t offset = buffer.size();
  buffer.resize(offset + sizeof(value));
  std::memcpy(buffer.data() + offset, &value, sizeof(value));
}

void WriteString(std::vector<uint8_t>& buffer, const std::string& str) {
  WriteUint64(buffer, static_cast<uint64_t>(str.size()));
  size_t offset = buffer.size();
  buffer.resize(offset + str.size());
  std::memcpy(buffer.data() + offset, str.data(), str.size());
}

void WriteCard(std::vector<uint8_t>& buffer, const Card& card) {
  WriteString(buffer, card.id);
  WriteString(buffer, card.name);
}

void WriteCommander(std::vector<uint8_t>& buffer, const Commander& commander) {
  WriteString(buffer, commander.id);
  WriteString(buffer, commander.name);
}

uint64_t ReadUint64(const std::vector<uint8_t>& data, size_t& offset) {
  uint64_t value = 0;
  if (offset + sizeof(value) <= data.size()) {
    std::memcpy(&value, data.data() + offset, sizeof(value));
    offset += sizeof(value);
  }
  return value;
}

int32_t ReadInt32(const std::vector<uint8_t>& data, size_t& offset) {
  int32_t value = 0;
  if (offset + sizeof(value) <= data.size()) {
    std::memcpy(&value, data.data() + offset, sizeof(value));
    offset += sizeof(value);
  }
  return value;
}

std::string ReadString(const std::vector<uint8_t>& data, size_t& offset) {
  uint64_t size = ReadUint64(data, offset);
  if (offset + size <= data.size()) {
    std::string str(reinterpret_cast<const char*>(data.data() + offset), size);
    offset += size;
    return str;
  }
  return "";
}

Card ReadCard(const std::vector<uint8_t>& data, size_t& offset) {
  Card card;
  card.id = ReadString(data, offset);
  card.name = ReadString(data, offset);
  return card;
}

Commander ReadCommander(const std::vector<uint8_t>& data, size_t& offset) {
  Commander commander;
  commander.id = ReadString(data, offset);
  commander.name = ReadString(data, offset);
  return commander;
}
}  // namespace

std::vector<uint8_t> RunState::Serialize() const {
  std::vector<uint8_t> buffer;
  WriteUint64(buffer, seed_);
  WriteInt32(buffer, gold_);

  WriteUint64(buffer, static_cast<uint64_t>(collection_.size()));
  for (const auto& card : collection_) {
    WriteCard(buffer, card);
  }

  WriteUint64(buffer, static_cast<uint64_t>(deck_.size()));
  for (const auto& card : deck_) {
    WriteCard(buffer, card);
  }

  WriteUint64(buffer, static_cast<uint64_t>(commanders_.size()));
  for (const auto& commander : commanders_) {
    WriteCommander(buffer, commander);
  }

  return buffer;
}

void RunState::Deserialize(const std::vector<uint8_t>& data) {
  size_t offset = 0;
  seed_ = ReadUint64(data, offset);
  gold_ = ReadInt32(data, offset);

  uint64_t collection_size = ReadUint64(data, offset);
  collection_.clear();
  for (uint64_t i = 0; i < collection_size; ++i) {
    collection_.push_back(ReadCard(data, offset));
  }

  uint64_t deck_size = ReadUint64(data, offset);
  deck_.clear();
  for (uint64_t i = 0; i < deck_size; ++i) {
    deck_.push_back(ReadCard(data, offset));
  }

  uint64_t commanders_size = ReadUint64(data, offset);
  commanders_.clear();
  for (uint64_t i = 0; i < commanders_size; ++i) {
    commanders_.push_back(ReadCommander(data, offset));
  }
}

}  // namespace dnd_rogue::core
