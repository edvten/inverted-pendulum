#include "../include/cart.h"
#include "../include/physics.h"
#include "raylib.h"
#include <stdio.h>

#define PIXELS_PER_METER (100.0f);

int main(void) {
  /* Window Init */
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");

  /* Inverted Pendulum setup */
  const float carWidth = CARWIDTH * PIXELS_PER_METER;
  const float carHeight = CARHEIGHT * PIXELS_PER_METER;
  const float rodWidht = PENDULUMWIDTH * PIXELS_PER_METER;
  const float rodLength = PENDULUMLENGTH * PIXELS_PER_METER;
  const float wheelRadius = WHEELRADIUS * PIXELS_PER_METER;

  const float centerX = (float)screenWidth / 2;
  const float centerY = (float)screenWidth / 2;

  Rectangle car = {centerX, centerY, carWidth, carHeight};
  Rectangle rod = {centerX + carWidth / 2.0, centerY, rodWidht, rodLength};

  Vector2 leftWheel = {car.x, car.y + carHeight};
  Vector2 rightWheel = {car.x + carWidth, car.y + carHeight};

  Vector2 origin = {rodWidht / 2.0, 0.0f};

  float rotation = -90.0f;

  SetTargetFPS(60);

  state_t state = {0, 0, 0.1, 0};
  float F = 0;
  float dt;

  // Main program loop
  while (!WindowShouldClose()) {
    /* Update */
    if (IsKeyDown(KEY_RIGHT)) {
      F = 3;
    }
    if (IsKeyDown(KEY_LEFT)) {
      F = -3;
    }
    if (IsKeyDown(KEY_DOWN)) {
      F = 0;
    }

    dt = GetFrameTime();
    /* change dt to actual time from last frame given by raylib */
    update(&state, F, dt);

    car.x = centerX + state.x * PIXELS_PER_METER;

    rod.x = car.x + carWidth / 2.0;
    leftWheel.x = car.x;
    rightWheel.x = car.x + carWidth;

    rotation = radianToRaylib(state.theta);

    printf("x = %.3f, v = %.3f, theta = %.3f deg, omega = %.3f, F = %.2f\n",
           state.x, state.v, rotation, state.omega, F);
    
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
