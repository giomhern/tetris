#include "game.h"
#include "grid.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
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
    currBlock.Draw(11, 11);
    switch(nextBlock.id){
        case 3:
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
        default:
            nextBlock.Draw(270, 270);
            break;
    }
}

void Game::HandleInput(){
    int keyPress = GetKeyPressed();
    if(gameOver && keyPress != 0){
        gameOver = false;
        Reset();
    }
    switch(keyPress){
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1);
            break;
        case KEY_UP:
            RotateBlock();
            break;
        
    }
}


void Game::MoveBlockLeft(){
    if (!gameOver){
        currBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false){
            currBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight(){
    if (!gameOver){
        currBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false){
            currBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown(){
    if (!gameOver){
        currBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false){
            currBlock.Move(-1, 0);
            LockBlock();
        }
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
    if(!gameOver){
        currBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currBlock.UndoRotation();
        }
    }
}

void Game::LockBlock(){
    vector<Position> tiles = currBlock.GetCellPositions();
    for (Position tile: tiles){
        grid.grid[tile.row][tile.col] = currBlock.id;
    }
    currBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
}

void Game::Reset(){
    grid.Initialize();
    blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints){
    switch(linesCleared){
        case 1:
            score += 100;
            break;
        case 2:
            score += 200;
            break;
        case 3:
            score += 500;
            break;
        default:
            break;
    }
    score += moveDownPoints;
}
