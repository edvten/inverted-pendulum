#include "../include/cart.h"
#include "../include/controller.h"
#include "../include/physics.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

#define PIXELS_PER_METER (100.0f)

float clamp(float num, float minMax) {
  if (num > minMax)
    return minMax;
  if (num < -minMax)
    return -minMax;
  return num;
}

int main(void) {
  /* Window Init */
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Inverted Pendulum");

  /* Inverted Pendulum setup */
  const float carWidth = CARWIDTH * PIXELS_PER_METER;
  const float carHeight = CARHEIGHT * PIXELS_PER_METER;
  const float rodWidth = PENDULUMWIDTH * PIXELS_PER_METER;
  const float rodLength = PENDULUMLENGTH * PIXELS_PER_METER;
  const float wheelRadius = WHEELRADIUS * PIXELS_PER_METER;

  const float centerX = (float)screenWidth / 2;
  const float centerY = (float)screenWidth / 2;

  Rectangle car = {centerX, centerY, carWidth, carHeight};
  Rectangle rod = {centerX + carWidth / 2.0, centerY, rodWidth, rodLength};

  Vector2 leftWheel = {car.x, car.y + carHeight};
  Vector2 rightWheel = {car.x + carWidth, car.y + carHeight};

  Vector2 origin = {rodWidth / 2.0, 0.0f};

  float rotation = -90.0f;

  SetTargetFPS(60);

  state_t state = {3, 0, 0.0, 0};
  float F = 0;
  float xRef = 0.0;
  float dt;

  bool automaticControl = true;

  // Main program loop
  while (!WindowShouldClose()) {
    /* Update */

    if (automaticControl) {
      F = clamp(controller(&state, xRef), 10.0);
    } else {
      if (IsKeyDown(KEY_RIGHT)) {
        F = 3;
      }
      if (IsKeyDown(KEY_LEFT)) {
        F = -3;
      }
      if (IsKeyDown(KEY_DOWN)) {
        F = 0;
      }
    }
    if (IsKeyDown(KEY_RIGHT)) {
      xRef += 0.1;
    }
    if (IsKeyDown(KEY_LEFT)) {
      xRef -= 0.1;
    }
    if (IsKeyPressed(KEY_C)) {
      automaticControl = !automaticControl;
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

    DrawText("Press c to toggle between manual and automatic control", 10, 10,
             20, DARKGRAY);
    if (automaticControl) {
      DrawText("Automatic", screenWidth - 180, 10, 20, MAROON);
      const char *xRefText = 0;
      const char *thetaText = 0;
      xRefText = TextFormat("x - target: %.1f, actual: %.1f", xRef, state.x);
      thetaText =
          TextFormat("theta - target: 0.0, actual: %.1f", 180.0 + rotation);
      DrawText(xRefText, 10, 60, 20, DARKGRAY);
      DrawText(thetaText, 10, 80, 20, DARKGRAY);
    } else {
      DrawText("Manual", screenWidth - 180, 10, 20, GREEN);
    }

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
