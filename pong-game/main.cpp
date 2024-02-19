#include <iostream>
#include <raylib.h>

using namespace std;


class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, ORANGE);
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
    }
};


class Paddle {
public:
    float x, y;
    int speed;
    int width, height;

    void Draw() {
        DrawRectangle(x, y, width, height, ORANGE);
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
    void Update(int ball_y) {
        if (y + height / 2 > ball_y && (y >= speed)) {
            y -= speed;
        }
        if (y + height / 2 < ball_y && (y <= (GetScreenHeight() - speed - height))) {
            y += speed;
        }
    }
};


Ball ball;
Paddle userPaddle;
CPUPaddle cpuPaddle;


int main() {

    int player_score = 0;
    int cpu_score = 0;

    const int screen_width = 1200;
    const int screen_height = 800;
    const int frame_rate = 60;

    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(frame_rate);

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    userPaddle.height = 120;
    userPaddle.width = 10;
    userPaddle.x = 30;
    userPaddle.y = screen_height / 2 - userPaddle.height / 2;
    userPaddle.speed = 6;

    cpuPaddle.height = 120;
    cpuPaddle.width = 10;
    cpuPaddle.x = screen_width - 30 - cpuPaddle.width;
    cpuPaddle.y = screen_height / 2 - cpuPaddle.height / 2;
    cpuPaddle.speed = 6;

    while (WindowShouldClose() == false) {  // if user hasn't hit Esc or closed the game window
        BeginDrawing();

        ball.Update();
        userPaddle.Update();
        cpuPaddle.Update(ball.y);

        ClearBackground(BLACK);

        // Initialize Game Boundaries and ScoreBoard
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

        ball.Draw();
        userPaddle.Draw();
        cpuPaddle.Draw();

        EndDrawing();
    }
    CloseWindow();

    return 0;
}