#ifndef CART_H
#define CART_H

#define CARMASS (0.5)      /* Cart mass */
#define CARWIDTH (0.5)     /* Car widht */
#define CARHEIGHT (0.2)    /* Car height */
#define PENDULUMMASS (0.1) /* Pendulum mass */
// #define b (0.1)                /* Friction coefficient */
#define INERTIA (0.006)      /* Moment of intertia pendulum */
#define GRAVITY (9.8)        /* Gravity constant */
#define PENDULUMLENGTH (0.5) /* Length to pendulum center of mass */
#define PENDULUMWIDTH (0.05) /* Pendulum widht */

#define WHEELRADIUS (0.1)

#define q ((M + m) * (I + m * l * l) - (m * m * l * l))
#endif /* CART_H */
