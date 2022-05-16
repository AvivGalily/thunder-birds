#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"
#include "utils.h"
#include "board.h"


class Point
{
	int x, y;
	char ch;
	Board* pBoard = nullptr;
	bool silent = false; 

public:
	Point() {}  // empty C'tor
	Point(int x1, int y1, char c) : x(x1), y(y1), ch(c) {} // C'tor
	bool operator==(const Point& p2) const { return x == p2.x && y == p2.y && ch == p2.ch; }
	//bool operator=(const Point& p2) const { return x == p2.x && y == p2.y && ch == p2.ch; }
	void setBoard(Board* pb);
	//void ChengeSilentMode() { if (silent == false) { silent = true; } else { silent = false; } }
	void setPoint(int x, int y, char ch);
	void draw() const;
	void draw(char ch);
	void del() const;
	int getx() const { return x; }
	int gety() const { return y; }
	char getch() const { return ch; }

	char checkNextCh(int dirx, int diry);
	void move(int difx, int dify);
	void setSilent(bool silentFlag) { silent = silentFlag; }
};

#endif
