#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <raylib.h>
#include <raymath.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 120

// Physical Constants
#define ELASTIC_CONSTANT 0.8
#define REST_LENGTH 400

typedef struct
{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;
} CenterOfMass;

// Physics
Vector2 calculateResultantForce(CenterOfMass *particle)
{
    Vector2 restPosition = {REST_LENGTH, 300};
    Vector2 elasticForce = Vector2Scale(Vector2Subtract(particle->position, restPosition), -ELASTIC_CONSTANT);
    return elasticForce;
}

void updatePhysics(CenterOfMass *particle)
{
    float time = GetFrameTime();
    particle->acceleration = Vector2Scale(calculateResultantForce(particle), 1 / particle->mass);
    particle->velocity = Vector2Add(particle->velocity, Vector2Scale(particle->acceleration, time));
    particle->position = Vector2Add(particle->position, Vector2Scale(particle->velocity, time));
}

// Render
void drawSpring(Vector2 start, Vector2 end)
{
    const int numberOfLines = 15;
    const float length = 40.0f;

    Vector2 springAxis = Vector2Subtract(end, start);
    float totalDistance = Vector2Length(springAxis);
    float horizontalSteps = totalDistance/(numberOfLines -1);

    Vector2 unitSpringAxis = Vector2Scale(springAxis, 1.0f/totalDistance);
    Vector2 orthoAxis = { -unitSpringAxis.y, unitSpringAxis.x };

    Vector2 currentPos = start;
    Vector2 nextPos;

    for(int i=0; i< numberOfLines; i++){
        float actualStep = (i == 0 || i == numberOfLines -1) ? horizontalSteps/2.0f : horizontalSteps; 
        float actualLength = (i == 0 || i == numberOfLines -1) ? length/2.0f : length; 
        float currentHeight = sqrtf(powf(actualLength, 2) - powf(actualStep,2));
        int downOrUp = i%2 == 0 ? 1 : -1;

        //Deslocation along the axis 
        nextPos = Vector2Add(currentPos, Vector2Scale(unitSpringAxis, actualStep));
        // Deslocation perpendicular to the axis, except in the end
        Vector2 visualTarget = nextPos;
        if(i < numberOfLines - 1)
        {
            visualTarget = Vector2Add(nextPos, Vector2Scale(orthoAxis, currentHeight*downOrUp));
        } else {
            visualTarget = end;
        }
        DrawLineV(currentPos, visualTarget, LIGHTGRAY);
        currentPos = visualTarget;
    }
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Physics with Raylib");
    SetTargetFPS(FPS);
    CenterOfMass square = {
        .position = {600, 300},
        .velocity = {0, 0},
        .acceleration = {0, 0},
        .mass = 1.0f};
    float squareSize = 100;
    Vector2 restPosition = {REST_LENGTH, 300};
    Vector2 springOffSet = {-220, squareSize/2};
    Vector2 springEndOffSet = {0, squareSize/2};

    // Mass on spring example
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawFPS(10, 10);
        updatePhysics(&square);
        DrawRectangle(square.position.x, square.position.y, squareSize, squareSize, MAROON);
        drawSpring(Vector2Add(restPosition, springOffSet), Vector2Add(square.position, springEndOffSet));
        ClearBackground(BLACK);
        DrawText("Mass on a Spring", 400 - 100, 100, 24, DARKGREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}