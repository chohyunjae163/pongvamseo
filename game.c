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
// Game Data
//------------------------------------------------------------------------------------


#define INPUT_HANDLE_INTERVAL 0.05f
#define ACCEL_MULTIPLER 0.1f

struct Entity {
	int ID;
};

enum Entity_ID {
	ID_None			= -1,
	ID_Ball 		= 0,
	ID_Paddle_1 = 1,
	ID_Paddle_2 = 2,
	NUM_Entity = 3,
};

bool	current_entities_alive[NUM_Entity];

Vector2 current_velocity[NUM_Entity];
Vector2 current_positions[NUM_Entity];


void HandlePlayerInput();
Vector2 HandleAccelInput(enum Entity_ID Entity, float FrameTime);
Vector2 ConsumeAccelInput(enum Entity_ID Entity,Vector2 Acceleration);
Vector2 UpdatePosition(enum Entity_ID Entity,Vector2 Velocity);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	current_entities_alive[ID_Paddle_1] = true;

	current_positions[ID_Ball].x = screenWidth / 2.0f;
	current_positions[ID_Ball].y = screenHeight / 2.0f;
	current_positions[ID_Paddle_1].x = 100.0f;
	current_positions[ID_Paddle_1].y = screenHeight / 2.0f;
	current_positions[ID_Paddle_2].x = screenWidth - 100.0f;
	current_positions[ID_Paddle_2].y = screenHeight / 2.0f;


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

	for (int i = 0; i < NUM_Entity; ++i) {
		enum Entity_ID entity = i;

		if (current_entities_alive[entity] == false) continue;


		Vector2 acceleration = HandleAccelInput(entity,FrameTime);
		Vector2 add_velocity = ConsumeAccelInput(entity,acceleration);
		current_velocity[entity].x += add_velocity.x;
		current_velocity[entity].y += add_velocity.y;

		Vector2 add_position = UpdatePosition(entity,current_velocity[entity]);
		current_positions[entity].x += add_position.x;
		current_positions[entity].y += add_position.y;
		TraceLog(LOG_INFO, "current_positions y : %.4f", current_positions[entity].y);
	}	

	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	EndDrawing();
	//----------------------------------------------------------------------------------
}

bool bMoveUp = false;
bool bMoveDown = false;
void HandlePlayerInput() {
	bMoveUp = IsKeyDown(KEY_UP);
	bMoveDown = IsKeyDown(KEY_DOWN);
}

float accumulate = 0.0f;

Vector2 HandleAccelInput(enum Entity_ID Entity,float FrameTime) {
	Vector2 acceleration = { 0 };

	switch (Entity) {
		case ID_None: // you dumbass. 
			break;
		case ID_Ball: //acceleration comes from force.
			//handle Physics!
			
			break;
			
		case ID_Paddle_1: { 	//acceleration comes from input
			//handle input!
			accumulate += FrameTime;
			while (accumulate > INPUT_HANDLE_INTERVAL) {
				accumulate -= INPUT_HANDLE_INTERVAL;
				if (bMoveUp) acceleration.y += 1.0f;
				else if (bMoveDown) acceleration.y -= 1.0f;
			}
		} break;

		case ID_Paddle_2: //acceleration comes from artificial intent!
			//this is where the fun is! let's play with the Player!
			break;
		default:
			break;
	}

	return acceleration;
}

Vector2 ConsumeAccelInput(enum Entity_ID Entity,Vector2 Acceleration) {

	Vector2 velocity = { 0 };
	switch (Entity) {
		case ID_None: // dumbass!
			break;
		case ID_Ball:
			//velocity2D
			break;
		case ID_Paddle_1:
			// only 1-d movement
			velocity.y += Acceleration.y * ACCEL_MULTIPLER;
			break;
		case ID_Paddle_2:
			// only 1-d movement
			break;
		default:
			break;
	}

	return velocity;
}

Vector2 UpdatePosition(enum Entity_ID Entity,Vector2 Velocity) {
	Vector2 position = { 0 };
	switch (Entity) {
		case ID_None: // dumb dumb!
			break;
		case ID_Ball:
			break;
		case ID_Paddle_1:
			position.y += Velocity.y;
			break;
		case ID_Paddle_2:
			break;
		default:
			break;
	}
	
	return position;
}
