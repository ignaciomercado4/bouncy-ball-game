#include "raylib.h"
#include "resource_dir.h"
#include "player.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 540

int main ()
{
	// initialization
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncy ball");
	
	SearchAndSetResourceDir("resources");

	// textures
	Texture2D backgroundImage = LoadTexture("background.png");
	Texture2D floorImage = LoadTexture("floor.png");

	// structures
	Player player;
	player.position.x = 0.0f;
	player.position.y = 0.0f;

	// game loop
	while (!WindowShouldClose())		
	{
		// user input
		if (IsKeyDown(KEY_W)) player.position.y--;
		if (IsKeyDown(KEY_A)) player.position.x--;
		if (IsKeyDown(KEY_S)) player.position.y++;
		if (IsKeyDown(KEY_D)) player.position.x++;

		// drawing
		BeginDrawing();

		DrawTexture(backgroundImage, 0, 0, WHITE);
		DrawTexture(floorImage, 0, SCREEN_HEIGHT - floorImage.height, WHITE);
		DrawCircle(player.position.x, player.position.y, 20, RED);
		
		EndDrawing();
	}

	// cleanup
	UnloadTexture(backgroundImage);
	UnloadTexture(floorImage);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
