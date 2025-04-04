#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main(){
    // Set window 
    int windowDimensions[2]{512, 380};
    
    // Rectangle velocity
    int const jumpVelocity{-600};
    int velocity{0};

    // Acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    // Initialize new window
    InitWindow(windowDimensions[0], windowDimensions[1], "Runner");

    // Setup obstacle
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8},    // Rectangle rec
        {windowDimensions[0], windowDimensions[1] - nebula.height/8},  // Vector2 pos
        0,                                              // int frame
        1.0 / 12.0,                                     // float updateTime
        0.0                                             // float runningTime
    };

    Texture2D nebula2 = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData neb2Data{
        {0.0, 0.0, nebula2.width/8, nebula2.height/8},            // Rectangle rec
        {windowDimensions[0] + 300, windowDimensions[1] - nebula2.height/8},    // Vector2 pos
        0,                                                      // int frame
        1.0 / 16.0,                                             // float updateTime
        0.0                                                     // float runningTime
    };

    AnimData nebulae[2]{nebData, neb2Data};

    // Obstacle X velocity
    int nebVel{-200};

    // Setup player character
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.frame = 0;
    scarfyData.runningTime = 0.0;

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
        if(scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height){
            // Rectangle in on the ground
            velocity = 0;
            isInAir = false;
        }
        else{
            // Apply gravity
             velocity += gravity * deltaTime;
             isInAir = true;
        }

        // Jump check
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVelocity;

        // Update obstacle position
        nebulae[0].pos.x += nebVel * deltaTime;

        // Update obstacle position
        nebulae[1].pos.x += nebVel * deltaTime;

        // Update character position
        scarfyData.pos.y += velocity * deltaTime;

        // Update character animation frame
        if(!isInAir){
            // Update running time
            scarfyData.runningTime += deltaTime;
            if(scarfyData.runningTime >= scarfyData.updateTime){
                scarfyData.runningTime = 0.0;
    
                // Update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if(scarfyData.frame > 5)
                    scarfyData.frame = 0;
            }
        }

        // Update obstacle animation frame
        nebulae[1].runningTime += deltaTime;
        if(nebulae[1].runningTime >= nebulae[1].updateTime){
            nebulae[1].runningTime = 0.0;

            nebulae[1].rec.x =  nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if(nebulae[1].frame > 7){
                nebulae[1].frame = 0;
            }
        }

        nebulae[0].runningTime += deltaTime;
        if(nebulae[0].runningTime >= nebulae[0].updateTime){
            nebulae[0].runningTime = 0.0;

            nebulae[0].rec.x =  nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if(nebulae[0].frame > 7){
                nebulae[0].frame = 0;
            }
        }

        // Draw Obstacle
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

        // Draw Obstacle
        DrawTextureRec(nebula2, nebulae[1].rec, nebulae[1].pos, RED);

        // Draw Character
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);


        // Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}