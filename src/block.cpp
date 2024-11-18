#include "block.h"

Block::Block(){
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    colOffset = 0;
}

void Block::Draw(int offsetX, int offsetY){
    vector<Position> tiles = GetCellPositions();
    for (Position tile: tiles)
    {
        DrawRectangle(tile.col * cellSize + offsetX, tile.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int cols){
    rowOffset += rows;
    colOffset += cols;
}

vector<Position> Block::GetCellPositions(){
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;

    for(Position tile: tiles){
        Position newPos = Position(tile.row + rowOffset, tile.col + colOffset);
        movedTiles.push_back(newPos);
    }

    return movedTiles;
}

void Block::Rotate(){
    rotationState++;
    if(rotationState == (int)cells.size()){
        rotationState = 0;
    }
}


void Block::UndoRotation(){
    rotationState--;
    if (rotationState == -1){
        rotationState = cells.size() - 1;
    }
    
}