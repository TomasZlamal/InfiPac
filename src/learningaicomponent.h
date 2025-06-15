#pragma once
#include "component.h"
#include "debug.h"
#include "playercomponent.h"
#include "rigidbody.h"
#include "simplecollidercomponent.h"
#include "worldentity.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
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

        for (int m = 0; m < lengths[i + 1]; m++) {
          m_nodes[i][j].next_edges[m].dest = m_nodes[i + 1] + m;

          m_nodes[i][j].next_edges[m].value =
              1.0f - (float)(rand() % 10000000) / 5000000;
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
  float sigmoid(float x) { return (x) / (1 + std::abs(x)); }
  int m_screen_height;
  int m_screen_width;
  void traverseGraph() {
    Node *curr;
    std::vector<Node *> next_nodes;

    for (int i = 0; i < lengths[0]; i++) {
      curr = m_nodes[0] + i;
      for (int j = 1; j < 3; j++) { // skip O-th
        for (int m = 0; m < lengths[j]; m++) {
          if (i == 0) {
            m_nodes[j][m].value = 0;
          }
          m_nodes[j][m].value += curr->value * curr->next_edges[m].value;
          // DEBUG_PRINT(curr->next_edges[m].value)
          /*if (curr->value > 0)
            DEBUG_PRINT(i)
          if (j == 1 && m_nodes[j][m].value > 0)
            DEBUG_PRINT(m_nodes[j][m].value)*/
        }
        curr = m_nodes[j];
      }
    }
    for (int j = 1; j < 3; j++) { // skip O-th
      for (int m = 0; m < lengths[j]; m++) {
        m_nodes[j][m].value = sigmoid(m_nodes[j][m].value);
      }
    }
  }

public:
  LearningAIComponent(std::shared_ptr<RigidBody2D> rb, int screen_width,
                      int screen_height)
      : m_rb(rb), m_screen_height(screen_height), m_screen_width(screen_width) {
    init();
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
    for (int i = 0; i < lengths[0]; i++) {
      m_nodes[0][i].value = 0;
    }
    m_nodes[0][player_quadrant].value = 1.0f;
    m_nodes[0][15 + ai_quadrant].value = 1.0f;
    // std::cout << "QP: " << player_quadrant << ", QA: " << ai_quadrant <<
    // "\n";
    traverseGraph();
    vec2 vals[] = {vec2{0, -1}, vec2{-1, 0}, vec2{0, 1}, vec2{1, 0}};
    vec2 res = {0, 0};
    std::cout << "{";
    for (int i = 0; i < 4; i++) {
      if (m_nodes[2][i].value < 0) {
        continue;
      }
      res = res + vals[i] * m_nodes[2][i].value;
      std::cout << m_nodes[2][i].value << ", ";
    }

    std::cout << "}\n";
    DEBUG_PRINT(res.x << ", " << res.y)
    if (m_nodes[2][4].value > 0.8)
      return {};

    // DEBUG_PRINT("here");
    return res * 3.0f; // m_nodes[4] is speed
  }
  ~LearningAIComponent() {
    for (int i = 0; i < lengths[0]; i++) {
      delete[] m_nodes[0][i].next_edges;
    }
    delete[] m_nodes[0];
    for (int j = 0; j < lengths[1]; j++) {

      delete[] m_nodes[1][j].next_edges;
    }

    delete[] m_nodes[1];
    for (int m = 0; m < lengths[2]; m++) {

      delete[] m_nodes[2][m].next_edges;
    }

    delete[] m_nodes[2];

    delete[] m_nodes;
  }
};
} // namespace pac
