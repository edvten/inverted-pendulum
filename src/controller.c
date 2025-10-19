#include "../include/controller.h"
#include "../include/physics.h"

float controller(state_t *state, float xRef) {
  /* Precomputed by LQR */
  const float Kx = 2.4586f;
  const float Kv = 4.0788f;
  const float Ktheta = 27.9984f;
  const float Komega = 5.0009f;

  float errorX = state->x - xRef;
  return (Kx * errorX + Kv * state->v + Ktheta * state->theta +
          Komega * state->omega);
}
