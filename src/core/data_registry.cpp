#include "core/data_registry.h"

#include <filesystem>
#include <iostream>

#include "engine/util/logger.h"
#include "pugixml/pugixml.hpp"

namespace dnd_rogue::core {

DataRegistry& DataRegistry::Get() {
  static DataRegistry instance;
  return instance;
}

void DataRegistry::LoadAll(const std::string& assets_path) {
  std::filesystem::path data_path = std::filesystem::path(assets_path) / "data";
  LoadCards((data_path / "cards").string());
  LoadCommanders((data_path / "commanders").string());
}

const Card* DataRegistry::GetCard(const std::string& id) const {
  auto it = cards_.find(id);
  if (it != cards_.end()) {
    return &it->second;
  }
  return nullptr;
}

const Commander* DataRegistry::GetCommander(const std::string& id) const {
  auto it = commanders_.find(id);
  if (it != commanders_.end()) {
    return &it->second;
  }
  return nullptr;
}

void DataRegistry::LoadCards(const std::string& cards_path) {
  if (!std::filesystem::exists(cards_path)) {
    LOG_WARN("Cards directory not found: %s", cards_path.c_str());
    return;
  }

  for (const auto& entry : std::filesystem::directory_iterator(cards_path)) {
    if (entry.path().extension() == ".xml") {
      pugi::xml_document doc;
      pugi::xml_parse_result result = doc.load_file(entry.path().c_str());

      if (result) {
        pugi::xml_node card_node = doc.child("Card");
        Card card;
        card.id = card_node.child_value("Id");
        card.name = card_node.child_value("Name");

        if (!card.id.empty()) {
          cards_[card.id] = card;
          LOG_INFO("Loaded card: %s (%s)", card.id.c_str(), card.name.c_str());
        } else {
          LOG_WARN("Card file missing Id: %s", entry.path().string().c_str());
        }
      } else {
        LOG_ERR("Failed to parse card XML: %s", entry.path().string().c_str());
      }
    }
  }
}

void DataRegistry::LoadCommanders(const std::string& commanders_path) {
  if (!std::filesystem::exists(commanders_path)) {
    LOG_WARN("Commanders directory not found: %s", commanders_path.c_str());
    return;
  }

  for (const auto& entry : std::filesystem::directory_iterator(commanders_path)) {
    if (entry.path().extension() == ".xml") {
      pugi::xml_document doc;
      pugi::xml_parse_result result = doc.load_file(entry.path().c_str());

      if (result) {
        pugi::xml_node commander_node = doc.child("Commander");
        Commander commander;
        commander.id = commander_node.child_value("Id");
        commander.name = commander_node.child_value("Name");

        if (!commander.id.empty()) {
          commanders_[commander.id] = commander;
          LOG_INFO("Loaded commander: %s (%s)", commander.id.c_str(),
                   commander.name.c_str());
        } else {
          LOG_WARN("Commander file missing Id: %s", entry.path().string().c_str());
        }
      } else {
        LOG_ERR("Failed to parse commander XML: %s", entry.path().string().c_str());
      }
    }
  }
}

}  // namespace dnd_rogue::core
