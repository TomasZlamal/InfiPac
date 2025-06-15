#include "world.h"
#include "debug.h"
#include "gravitycomponent.h"
#include "immovablerect.h"
#include "instakillcomponent.h"
#include "learningaicomponent.h"
#include "libs/raylib/src/raylib.h"
#include "pelletcomponent.h"
#include "pelletentity.h"
#include "playercomponent.h"
#include "rectanglerenderer.h"
#include "renderer.h"
#include "rigidbody.h"
#include "simpleaicomponent.h"
#include "utils.h"
#include "worldentity.h"
#include <endian.h>
#include <memory>
#include <string>
#include <vector>
namespace pac {
World::World(int height, int width)
    : m_screenheight(height), m_screenwidth(width), m_score(0) {}
void World::onPlayerDeath() {
  /*int n = 0;
  for (WorldEntity *entity : m_entities) {
    auto pc = entity->getComponent<PlayerComponent>();
    if (pc) {
      m_entities.erase(m_entities.begin() + n);
    }
    ++n;
  }*/
  m_score = 0;
  if (m_ai_score < 0) {
    m_ai.reset();
  } else {
    // TODO: Do LEARNING HERE
  }
  m_ai_score = m_ai_baseline_score;
  m_entities.clear();
  setupEntities();
}
void World::entityLoop() {
  int m = -1;
  const int pellet_factor = 300;
  bool skip_elem = 0;
  bool player_killed = 0;
  for (WorldEntity *entity : m_entities) {
    ++m;
    auto scc = entity->getComponent<pac::SimpleColliderComponent>();
    auto pc = entity->getComponent<PlayerComponent>();
    auto rr = entity->getComponent<Renderer>();
    auto simpleai = entity->getComponent<SimpleAIComponent>();
    auto learningai = entity->getComponent<LearningAIComponent>();
    std::shared_ptr<RigidBody2D> rb = entity->getRigidBody();
    if (simpleai) {
      tryMoveRigidBody(rb, simpleai->getMove(m_entities));
      simpleai->add_anger(0.025f);
    }

    if (learningai) {
      vec2 f = learningai->getMove(m_entities);
      tryMoveRigidBody(rb, f);
      for (WorldEntity *entity_b : m_entities) {
        auto pl = entity_b->getComponent<PlayerComponent>();
        if (pl) {
          vec2 diff = entity_b->getRigidBody()->pos - rb->pos;
          diff.abs();
          float reward = ((m_screenwidth - diff.x) / m_screenwidth +
                          (m_screenheight - diff.y) / m_screenheight);
          if (reward > 0) {
            m_ai_score += reward;
          }
        }
      }
    }

    if (rr) {
      rr->render();
    }
    auto gravity = entity->getComponent<pac::GravityComponent>();

    if (gravity) {
      // DEBUG_PRINT("EWREW")
      tryMoveRigidBody(rb, gravity->getMove());
    }
    if (pc) {
      constexpr float move_factor = 2.5;
      while (!m_inputs.empty()) {
        auto input = m_inputs.front();
        m_inputs.pop();
        switch (input) {
        case pac::UserInput::W_KEY: {
          // rb->pos = rb->pos + vec2{0, -move_factor};
          tryMoveRigidBody(rb, vec2{0, -move_factor});
        } break;
        case pac::UserInput::A_KEY: {
          // rb->pos = rb->pos + vec2{-move_factor, 0};
          tryMoveRigidBody(rb, vec2{-move_factor, 0});
        } break;
        case pac::UserInput::S_KEY: {
          // rb->pos = rb->pos + vec2{0, move_factor};
          tryMoveRigidBody(rb, vec2{0, move_factor});
        } break;
        case pac::UserInput::D_KEY: {
          // rb->pos = rb->pos + vec2{move_factor, 0};
          tryMoveRigidBody(rb, vec2{move_factor, 0});
        } break;

        default:
          break;
        }
      }
    }

    if (scc) {
      int n = -1;
      for (WorldEntity *entity_b : m_entities) {

        ++n;
        if (entity == entity_b) {
          continue;
        }
        auto generic_collider = entity_b->getComponent<Collider>();
        if (entity->type() == entity_b->type() &&
            entity->type() == IMMOVABLE_RECT) {
          continue;
        }
        if (generic_collider) {
          vec2 collision_factor = scc->isColliding(generic_collider);

          if (collision_factor) {

            if (pc) {
              auto pellet = entity_b->getComponent<PelletComponent>();
              // auto instakiill;
              if (pellet) {
                m_entities.erase(m_entities.begin() + n);
                --n;
                m_score++;

                m_ai_score -= pellet_factor;
                continue;
              }

              auto instakill = entity_b->getComponent<InstaKillComponent>();
              if (instakill) {
                player_killed = 1;
                continue;
              }
            }

            auto pellet = entity->getComponent<PelletComponent>();

            auto player = entity_b->getComponent<PlayerComponent>();
            if (pellet) {

              if (player) {
                m_entities.erase(m_entities.begin() + m);
                --m;
                m_score++;
                m_ai_score -= pellet_factor;
                skip_elem = 1;
                break;
              }
            }
            auto instakill = entity->getComponent<InstaKillComponent>();
            if (instakill && player) {
              player_killed = 1;
              continue;
            }
            // handle based on types; fruit, ghost, ...
            auto opposing_rb = entity_b->getRigidBody();
            // collision_factor.getPrint();
            float wth = 1;
            if (opposing_rb)
              wth = opposing_rb->weight;
            float share = rb->weight / wth;
            if (share > 1) {

              tryMoveRigidBody(rb, -(collision_factor / share));
              // rb->pos = rb->pos - (collision_factor / share);
            } else {

              tryMoveRigidBody(rb, -(collision_factor));
              // rb->pos = rb->pos - collision_factor;
            }
            if (opposing_rb) {
              if (share < 1) {

                tryMoveRigidBody(opposing_rb, collision_factor * share);
                /*opposing_rb->pos =
                    opposing_rb->pos + (collision_factor * share);*/
              } else {

                tryMoveRigidBody(opposing_rb, collision_factor);
                // opposing_rb->pos = opposing_rb->pos + collision_factor;
              }
            }
          }
        }
      }
    }
    if (skip_elem) {
      skip_elem = 0;
      continue;
    }
  }
  if (player_killed) {
    onPlayerDeath();
  }
}
void World::setupEntities() {
  auto w1rb = std::shared_ptr<pac::RectangleRigidBody>(
      new pac::RectangleRigidBody({pac::vec2{30, 30}, pac::vec2{1, 2}, 5}));
  auto w2rb =
      std::shared_ptr<pac::RectangleRigidBody>(new pac::RectangleRigidBody(
          {pac::vec2{50, 200}, pac::vec2{100, 200}, 5}));

  pac::WorldEntity *we1 = new WorldEntity{w1rb}, *we2 = new WorldEntity{w2rb};
  pac::ImmovableRect *ir1 = new ImmovableRect{{200, 100}, {300, 300}};
  pac::ImmovableRect *ir2 = new ImmovableRect{{200, 100}, {300, 100}};

  pac::ImmovableRect *ir3 = new ImmovableRect{{50, 50}, {300, 150}, RED};
  ir3->addComponent(new InstaKillComponent());
  pac::ImmovableRect *ir5 = new ImmovableRect{{30, 30}, {200, 200}, RED};

  ir5->addComponent(new InstaKillComponent());
  pac::ImmovableRect *ir4 = new ImmovableRect{{50, 50}, {300, 250}, RED};
  ir4->addComponent(new InstaKillComponent());
  /*pac::ImmovableRect *enemy = new ImmovableRect{{30, 30}, {400, 400}, RED};
  enemy->addComponent(new SimpleAIComponent(enemy->getRigidBody()));
  enemy->addComponent(new InstaKillComponent());*/
  pac::ImmovableRect *enemy = new ImmovableRect{{30, 30}, {400, 400}, RED};
  enemy->addComponent(new InstaKillComponent());
  if (!m_ai) {
    enemy->addComponent(new LearningAIComponent(enemy->getRigidBody(),
                                                m_screenwidth, m_screenheight));
    m_ai = std::shared_ptr<LearningAIComponent>(
        enemy->getComponent<LearningAIComponent>());
  } else {
    enemy->addComponent(m_ai.get());
  }
  pac::PelletEntity *p1 = new PelletEntity{{20, 20}, {300, 200}};

  we1->addComponent(new pac::SimpleColliderComponent(w1rb));
  we2->addComponent(new pac::SimpleColliderComponent(w2rb));

  we2->addComponent(new pac::RectangleRenderer(w2rb));
  we1->addComponent(new pac::PlayerComponent());
  we1->addComponent(new pac::RectangleRenderer(w1rb, YELLOW));
  // ir2.addComponent(new
  // GravityComponent(w2rb, vec2{0,
  // 2})); we2->addComponent(new
  // pac::GravityComponent(w2rb,
  // vec2{0.5f, 0.5f}));
  this->addEntity(we1);
  this->addEntity(we2);
  this->addEntity(ir1);
  this->addEntity(ir2);
  this->addEntity(ir3);
  this->addEntity(ir4);
  this->addEntity(ir5);
  this->addEntity(p1);
  this->addEntity(enemy);
}
void World::worldLoop() {
  // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    if (IsKeyDown(KEY_W))
      handleUserInput(pac::UserInput::W_KEY);
    if (IsKeyDown(KEY_A))

      handleUserInput(pac::UserInput::A_KEY);
    if (IsKeyDown(KEY_S))

      handleUserInput(pac::UserInput::S_KEY);
    if (IsKeyDown(KEY_D))

      handleUserInput(pac::UserInput::D_KEY);
    if (IsKeyDown(KEY_SPACE))
      handleUserInput(pac::UserInput::SPACE_KEY);
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(BLACK);

    entityLoop();
    DrawText((std::string("Score: ") + std::to_string(m_score)).c_str(), 190,
             200, 20, LIGHTGRAY);

    DrawText((std::string("AI Score: ") + std::to_string(m_ai_score)).c_str(),
             0, 0, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }
}
void World::addEntity(WorldEntity *entity) { m_entities.push_back(entity); }
void World::handleUserInput(UserInput input) { m_inputs.push(input); }
void World::runWorld() {
  setupWindow();
  setupEntities();
  worldLoop();
  endWindow();
  // De-Initialization
  //--------------------------------------------------------------------------------------
}

void World::endWindow() {
  CloseWindow(); // Close window and OpenGL context
}
void World::setupWindow() {
  InitWindow(m_screenwidth, m_screenheight, "Pac");

  SetTargetFPS(60);
}

vec2 World::posLocation(vec2 rb) {
  return {((rb.x < 0)               ? -1.0f
           : (rb.x > m_screenwidth) ? 1.0f
                                    : 0),
          ((rb.y < 0)                ? -1.0f
           : (rb.y > m_screenheight) ? 1.0f
                                     : 0)};
}

void World::tryMoveRigidBody(std::shared_ptr<RigidBody2D> rb, vec2 factor) {

  rb->pos = rb->pos + factor;
  if (auto dyn = dynamic_cast<RectangleRigidBody *>(rb.get())) {
    if (rb->pos.x - dyn->wh.x / 2 < 0)
      rb->pos.x = dyn->wh.x / 2;
    if (rb->pos.y - dyn->wh.y / 2 < 0)
      rb->pos.y = dyn->wh.y / 2;
    if (rb->pos.x + dyn->wh.x / 2 > m_screenwidth)
      rb->pos.x = m_screenwidth - dyn->wh.x / 2;
    if (rb->pos.y + dyn->wh.y / 2 > m_screenheight)
      rb->pos.y = m_screenheight - dyn->wh.y / 2;

  } else {
    if (rb->pos.x < 0)
      rb->pos.x = 0;
    if (rb->pos.y < 0)
      rb->pos.y = 0;
    if (rb->pos.x > m_screenwidth)
      rb->pos.x = m_screenwidth;
    if (rb->pos.y > m_screenheight)
      rb->pos.y = m_screenheight;
  }
}
} // namespace pac
