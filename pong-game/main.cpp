#include <iostream>
#include <raylib.h>

using namespace std;

int main() {

    cout << "starting my game yeah!" << endl;
    const int screen_width = 1200;
    const int screen_height = 800;
    const int frame_rate = 60;
    const int ball_radius = 15;
    const int paddle_length = 120;
    const int paddle_thickness = 10;
    const int paddle_offset = 30;
    const int paddle_y = screen_height / 2 - paddle_length / 2;

    InitWindow(screen_width, screen_height, "My Pong Game!");
    SetTargetFPS(frame_rate);

    while (WindowShouldClose() == false) {  // if user hasn't hit Esc or closed the game window
        BeginDrawing();

        // Initialize Ball and Paddles
        DrawCircle(screen_width / 2, screen_height / 2, ball_radius, ORANGE);
        DrawRectangle(paddle_offset, paddle_y, paddle_thickness, paddle_length, ORANGE);
        DrawRectangle(screen_width - paddle_offset - paddle_thickness, paddle_y, paddle_thickness, paddle_length, ORANGE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}