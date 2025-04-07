#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight){
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updataAnimData(AnimData data, float deltaTime, int maxFrame){
    // Update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime){
        data.runningTime = 0.0;
        // Update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame)
            data.frame = 0;
    }
    return data;
}

int main(){
    // Set window 
    int windowDimensions[2]{512, 380};
    
    // Rectangle velocity
    int const jumpVelocity{-600};
    int velocity{0};

    // Acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};

    // Number of obstacles
    const int sizeOfNebulae{6};

    // Initialize new window
    InitWindow(windowDimensions[0], windowDimensions[1], "Runner");

    // Setup obstacle
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    AnimData nebulae[sizeOfNebulae]{};

    for(int i = 0; i < sizeOfNebulae; i++){
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.width/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
        nebulae[i].pos.x = windowDimensions[0] + i * 300;
    }

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
        if(isOnGround(scarfyData, windowDimensions[1])){
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
        for (int i = 0; i < sizeOfNebulae; i++)
            nebulae[i].pos.x += nebVel * deltaTime;

        // Update character position
        scarfyData.pos.y += velocity * deltaTime;

        // Update character animation frame
        if(!isInAir)
            scarfyData = updataAnimData(scarfyData, deltaTime, 5);

        // Update obstacle animation frame
        for(int i = 0; i < sizeOfNebulae; i++)
            nebulae[i] = updataAnimData(nebulae[i], deltaTime, 7);

        // Draw Obstacles
        for(int i = 0; i < sizeOfNebulae; i++)
              DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);

        // Draw Character
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}