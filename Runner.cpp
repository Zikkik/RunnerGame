#include "raylib.h"

int main(){
    // Set window dimensions
    const int windowHeight{380}, windowWidth{512};
    
    // Rectangle dimensions, position and velocity
    int const jumpVelocity{-22};
    int velocity{0};

    // Acceleration due to gravity
    const int gravity{1};

    // Initialize new window
    InitWindow(windowWidth, windowHeight, "Runner");

    // Setup player character
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
        scarfyRec.width = scarfy.width/6;
        scarfyRec.height = scarfy.height;
        scarfyRec.x = 0;
        scarfyRec.y = 0;
    Vector2 scarfyPos;
        scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
        scarfyPos.y = windowHeight - scarfyRec.height;

    // Check if character is in air
    bool isInAir{false};

    // Set frames per second
    SetTargetFPS(60);

    // Game loop
    while(!WindowShouldClose()){
        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Ground check
        if(scarfyPos.y >= windowHeight - scarfyRec.height){
            // Rectangle in on the ground
            velocity = 0;
            isInAir = false;
        }
        else{
            // Apply gravity
             velocity += gravity;
             isInAir = true;
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        // Update position
        scarfyPos.y += velocity;

        // Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}