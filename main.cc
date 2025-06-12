#include "raylib/src/raylib.h"

#include "src/debug.h"
#include "src/simplecollidercomponent.h"
#include "src/world.h"
#include "src/worldentity.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;
  pac::World world;
  DEBUG_PRINT("EWR")
  pac::WorldEntity we1, we2;
  pac::RectangleRigidBody w1rb = {pac::vec2{2, 2}, pac::vec2{2, 2}};
  pac::RectangleRigidBody w2rb = {pac::vec2{2, 2}, pac::vec2{1, 2}};
  we1.addComponent(new pac::SimpleColliderComponent(w1rb));
  we2.addComponent(new pac::SimpleColliderComponent(w2rb));
  world.addEntity(&we1);
  world.addEntity(&we2);
  world.worldLoop();

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    if (IsKeyDown(KEY_W))
      world.handleUserInput(pac::UserInput::W_KEY);
    if (IsKeyDown(KEY_LEFT))
      ballPosition.x -= 2.0f;
    if (IsKeyDown(KEY_UP))
      ballPosition.y -= 2.0f;
    if (IsKeyDown(KEY_DOWN))
      ballPosition.y += 2.0f;
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
  DEBUG_PRINT("end")
  return 0;
}
