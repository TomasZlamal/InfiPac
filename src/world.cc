#include "world.h"
#include "debug.h"
#include "playercomponent.h"
#include "rectanglerenderer.h"
#include "renderer.h"
#include <chrono>
#include <endian.h>
#include <memory>
#include <thread>
namespace pac {
World::World() {}
void World::entityLoop() {
  for (WorldEntity *entity : m_entities) {
    auto scc = entity->getComponent<pac::SimpleColliderComponent>();
    auto pc = entity->getComponent<PlayerComponent>();

    if (scc) {

      for (WorldEntity *entity_b : m_entities) {
        if (entity == entity_b)
          continue;
        auto generic_collider = entity_b->getComponent<Collider>();
        if (generic_collider) {
          if (scc->isColliding(generic_collider)) {
            // handle based on types; fruit, ghost, ...
            DEBUG_PRINT("Collided.")
          }
        }
      }
    }
    auto rr = entity->getComponent<Renderer>();
    if (rr) {

      rr->render();
    }
    if (pc) {
      std::shared_ptr<RigidBody2D> rb = entity->getRigidBody();
      constexpr float move_factor = 0.4;
      if (m_lastinput != UserInput::NONE) {
        switch (m_lastinput) {
        case pac::UserInput::W_KEY: {
          rb->pos = rb->pos + vec2{0, -move_factor};
        } break;
        case pac::UserInput::A_KEY: {
          rb->pos = rb->pos + vec2{-move_factor, 0};
        } break;
        case pac::UserInput::S_KEY: {
          rb->pos = rb->pos + vec2{0, move_factor};
        } break;
        case pac::UserInput::D_KEY: {
          rb->pos = rb->pos + vec2{move_factor, 0};
        } break;
        default:
          break;
        }
      }
    }
  }
}
void World::worldLoop() { entityLoop(); }
void World::addEntity(WorldEntity *entity) { m_entities.push_back(entity); }
void World::handleUserInput(UserInput input) { m_lastinput = input; }
void World::runWorld() {
  const int screenWidth = 800;
  const int screenHeight = 450;
  auto w1rb = std::shared_ptr<pac::RectangleRigidBody>(
      new pac::RectangleRigidBody({pac::vec2{30, 30}, pac::vec2{1, 2}}));
  auto w2rb = std::shared_ptr<pac::RectangleRigidBody>(
      new pac::RectangleRigidBody({pac::vec2{200, 200}, pac::vec2{100, 200}}));

  pac::WorldEntity we1{w1rb}, we2{w2rb};

  we1.addComponent(new pac::SimpleColliderComponent(w1rb));
  we2.addComponent(new pac::SimpleColliderComponent(w1rb));

  we2.addComponent(new pac::RectangleRenderer(w2rb));
  we1.addComponent(new pac::PlayerComponent());
  we1.addComponent(new pac::RectangleRenderer(w1rb));
  this->addEntity(&we1);
  this->addEntity(&we2);

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
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
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    worldLoop();
    /*DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);*/

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
}
} // namespace pac
