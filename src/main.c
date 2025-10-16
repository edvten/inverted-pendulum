#include "raylib.h"

int main(void) {
  /* Window Init */
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");

  /* Inverted Pendulum setup */
  float carWidth = 40;
  float carHeight = 20;
  float rodWidht = 50;
  float rodHeight = 10;

  Rectangle car = {(float)screenWidth / 2, (float)screenWidth / 2, carWidth,
                   carHeight};
  Rectangle rod = {(float)screenWidth / 2 + rodWidht / 2.0f - rodHeight / 2.0f,
                   (float)screenWidth / 2 + 5, rodWidht, rodHeight};

  Vector2 leftWheel = {car.x, car.y + carHeight};
  Vector2 rightWheel = {car.x + carWidth, car.y + carHeight};

  float wheelRadius = 10.0f;

  Vector2 origin = {0.0f, 5.0f};

  float rotation = -90.0f;

  SetTargetFPS(60);

  // Main program loop
  while (!WindowShouldClose()) {
    /* Update */
    if (IsKeyDown(KEY_RIGHT)) {
      rod.x += 2.0f;
      car.x += 2.0f;
      leftWheel.x += 2.0f;
      rightWheel.x += 2.0f;
      rotation -= 2.0f;
    }
    if (IsKeyDown(KEY_LEFT)) {
      rod.x -= 2.0f;
      car.x -= 2.0f;
      leftWheel.x -= 2.0f;
      rightWheel.x -= 2.0f;
      rotation += 2.0f;
    }
    if (IsKeyDown(KEY_UP)) {
      rod.y -= 2.0f;
      car.y -= 2.0f;
      leftWheel.y -= 2.0f;
      rightWheel.y -= 2.0f;
    }
    if (IsKeyDown(KEY_DOWN)) {
      rod.y += 2.0f;
      car.y += 2.0f;
      leftWheel.y += 2.0f;
      rightWheel.y += 2.0f;
    }
    /* Update DONE */

    /* Draw */
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

    DrawRectangleRec(car, LIGHTGRAY);
    DrawRectanglePro(rod, origin, rotation, MAROON);
    DrawCircleV(leftWheel, wheelRadius, RED);
    DrawCircleV(rightWheel, wheelRadius, RED);

    EndDrawing();
    /* Draw DONE */
  }

  /* De-Init */
  CloseWindow();

  return 0;
}
