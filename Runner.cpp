#include "raylib.h"

int main(){
    // Set window dimensions
    const int windowHeight{380}, windowWidth{512};

    // Initialize new window
    InitWindow(windowWidth, windowHeight, "Runner");

    // Set frames per second
    SetTargetFPS(60);

    // Game loop
    while(!WindowShouldClose()){
        // Start drawing
        BeginDrawing();

        ClearBackground(WHITE);

        // Stop drawing
        EndDrawing();
    }
    CloseWindow();
}