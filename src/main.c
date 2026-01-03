#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

// Physical Constants
#define ELASTIC_CONSTANT 0.8
#define REST_LENGTH 150

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
int main(void)
{
    InitWindow(WIDTH, HEIGHT, "Physics with Raylib");
    SetTargetFPS(FPS);
    CenterOfMass square = {
        .position = {100, 300},
        .velocity = {0, 0},
        .acceleration = {0, 0},
        .mass = 1.0f};
    float squareSize = 100;
    Vector2 restPosition = {REST_LENGTH, 300};
    Vector2 lineOffset = {0, squareSize/2};

    // Mass on spring example
    while (!WindowShouldClose())
    {
        BeginDrawing();
        DrawFPS(10, 10);
        updatePhysics(&square);
        DrawRectangle(square.position.x, square.position.y, squareSize, squareSize, MAROON);
        DrawLineEx(Vector2Add(square.position,lineOffset), Vector2Add(restPosition, lineOffset), 6, LIGHTGRAY);
        ClearBackground(BLACK);
        DrawText("Mass on a Spring", 400 - 100, 100, 24, DARKGREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}