#include "raylib.h"
#include "utils.h"

int main(int argc, char *argv[]) {

	initBrickWall();
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Brick Another Brick On the Wall");
	SetTargetFPS(TARGET_FPS);

	while(!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);

			gameScene();

		EndDrawing();
	};

	CloseWindow();
	return 0;
};
