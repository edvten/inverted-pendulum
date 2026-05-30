# Inverted Pendulum Simulation

A real-time inverted pendulum (cart-pole) simulation written in C using Raylib.

## Features
* **Automatic Control:** Uses an LQR controller to balance the pole upright.
* **Manual Control:** Apply forces manually using the keyboard.
* **Physics:** Implements rigid-body dynamics using semi-implicit Euler integration.

## Controls
* `C` - Toggle between Manual and Automatic control modes.
* `Left` / `Right` Arrow keys - Move the cart or adjust the target position ($x_{ref}$).

## Build & Run
Requires **Raylib** installed on your system.

```bash
make      # Compile the project
make run  # Compile and run immediately
make clean # Remove build files
