#pragma once
#include "component.h"
#include "playercomponent.h"
#include "rigidbody.h"
#include "simplecollidercomponent.h"
#include "worldentity.h"
#include <cmath>
#include <cstdlib>
#include <memory>
#include <vector>
namespace pac {
struct Edge;
struct Node {
  float value;
  Edge *next_edges;
  int edge_count;
};
struct Edge {
  Node *dest;
  float value;
};
class LearningAIComponent : public Component {
  Node **m_nodes;

  std::shared_ptr<RigidBody2D> m_rb;
  int lengths[3] = {32, 24, 5};
  void init() {
    m_nodes = new Node *[3];
    //= new Node[m_starting_node_count]{};
    for (int i = 0; i < 3; i++) {
      m_nodes[i] = new Node[lengths[i]]{};
      for (int j = 0; j < lengths[i]; j++) {
        m_nodes[i][j].value = rand() - 1 / RAND_MAX;
      }
    }
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < lengths[i]; j++) {
        m_nodes[i][j].next_edges = new Edge[lengths[i + 1]];
        for (int m = 0; i < lengths[i + 1]; m++) {
          m_nodes[i][j].next_edges[m].dest = m_nodes[i + 1] + m;

          m_nodes[i][j].next_edges[m].value = rand() - 1 / RAND_MAX;
        }
      }
    }
  }
  int getQuadrant(std::shared_ptr<RigidBody2D> rb) {
    int count = sqrt(lengths[0] / 2);
    vec2 one_square =
        vec2{m_screen_width / (float)count, m_screen_height / (float)count};
    for (int i = 0; i < count; i++) {
      for (int j = 0; j < count; j++) {
        vec2 square_tl = vec2{one_square.x * i, one_square.y * j};
        vec2 points_a[] = {square_tl, square_tl + one_square};
        vec2 d1 = rb->pos - points_a[0];
        vec2 d2 = rb->pos - points_a[1];
        if (d1.x > 0 && d1.y > 0 && d2.x < 0 && d2.y < 0) {
          return (i + j * 4); // 0..15
        }
      }
    }
    return {};
  }
  int m_screen_height;
  int m_screen_width;

public:
  LearningAIComponent(std::shared_ptr<RigidBody2D> rb, int screen_width,
                      int screen_height)
      : m_rb(rb), m_screen_height(screen_height), m_screen_width(screen_width) {
  }
  vec2 getMove(const std::vector<WorldEntity *> &m_entities) {
    int player_quadrant = 0;
    int ai_quadrant = getQuadrant(m_rb);
    for (WorldEntity *entity : m_entities) {
      auto pc = entity->getComponent<PlayerComponent>();
      if (pc) {
        player_quadrant = getQuadrant(entity->getRigidBody());
      }
    }
    m_nodes[0][player_quadrant].value = 1.0f;
    m_nodes[0][15 + ai_quadrant].value = 1.0f;
    // TODO Traverse through graph and get the five values
  }
};
} // namespace pac
