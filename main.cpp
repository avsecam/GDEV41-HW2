#include <raylib.h>

int main() {
  InitWindow(800, 600, "Hello Raylib");
  while (!WindowShouldClose()) {
      BeginDrawing();
      EndDrawing();
  }
  CloseWindow();
  return 0;
}