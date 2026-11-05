/*******************************************************************************************
	*
	*   raylib [core] example - basic window
	*
	*   Example complexity rating: [★☆☆☆] 1/4
	*
	*   NOTE: This example is prepared to compile for PLATFORM_WEB, and PLATFORM_DESKTOP
	*   As you will notice, code structure is slightly diferent to the other examples...
	*   To compile it for PLATFORM_WEB just uncomment #define PLATFORM_WEB at beginning
	*
	*   Example originally created with raylib 1.3, last time updated with raylib 1.3
	*
	*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
	*   BSD-like license that allows static linking with closed source software
	*
	*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
	*
	********************************************************************************************/

#include "raylib.h"

#define PLATFORM_WEB

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
const int screenWidth = 800;
const int screenHeight = 450;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	#if defined(PLATFORM_WEB)
	const int Target_FPS = 30;
	emscripten_set_main_loop(UpdateDrawFrame, Target_FPS, 1);
	#else
	SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		UpdateDrawFrame();
	}
	#endif

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void)
{
	// Update
	float FrameTime = GetFrameTime();
	TraceLog(LOG_INFO, "frame time : %.4f", FrameTime);

	//----------------------------------------------------------------------------------
	// TODO: Update your variables here
	//----------------------------------------------------------------------------------

	int input_x = 0;
	int input_y = 0;
	int accel_x = 0;
	int accel_y = 0;
	int velocity_x = 0;
	int velocity_y = 0;
	for (int i = 0; i < NUM_ENTITY; ++i) {
		int num_accel = HandleAccelInput(FrameTime);
		int velocity = ConsumeAccelInput(num_accel);
		int position = UpdatePosition(velocity);
		positions[i].x = velocity_x;
		positions[i].y = velocity_y;
		rotations[i].value = 1;
	}

	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	EndDrawing();
	//----------------------------------------------------------------------------------
}

#define INPUT_HANDLE_INTERVAL 0.05f
#define ACCEL_MULTIPLER 0.1f

//------------------------------------------------------------------------------------
// Game Data
//------------------------------------------------------------------------------------

struct Position {
	int x;
	int y;
}

struct Rotation {
	int value;
}

struct Entity {
	int ID;
}

#define NUM_ENTITY 3
struct Position positions[NUM_ENTITY];
struct Rotation rotations[NUM_ENTITY];

enum Entity_ID {
	ID_None			= -1,
	ID_Ball 		= 0,
	ID_Paddle_1 = 1,
	ID_Paddle_2 = 2,
}



int HandleAccelInput(float FrameTime) {
	int num_accel = 0;
	float accumulate = 0.f;

	switch (Entity_ID) {
		case ID_None: // you dumbass. 
			break;
		case ID_Ball: //acceleration comes from force.
			//handle Physics!
			
			break;
			
		case ID_Paddle_1: { 	//acceleration comes from input
			//handle input!
			while (accumulate < FrameTime) {
				accumulate += INPUT_HANDLE_INTERVAL;
				if (IsKeyDown(KEY_UP)) num_accel++;
				else if (IsKeyDown(KEY_DOWN)) num_accel--;
			}
		} break;

		case ID_Paddle_2: //acceleration comes from artificial intent!
			//this is where the fun is! let's play with the Player!
			break;
	}


	return num_accel;
}

int ConsumeAccelInput(int num_accel) {

	switch (Entity_ID) {
		case ID_None: // dumbass!
			break;
		case ID_Ball:
			//velocity2D
			break;
		case ID_Paddle_1:
			// only 1-d movement
			int velocity += num_accel * ACCEL_MULTIPLER;
			break;
		case ID_Paddle_2:
			// only 1-d movement
			break;
	}
	

	return velocity;
}

int UpdatePosition(int velocity) {
	switch (Entity_ID) {
		case ID_None: // dumb dumb!
			break;
		case ID_Ball:
			break;
		case ID_Paddle_1:
			break;
		case ID_Paddle_2:
			break;
	}
	int position += velocity;

	return position;
}