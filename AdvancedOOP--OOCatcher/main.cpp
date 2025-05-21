#include "body.h"
#include "raylib.h"
#include <cmath>
#include "config.h"

// Mapping simulation coords to screen
int mapX(double x) { return static_cast<int>(x * scale); }
int mapY(double y) { return screenHeight - static_cast<int>(y * scale); }

enum class BallState { Thrown, Returning };

int main() {
    InitWindow(screenWidth, screenHeight, "OOCatcher - Triangle Based Body");
    SetTargetFPS(60);

    body dancer(7, 13, 2);  // Legs on ground
    BallState state = BallState::Thrown;
    bool isPaused = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) isPaused = !isPaused;
        if (IsKeyPressed(KEY_ESCAPE)) break;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!isPaused) {
            if (state == BallState::Thrown) {
                dancer.animate_throw();
                if (dancer.ball.get_x() > 25)
                    state = BallState::Returning;
            } else {
                dancer.animate_catch();
                if (dancer.can_grab(dancer.ball, 1.5))
                    state = BallState::Thrown;
            }
        }

        // Draw ground
        DrawLine(0, mapY(0), screenWidth, mapY(0), GRAY);

        // Body segments
        for (const auto& seg : dancer.limbs)
            DrawLine(mapX(seg->get_x()), mapY(seg->get_y()),
                     mapX(seg->end_x()), mapY(seg->end_y()), BLACK);

        // Fingers
        for (const auto& f : dancer.fingers)
            DrawLine(mapX(f->get_x()), mapY(f->get_y()),
                     mapX(f->end_x()), mapY(f->end_y()), DARKGRAY);

        // Toes
        for (const auto& t : dancer.toes)
            DrawLine(mapX(t->get_x()), mapY(t->get_y()),
                     mapX(t->end_x()), mapY(t->end_y()), DARKGRAY);

        // Head (larger + more transparent)
        float head_radius = 32;
        DrawCircle(mapX(dancer.head_center.get_x()), mapY(dancer.head_center.get_y()),
                   head_radius, Fade(GRAY, 0.15f));

        // Ball
        DrawCircle(mapX(dancer.ball.get_x()), mapY(dancer.ball.get_y()), 6, BLUE);

        // UI
        DrawText(state == BallState::Thrown ? "Throwing..." : "Catching...", 20, 20, 20, MAROON);
        DrawText(isPaused ? "[PAUSED] Press SPACE to resume" : "Press SPACE to pause", 20, 50, 18, DARKBLUE);
        DrawText("Press ESC to exit", 20, 80, 16, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
