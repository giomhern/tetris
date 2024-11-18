#pragma once 
#include "grid.h"
#include "blocks.cpp"

class Game {
    public:
        Game();
        Grid grid;
        Block GetRandomBlock();
        vector<Block> GetAllBlocks();
        void HandleInput();
        void MoveBlockLeft();
        void MoveBlockRight();
        void MoveBlockDown();
        void Draw();
        bool gameOver;
        int score;

    private:
        bool BlockFits();
        bool IsBlockOutside();
        vector<Block> blocks;
        Block currBlock;
        Block nextBlock;
        void RotateBlock();
        void LockBlock();
        void Reset();
        void UpdateScore(int linesCleared, int MoveDownPoints);
};