#include "raylib.h"
#include <iostream>
#include <cmath>

typedef struct {
    bool hasBlock;
    Color color;
} Cell;

int fallingDelayCounter = 0;
int placedBlocks;
const int threshold = 150;
const int width = 700/10;
const int height = 700/10;
Cell grid[width][height];

Color colors[] = {
    RED, ORANGE, YELLOW, GREEN, BLUE, DARKBLUE, VIOLET
};
int currentColor = 0;

void updateFalling() {
    // Corrected loop to start from width - 1 and height - 2 without skipping the first row and column
    for(int i = 0; i < width; i++){ // Loop through all columns
        for(int j = height - 2; j >= 0; j--){ // Start from the second-to-last row and move upwards
            if(grid[i][j].hasBlock){
                // Downward movement
                if(j < height - 1 && !grid[i][j+1].hasBlock){
                    grid[i][j+1].hasBlock = true;
                    grid[i][j+1].color = grid[i][j].color;
                    grid[i][j].hasBlock = false;
                }
                // Down-right movement
                else if(i < width - 1 && j < height - 1 && grid[i][j+1].hasBlock && !grid[i+1][j+1].hasBlock){
                    grid[i+1][j+1].hasBlock = true;
                    grid[i+1][j+1].color = grid[i][j].color;
                    grid[i][j].hasBlock = false;
                }
                // Down-left movement
                else if(i > 0 && j < height - 1 && grid[i][j+1].hasBlock && !grid[i-1][j+1].hasBlock){
                    grid[i-1][j+1].hasBlock = true;
                    grid[i-1][j+1].color = grid[i][j].color;
                    grid[i][j].hasBlock = false;
                }
            }
        }
    }
}


void UpdateDrawFrame();

int main()
{
    SetTargetFPS(60);

    InitWindow(700, 700, "Titel");
    
    
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++){
            grid[i][j].hasBlock = false;
        }
    }

    while(!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();
}

void UpdateDrawFrame()
{
    if(IsMouseButtonDown( MOUSE_BUTTON_LEFT)) {
        unsigned int i = (int)std::floor(GetMousePosition().x / 10);
        unsigned int j = (int)std::floor(GetMousePosition().y / 10);
        if(i < width && j < height && !grid[i][j].hasBlock)
        {
            grid[i][j].hasBlock = true;
            grid[i][j].color = colors[currentColor];
            placedBlocks++;
            if(placedBlocks >= threshold){
                placedBlocks = 0;
                currentColor = (currentColor + 1) % (sizeof(colors) / sizeof(colors[0]));
            }
        }
    }

    updateFalling();   
    
    BeginDrawing();
        ClearBackground(BLACK);
        for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++){
            int x = i * 10;
            int y = j * 10;
            DrawRectangleLines(x, y, 10, 10, WHITE);
            if(grid[i][j].hasBlock)
            {
                DrawRectangle(x, y, 10, 10, grid[i][j].color);
            }
        }
        }
        
    EndDrawing();
}
