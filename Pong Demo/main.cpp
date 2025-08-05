/*
* A simple Pong game demo using only C++ and raylib.
* This code is a basic implementation of Pong with a player paddle, a CPU paddle, and a ball.
* The player can control their paddle using the W and S keys, while the CPU paddle follows the ball.
* The game keeps track of the player and CPU scores, and resets the ball when it goes out of bounds.
* To compile this code, you need to have raylib installed and linked properly.
* 
* This code is provided as a starting point for a Pong game and can be extended with additional features such as menus, sound effects, and more complex AI for the CPU paddle.
* Author: Zachary Bram
*/


#include <iostream>
#include "raylib.h"

using namespace std;


int player_score = 0;
int cpu_score = 0;

//NOTE: Add a class for menus later on
class Ball {
public:
	float x, y;
	float speed_x, speed_y;
	int radius;

	void Draw() {
		//Pong Ball
		DrawCircle(x, y, radius, WHITE);
	}

	void Update() {
		x += speed_x;
		y += speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0)
		{
			speed_y *= -1; // Reverse direction on Y axis
			speed_y > 0 ? speed_y++ : speed_y--; // Increase speed slightly on bounce
		}
		if (x + radius >= GetScreenWidth()) {
			player_score++;
			ResetBall(); // Reset ball position and speed
		}
		if (x - radius <= 0) {
			cpu_score++;
			ResetBall(); // Reset ball position and speed
		}
	}
	void ResetBall() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		speed_x = 5; // Reset speed in x direction
		speed_y = 5; // Reset speed in y direction


		int speed_choices[2] = { -1, 1 };
		speed_x *= speed_choices[GetRandomValue(0, 1)]; // Randomly choose direction
		speed_y *= speed_choices[GetRandomValue(0, 1)]; // Randomly choose direction

	}
};

class Paddle {
public:
	float x, y;
	float width, height;
	int speed;
	Color color;

	void Draw() {
		DrawRectangle(x, y, width, height, color);
	}

	void Update() {
		if (IsKeyDown(KEY_W) && y >= 0) {
			y -= speed; //Move up
		}
		if (IsKeyDown(KEY_S) && y + height <= GetScreenHeight()) {
			y += speed; //Move down
		}
		if (IsKeyDown(KEY_UP) && y >= 0) {
			y -= speed; //Move up
		}
		if (IsKeyDown(KEY_DOWN) && y + height <= GetScreenHeight()) {
			y += speed; //Move down
		}
	}

};

class CpuPaddle : public Paddle {
public:
	void Update(int ball_y) {
		if (y + height / 2 > ball_y) {
			y -= speed; // Move up if ball is above paddle
		}
		else if (y + height / 2 < ball_y) {
			y += speed;
		}
	}
};





Ball ball;
Paddle playerPaddle;
CpuPaddle cpuPaddle;



int main()
{
	const int screenWidth = 1280;
	const int screenHeight = 720;

	InitWindow(screenWidth, screenHeight, "Pong Demo");

	SetTargetFPS(60);

	ball.radius = 15;
	ball.x = screenWidth / 2;
	ball.y = screenHeight / 2;
	ball.speed_x = 5; // Speed in x direction
	ball.speed_y = 5; // Speed in y direction


	//Initialize left paddle
	playerPaddle.x = 50;
	playerPaddle.y = screenHeight / 2 - 50; // Center paddle vertically
	playerPaddle.width = 20;
	playerPaddle.height = 120; 
	playerPaddle.speed = 10; 
	playerPaddle.color = BLUE;

	//Initialize CPU paddle (if needed)
	cpuPaddle.x = screenWidth - 70; // Right paddle position
	cpuPaddle.y = screenHeight / 2 - 50; // Center paddle vertically
	cpuPaddle.width = 20;
	cpuPaddle.height = 120;
	cpuPaddle.speed = 10;
	cpuPaddle.color = WHITE;
	

	//MAIN GAME LOOP
	while (!WindowShouldClose()) 
	{
		BeginDrawing();

		ball.Update();
		playerPaddle.Update();
		//rightPaddle.Update();
		cpuPaddle.Update(ball.y);


		//Collision detection
		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{playerPaddle.x, playerPaddle.y, playerPaddle.width, playerPaddle.height}))
		{
			ball.speed_x *= -1; // Reverse direction on X axis
			ball.speed_x > 0 ? ball.speed_x++ : ball.speed_x--; // Increase speed slightly on bounce
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpuPaddle.x, cpuPaddle.y, cpuPaddle.width, cpuPaddle.height }))
		{
			ball.speed_x *= -1; // Reverse direction on X axis
			ball.speed_x > 0 ? ball.speed_x++ : ball.speed_x--; // Increase speed slightly on bounce
		}

		//Center	
		ClearBackground(BLACK);
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, GRAY); 
		ball.Draw();
		cpuPaddle.Draw();
		playerPaddle.Draw();
		DrawText(TextFormat("Player Score:"), 10, 10, 20, WHITE);
		DrawText(TextFormat("%d", player_score), 10, 40, 20, WHITE);
		DrawText(TextFormat("CPU Score:"), screenWidth - 125, 10, 20, WHITE);
		DrawText(TextFormat("%d", cpu_score), screenWidth - 20, 40, 20, WHITE);

		EndDrawing();
	}


	CloseWindow();


	return 0;
}