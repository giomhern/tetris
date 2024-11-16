#include "game.h"
#include "grid.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock(){
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
};

vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};;
}

void Game::Draw(){
    grid.Draw();
    currBlock.Draw();
}

void Game::HandleInput(){
    int keyPress = GetKeyPressed();
    switch(keyPress){
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            break;
        case KEY_UP:
            RotateBlock();
            break;
        
    }
}


void Game::MoveBlockLeft(){
    currBlock.Move(0, -1);
    if(IsBlockOutside()){
        currBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight(){
    currBlock.Move(0, 1);
     if(IsBlockOutside()){
        currBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown(){
    currBlock.Move(1, 0);
     if(IsBlockOutside()){
        currBlock.Move(-1, 0);
    }
}

bool Game::IsBlockOutside(){
    vector<Position> tiles = currBlock.GetCellPositions();
    for(Position tile: tiles){
        if(grid.IsCellOutside(tile.row, tile.col)){
            return true;
        }
    }

    return false;
}

void Game::RotateBlock(){
    currBlock.Rotate();
    if(IsBlockOutside()){
        currBlock.UndoRotation();
    }
}
