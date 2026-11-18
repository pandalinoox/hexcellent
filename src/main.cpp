#include "raylib.h"

#define FPS 60

int main(void) {
  const int screen_width = 400;
  const int screen_height = 400;
  const int posx = 150;
  const int posy = 200;
  const int font_size = 20;

  InitWindow(screen_width, screen_height, "gaem");
  SetTargetFPS(FPS);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hexcellent!", posx, posy, font_size, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
