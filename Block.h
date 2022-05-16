#ifndef _BLOCKS_H_
#define _BLOCKS_H_
#include <vector>

#include "Point.h"
#include "io_utils.h"
#include "utils.h"
#include "board.h"


using namespace std;

class Block
{
	Board* pBoard = nullptr;
	enum { SMALL_BLOCK_SIZE = 2, MAX_SIZE_BIG_BLOCK = 6,BLOCK_COLOR =  14};
	vector<Point> body;
	int size = 0;
	char blockCh;
	int dirx = 0, diry = 0;
	int carry = 0;
	
public:

	void setBlockPoint(Board* pb, int x1, int y1, char ch);
	void setBoardBlock(Board* pb);
	Point getPoint(int idx) const { return (body[idx]); };
	void drawBlock(int* colorsFlag);
	bool isFallBlock();
	char whichCharBelowBlock();
	bool isWallBelow();
	void moveBlock(int difx, int dify);
	bool canMoveBlock(int difx, int dify, int* totalBlocksSize);
	int whatSize() const { return size; }
	int  GetColor() const { return BLOCK_COLOR; };
	Point isPushBlock(int dirx, int diry);
	void setPointsSilent();

	char const getBlockCh() { return blockCh; }
	void setBlockCh(char ch) { blockCh = ch; }
	int const getDirX() { return dirx; }
	int const getDirY() { return diry; }
	void setDirX(int newDir) { dirx = newDir; }
	void setDirY(int newDir) { diry = newDir; }
	int const getCarry() { return carry; }
	void setCarry(int newCarry) { carry = newCarry; }


};

#endif

