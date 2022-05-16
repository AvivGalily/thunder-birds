#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include "io_utils.h"
#include "utils.h"

using namespace std;


struct Board
{
	enum { MAX_HIGHT = 25, MAX_WIDTH = 81, BOARD_COLOR = 5};
	char board[MAX_HIGHT][MAX_WIDTH] = { Keys::emptyCh };
	int ghostCounter, blocksCounter, ROWS, COLS, shipsCounter;

	Board() : ghostCounter(0), blocksCounter(0), shipsCounter(0), ROWS(0), COLS(0) {} //ctor
	char get(int x, int y) const { return board[y][x]; }
	void set(int x, int y, char ch) { board[y][x] = ch; }
	void changeLife(char life) { board[1][76] = life; }
	void changeBoardNum(char boardNum) { board[1][66] = boardNum; }
	bool isWall(int x, int y);
	void printBoard(int* colorsFlag); 
	int findHowManyBlocks();
	void deleteBlockFromBoard(int row, int col, char ch, char board[][MAX_WIDTH]);

};

#endif