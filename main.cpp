#include <raylib.h>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


struct Particle {
  bool isActive;
  Vector2 position;
  Vector2 direction;
  float speed;
  float lifeTime;
  Color color;

  Particle() {
    isActive = false;
    position.x = 0.0f;
    position.y = 0.0f;
    direction.x = 0.0f;
    direction.y = 0.0f;
    speed = 0.0f;
    lifeTime = 0.0f;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
  }
};


int main() {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Loop, Input Handling, and Frames");
  while (!WindowShouldClose()) {
      BeginDrawing();
      EndDrawing();
  }
  CloseWindow();
  return 0;
}