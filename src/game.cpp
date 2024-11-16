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
    if(IsBlockOutside() || BlockFits() == false){
        currBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight(){
    currBlock.Move(0, 1);
     if(IsBlockOutside() || BlockFits() == false){
        currBlock.Move(0, -1);
    }
}

void Game::MoveBlockDown(){
    currBlock.Move(1, 0);
    if(IsBlockOutside() || BlockFits() == false){
        currBlock.Move(-1, 0);
        LockBlock();
    }
}

bool Game::BlockFits(){
    vector<Position> tiles = currBlock.GetCellPositions();

    for(Position tile: tiles){
        if(grid.IsCellEmpty(tile.row, tile.col) == false){
            return false;
        }
    }

    return true;
}

bool Game::IsBlockOutside()
{
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

void Game::LockBlock(){
    vector<Position> tiles = currBlock.GetCellPositions();
    for(Position tile: tiles){
        grid.grid[tile.row][tile.col] = currBlock.id;
    }
    currBlock = nextBlock;
    nextBlock = GetRandomBlock();
}
