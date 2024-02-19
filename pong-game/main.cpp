#include <iostream>
#include <raylib.h>

using namespace std;


int PLAYER_SCORE = 0;
int CPU_SCORE = 0;
int TARGET_SCORE = 5;


class Ball {
public:
    float x, y;
    float speed_x, speed_y;
    float radius;

    void Draw() {
        DrawCircle(x, y, radius, DARKBLUE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
        }

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }


        if (x <= radius) {
            CPU_SCORE++;
            reset();
        }
        if (x >= GetScreenWidth() - radius) {
            PLAYER_SCORE++;
            reset();
        }
    }

    void reset() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speedChoices[] = { 1, 1 };
        speed_x *= speedChoices[GetRandomValue(0, 1)];
        speed_y *= speedChoices[GetRandomValue(0, 1)];
    }
};


class Paddle {
public:
    float x, y;
    float speed;
    float width, height;

    void Draw() {
        DrawRectangleRounded({ x, y, width, height }, 0.8, 0, ORANGE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP) && (y >= speed)) {
            y -= speed;
        }

        if (IsKeyDown(KEY_DOWN) && (y <= (GetScreenHeight() - speed - height))) {
            y += speed;
        }
    }

};


class CPUPaddle: public Paddle {
public:
    void Update(float ball_y) {
        if (y + height / 2 > ball_y && (y >= speed)) {
            y -= speed;
        }
        if (y + height / 2 < ball_y && (y <= (GetScreenHeight() - speed - height))) {
            y += speed;
        }
    }
};


Ball ball;
Paddle player;
CPUPaddle cpu;


int main() {

    const int screen_width = 1200;
    const int screen_height = 800;
    const int frame_rate = 60;

    InitWindow(screen_width, screen_height, "Diondra's Pong Game");
    SetTargetFPS(frame_rate);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.height = 120;
    player.width = 20;
    player.x = 15;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    cpu.height = 120;
    cpu.width = 20;
    cpu.x = screen_width - 15 - cpu.width;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    while (WindowShouldClose() == false && CPU_SCORE < TARGET_SCORE && PLAYER_SCORE < TARGET_SCORE) {
        BeginDrawing();

        // Update with new locations
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Check for collisions
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height })) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height })) {
            ball.speed_x *= -1;
        }

        ClearBackground(BLACK);

        // Initialize game boundaries and scoreboard
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        DrawText(TextFormat("%i", PLAYER_SCORE), GetScreenWidth() * .25 - 20, 0, 80, WHITE);
        DrawText(TextFormat("%i", CPU_SCORE), GetScreenWidth() * .75, 0, 80, WHITE);

        ball.Draw();
        player.Draw();
        cpu.Draw();

        EndDrawing();
    }

    while (WindowShouldClose() == false) {
        EndDrawing();
        ClearBackground(BLACK);

        if (PLAYER_SCORE == TARGET_SCORE) {
            BeginDrawing();
            DrawText("YOU WIN!", GetScreenWidth() / 2 - 200, GetScreenHeight() / 2, 100, WHITE);
        }

        if (CPU_SCORE == TARGET_SCORE) {
            BeginDrawing();
            DrawText("YOU LOSE", GetScreenWidth() / 2 - 200 - 25, GetScreenHeight() / 2, 100, WHITE);
        }
    }

    CloseWindow();

    return 0;
}