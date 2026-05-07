#include "overworld/pathfinding.h"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>

namespace dnd_rogue::overworld {

struct Node {
  glm::ivec2 pos;
  int g_cost;
  int h_cost;
  glm::ivec2 parent;

  int f_cost() const { return g_cost + h_cost; }

  bool operator>(const Node& other) const {
    return f_cost() > other.f_cost();
  }
};

// Simple hash for glm::ivec2 to use in unordered_map
struct Vec2Hash {
  std::size_t operator()(const glm::ivec2& v) const {
    return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
  }
};

int Heuristic(const glm::ivec2& a, const glm::ivec2& b) {
  return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<glm::ivec2> FindPath(const glm::ivec2& start, const glm::ivec2& end,
                                const MapData& map) {
  if (start == end) return {start};
  if (!map.IsWalkable(end.x, end.y)) return {};

  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open_set;
  std::unordered_map<glm::ivec2, int, Vec2Hash> g_costs;
  std::unordered_map<glm::ivec2, glm::ivec2, Vec2Hash> parents;

  open_set.push({start, 0, Heuristic(start, end), start});
  g_costs[start] = 0;

  while (!open_set.empty()) {
    Node current = open_set.top();
    open_set.pop();

    if (current.pos == end) {
      std::vector<glm::ivec2> path;
      glm::ivec2 curr_pos = end;
      while (curr_pos != start) {
        path.push_back(curr_pos);
        curr_pos = parents[curr_pos];
      }
      path.push_back(start);
      std::reverse(path.begin(), path.end());
      return path;
    }

    const glm::ivec2 neighbors[] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    for (const auto& offset : neighbors) {
      glm::ivec2 neighbor_pos = current.pos + offset;

      if (map.IsWalkable(neighbor_pos.x, neighbor_pos.y)) {
        int new_g_cost = current.g_cost + 1;
        if (g_costs.find(neighbor_pos) == g_costs.end() || new_g_cost < g_costs[neighbor_pos]) {
          g_costs[neighbor_pos] = new_g_cost;
          parents[neighbor_pos] = current.pos;
          open_set.push({neighbor_pos, new_g_cost, Heuristic(neighbor_pos, end), current.pos});
        }
      }
    }
  }

  return {};
}

}  // namespace dnd_rogue::overworld
