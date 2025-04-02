#include "raylib.h"

int main(){
    // Set window dimensions
    const int windowHeight{380}, windowWidth{512};
    
    // Rectangle velocity
    int const jumpVelocity{-600};
    int velocity{0};

    // Acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    // Initialize new window
    InitWindow(windowWidth, windowHeight, "Runner");

    // Setup obstacle
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // Obstacle animation variables
    int nebFrame{};
    const float nebUpdateTime{1.0/12.0};
    float nebRunningTime{};

    // Obstacle X velocity
    int nebVel{-200};

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

    // Animation frame
    int animationFrame{};

    // Amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    float runningTime{};

    // Check if character is in air
    bool isInAir{false};

    // Set frames per second 
    SetTargetFPS(60);

    // Game loop
    while(!WindowShouldClose()){
        // Delta Time
        float const deltaTime{GetFrameTime()};

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
             velocity += gravity * deltaTime;
             isInAir = true;
        }

        // Draw Obstacle
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // Draw Character
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        // Update obstacle position
        nebPos.x += nebVel * deltaTime;

        // Update character position
        scarfyPos.y += velocity * deltaTime;

        // Update character animation frame
        if(!isInAir){
            // Update running time
            runningTime += deltaTime;
            if(runningTime >= updateTime){
                runningTime = 0.0;
    
                // Update animation frame
                scarfyRec.x = animationFrame * scarfyRec.width;
                animationFrame++;
                if(animationFrame > 5)
                    animationFrame = 0;
            }
        }

        // Update obstacle animation frame
        nebRunningTime += deltaTime;
        if(nebRunningTime >= nebUpdateTime){
            nebRunningTime = 0.0;

            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if(nebFrame > 7){
                nebFrame = 0;
            }
        }

        // Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}