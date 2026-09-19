#include <raymob.h>
#include <raymath.h>
#include <string>

int main(void)
{
    InitWindow(0, 0, "raylib [core] example - basic window");
    const int WIDTH = GetScreenWidth();
    const int HEIGHT = GetScreenHeight();

    int joystick_x = 150;
    const int JOYSTICK_X_ORIGIN = 150;
    int joystick_y = HEIGHT-150;
    const int JOYSTICK_Y_ORIGIN = HEIGHT-150;
    const int JOYSTICK_RADIUS = 50.f;

    bool on_joystick = false;

    Vector2 player_position = {(float)WIDTH/2-50/2, (float)HEIGHT/2-50/2};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointCircle(GetMousePosition(), {(float)joystick_x, (float)joystick_y}, JOYSTICK_RADIUS)
        )
        {
            on_joystick = true;
        }

        if (on_joystick)
        {
            joystick_x = Clamp(GetMouseX(), JOYSTICK_X_ORIGIN-25, JOYSTICK_X_ORIGIN+25);
            joystick_y = Clamp(GetMouseY(), JOYSTICK_Y_ORIGIN-25, JOYSTICK_Y_ORIGIN+25);
        }
        
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            joystick_x = 150;
            joystick_y = HEIGHT-150;
            on_joystick = false;
        }

        // Joystick moving player
        player_position.x += (joystick_x - JOYSTICK_X_ORIGIN) * 10 * GetFrameTime();
        player_position.y += (joystick_y - JOYSTICK_Y_ORIGIN) * 10 * GetFrameTime();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawCircleLines(150, HEIGHT-150, JOYSTICK_RADIUS, LIGHTGRAY);
        DrawCircleV({(float)joystick_x, (float)joystick_y}, JOYSTICK_RADIUS-25.f, GRAY);

        std::string joystick_text = "JOYSTICK X: " + std::to_string(joystick_x) + ", Y: " + std::to_string(joystick_y);
        DrawText(joystick_text.c_str(), 20, 20, 20, BLACK);

        DrawRectangleV(player_position, {50, 50}, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}