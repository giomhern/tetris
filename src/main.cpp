#include <raylib.h>
#include "grid.h"
#include "game.h"
#include "colors.h"
#include <iostream>
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
    // Game loop 
    // 1. Event handling 
    // 2. Updating positions
    // 3. Drawing objects
    Game game = Game();
    Grid grid = Grid();
    grid.Print();

    InitWindow(500, 620, "Raylib Tetris"); 
    Font font = LoadFontEx("/fonts/monogram.ttf'", 64, 0, 0);
    SetTargetFPS(60);
    while(WindowShouldClose() == false){
        game.HandleInput();
        if(EventTriggered(0.2)){
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {350, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {360, 175}, 38, 2, WHITE);
        if(game.gameOver){
            DrawTextEx(font, "GAME OVER", {320, 450}, 28, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);
        char scoreText[10];
        snprintf(scoreText, sizeof(game.score), "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();
        EndDrawing();
    }
    CloseWindow();
}