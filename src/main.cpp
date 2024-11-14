#include <raylib.h>
#include "grid.h"

int main() {

    // Defining colors 
    Color darkBlue = {44, 44, 127, 255};

    // Game loop 
    // 1. Event handling 
    // 2. Updating positions
    // 3. Drawing objects
    Grid grid = Grid();
    grid.Print();

    InitWindow(300, 600, "Raylib Tetris"); 
    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(darkBlue);
        grid.Draw();
        EndDrawing();
    } 

    CloseWindow();
}