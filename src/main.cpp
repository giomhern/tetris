#include <raylib.h>
#include "grid.h"
#include "game.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

int main() {
    // Defining colors 
    Color darkBlue = {44, 44, 127, 255};
    LBlock lBlock = LBlock();
    // Game loop 
    // 1. Event handling 
    // 2. Updating positions
    // 3. Drawing objects
    Game game = Game();
    Grid grid = Grid();
    grid.Print();

    InitWindow(300, 600, "Raylib Tetris"); 
    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        game.HandleInput();
        if(EventTriggered(0.2)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        lBlock.Draw();
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
}