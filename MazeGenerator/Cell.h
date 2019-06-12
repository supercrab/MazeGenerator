#ifndef Cell_H
#define Cell_H

class Cell{

private:
	bool _walls[4];
	int _column;
	int _row;

public:
	Cell();

	int column();
	int row();

	void setRow(int r);
	void setColumn(int c);
	void setWall(int, bool v);

	bool hasAllWalls();
	void knockDownWall(class Cell* c);
	int findAdjacentWall(class Cell* c);
	int getRandomWall();
	bool wall(int d);

	void draw();
};

#endif