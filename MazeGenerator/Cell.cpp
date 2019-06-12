#include "stdafx.h"

#include "Cell.h"
#include "Maze.h"

// Constructor - set all walls
Cell::Cell() {
	memset(_walls, 1, sizeof _walls);
}

// Cell column property
int Cell::column(){
	return _column;
}
void Cell::setColumn(int c){
	_column = c;
}

// Cell row property
int Cell::row(){
	return _row;
}
void Cell::setRow(int r){
	_row = r;
}

// Wall property
bool Cell::wall(int d){
	return _walls[d];
}

void Cell::setWall(int d, bool v){
	_walls[d] = v;
}

// Does the cell have 4 walls
bool Cell::hasAllWalls(){
	for (int i = 0; i < 4; i++){
		 if (_walls[i] == 0)
			 return false;
	}
	return true;
}

// Knock down a wall
void Cell::knockDownWall(class Cell* theCell){

	// find adjacent wall
	int theWallToKnockDown = findAdjacentWall(theCell);
	_walls[theWallToKnockDown] = false;
	int oppositeWall = (theWallToKnockDown + 2) % 4;
	theCell->setWall(oppositeWall, false);
}

// Find the adjacent wall
int Cell::findAdjacentWall(class Cell* theCell){
	if (theCell->column() == _column) {
		if (theCell->row() < _row)
			return 0;
		else
			return 2;
	}
	else {
		// _rows are the same
		if (theCell->column() < _column)
			return 1;
		else
			return 3;
	}
}

// Draw cell
void Cell::draw(){

}