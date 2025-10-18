#ifndef PHYSICS_H
#define PHYSICS_H

typedef struct state_t {
  float x;     /* Cart position */
  float v;     /* Cart velocity */
  float theta; /* Pendulum angle */
  float omega; /* Pendulum angular velocity */
} state_t;

void update(state_t *s, float F, float dt);
float radianToRaylib(float theta);
#endif /* PHYSICS_H */
