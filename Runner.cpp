#include "raylib.h"

int main(){
    // Set window dimensions
    const int windowHeight{380}, windowWidth{512};
    
    // Rectangle dimensions, position and velocity
    const int width{50}, height{80}, jumpVelocity{-22};
    int posY{windowHeight - height}, velocity{0};

    // Acceleration due to gravity
    const int gravity{1};

    // Check if character is in air
    bool isInAir{false};


    // Initialize new window
    InitWindow(windowWidth, windowHeight, "Runner");

    // Set frames per second
    SetTargetFPS(60);

    // Game loop
    while(!WindowShouldClose()){
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Ground check
        if(posY >= windowHeight - height){
            // Rectangle in on the ground
            velocity = 0;
            isInAir = false;
        }
        else{
            // Apply gravity
             velocity += gravity;
             isInAir = true;
        }

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        // Update position
        posY += velocity;

        // Stop drawing
        EndDrawing();
    }
    CloseWindow();
}