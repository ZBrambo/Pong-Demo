# Pong Game Demo (C++ & raylib)

A basic Pong game built using C++ and the [raylib](https://www.raylib.com/) game development library. This project demonstrates the fundamentals of 2D game programming, including player input handling, basic collision detection, object-oriented design, and simple AI logic for a CPU paddle.

## 🎮 Features

- Player paddle controlled using `W` and `S` keys
- CPU paddle with simple AI tracking the ball
- Score tracking and display
- Ball resets after scoring, with randomized direction
- Frame-based animation at 60 FPS

## 🛠 Requirements

- C++ compiler (e.g., `g++`, `clang++`)
- raylib library installed and properly linked

## 🧩 Building the Game

If you have raylib installed via your package manager or manually, you can compile the code using:

```bash
g++ pong.cpp -o pong -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
