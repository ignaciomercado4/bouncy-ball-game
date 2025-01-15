#include "raylib.h"
#include "resource_dir.h"
#include "player.h"
#include "door.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 540
#define GRAVITY 0.5f
#define JUMP_FORCE -10.0f

int main ()
{
	// initialization
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bouncy ball");
	
	SearchAndSetResourceDir("resources");

	// textures
	Texture2D backgroundTexture = LoadTexture("background.png");
	Texture2D floorTexture = LoadTexture("floor.png");
	Texture2D ballTexture = LoadTexture("ball.png");
	Texture2D doorTexture = LoadTexture("door.png");

	// player struct
	Rectangle playerHitbox = {0.0f, 0.0f, 64.0f, 64.0f};
	Rectangle floorHitbox = {0.0f, SCREEN_HEIGHT - floorTexture.height, SCREEN_WIDTH, floorTexture.height};
	Player player;
	player.position.x = 0.0f;
	player.position.y = 0.0f;
	player.hitbox = playerHitbox;

	// door struc
	Rectangle doorHitbox = {SCREEN_WIDTH - doorTexture.width, SCREEN_HEIGHT - floorTexture.height * 2, floorTexture.width, floorTexture.height};
	Door door;
	door.hitbox = doorHitbox;

	// physics variables
	player.canJump = false;
	float velocityY = 0.0f;


	// game loop
	while (!WindowShouldClose())		
	{
		// user input
		if (IsKeyDown(KEY_W) && player.canJump) {
			velocityY = JUMP_FORCE;
            player.canJump = false;
		} 

		if (IsKeyDown(KEY_A)) player.hitbox.x -= 2.0f;
		if (IsKeyDown(KEY_D)) player.hitbox.x += 2.0f;

		velocityY += GRAVITY;
        player.hitbox.y += velocityY;

		 // check collision with the floor
        if (CheckCollisionRecs(player.hitbox, floorHitbox)) {
            player.hitbox.y = floorHitbox.y - player.hitbox.height;
            velocityY = 0.0f;
            player.canJump = true;
        } else {
            player.canJump = false;
        }

		// drawing
		BeginDrawing();

		// drawing scene
		DrawTexture(backgroundTexture, 0, 0, WHITE);
		DrawRectangleRec(floorHitbox, WHITE);
		DrawTexture(floorTexture, 0, SCREEN_HEIGHT - floorTexture.height, WHITE);
		
		// drawing door
		DrawTexture(doorTexture, door.hitbox.x, door.hitbox.y, WHITE);

		// ball drawing ball
		DrawTexture(ballTexture, player.hitbox.x, player.hitbox.y, WHITE);

		
		if (CheckCollisionRecs(player.hitbox, door.hitbox)) {
            DrawText("Collided", 5, 5, 25, BLACK);  
		}

		EndDrawing();
	}

	// cleanup
	UnloadTexture(backgroundTexture);
	UnloadTexture(floorTexture);
	UnloadTexture(ballTexture);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
