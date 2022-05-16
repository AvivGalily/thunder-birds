#ifndef _SHIPS_H_
#define _SHIPS_H_

#include <cstring>
#include <vector>
#include "Point.h"
#include "utils.h"
#include "board.h"
#include "io_utils.h"

using namespace std;

class Ship
{
	Board* pboard = nullptr;
	enum { SMALL_SHIP_SIZE = 2, SIZE_BIG_SHIP = 4,SMALL_SHIP_COLOR = 7,BIG_SHIP_COLOR = 6};
	vector<Point> body; // BigShip matrix by regular array
	int size = 0;

public:
	void setShipPoint(Board* pb, int x1, int y1, char ch);
	void setBoard(Board* pb);
	void draw(int* colorsFlag);
	bool canMove(int dirx, int diry, int* ghostFlag);
	void move(int difx, int dify, int* ghostFlag);
	Point isPushBlock(int dirx, int diry, int* ghostFlag);
	bool win();
	int GetSmallShipColor() const {return SMALL_SHIP_COLOR;}
	int GetBigShipColor() const { return BIG_SHIP_COLOR; }
	Point getPoint(int idx) const { return (body[idx]); };
	void setPointsSilent();
	bool canPushBlock(int dirx, int diry, int* ghostFlag);

	void setSize(int newSize) { size = newSize; }
	int const getSize() { return size; }

};

#endif