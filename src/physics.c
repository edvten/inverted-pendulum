#include "../include/physics.h"
#include "../include/cart.h"
#include <math.h>
#include <raylib.h>

void update(state_t *s, float F, float dt) {
  float x = s->x;
  float v = s->v;
  float theta = s->theta;
  float omega = s->omega;

  /* Compute accelerations */
  float sineTheta = sinf(theta);
  float cosTheta = cosf(theta);

  float denom = CARMASS + PENDULUMMASS * sineTheta * sineTheta;

  float xSecondDerivative =
      (F + PENDULUMMASS * sineTheta * (PENDULUMLENGTH* omega * omega - GRAVITY * cosTheta)) / denom;

  float thetaSecondDerivative =
      (-F * cosTheta - PENDULUMMASS * PENDULUMLENGTH* omega * omega * cosTheta * sineTheta +
       (CARMASS + PENDULUMMASS) * GRAVITY * sineTheta) /
      (PENDULUMLENGTH* denom);

  /* Integrate and update states (semi-implicit Euler) */
  omega += thetaSecondDerivative * dt;
  omega *= 0.995f;              /* Apply damping */
  theta += omega * dt;

  v += xSecondDerivative * dt;
  x += v * dt;

  /* Wrap angles */
  if (theta > PI)
    theta -= 2 * PI;
  if (theta < -1 * PI)
    theta += 2 * PI;

  /* Update state */
  s->x = x;
  s->v = v;
  s->theta = theta;
  s->omega = omega;
}

float radianToRaylib(float theta) {
        return theta * (180.0 / PI) - 180;
}
