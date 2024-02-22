#include "raylib.h"
#include <iostream>
#include <cmath>

int fallingDelayCounter = 0;
const int width = 700/10;
const int height = 700/10;
int grid[width][height];
void updateFalling() {
    for(int i = width; i > 0; i--){
        for(int j = height; j > 0; j--){
            int state = grid[i][j];
            if(state == 1){
                if(j < height - 1 && grid[i][j+1] != 1){
                    grid[i][j+1] = 1;
                    grid[i][j] = 0;
                    break;
                }
                else if(grid[i][j+1] == 1 && grid[i+1][j+1] == 0)
                {
                    grid[i+1][j+1] = 1;
                    grid[i][j] = 0;
                    break;
                }
                else if(grid[i][j+1] == 1 && grid[i-1][j+1] == 0)
                {
                    grid[i-1][j+1] = 1;
                    grid[i][j] = 0;
                    break;
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
            grid[i][j] = 0;
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
        if(!(i > 700 || j > 700))
        {
            grid[i][j] = 1;
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
            if(grid[i][j] == 1)
            {
                DrawRectangle(x, y, 10, 10, WHITE);
            }
        }
        }
        
    EndDrawing();
}
