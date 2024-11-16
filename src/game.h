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

    private:
        bool IsBlockOutside();
        vector<Block> blocks;
        Block currBlock;
        Block nextBlock;
        void RotateBlock();
};