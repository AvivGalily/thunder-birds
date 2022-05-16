#include "Block.h"

void Block::setBlockPoint(Board* pb, int x1, int y1, char ch)  // set blocks points
{
	body.push_back(Point(x1, y1, ch));
	setBoardBlock(pb);

	size++;
	blockCh = ch;
	body.resize(size);
}

void Block::setBoardBlock(Board* pb) // set the blocks on the board
{
	int blockSize = body.size();

	for (int i = 0; i < blockSize; i++)
		body[i].setBoard(pb);

	pBoard = pb;
}


void Block::drawBlock(int* colorsFlag)  // draw function
{
	int blockSize = body.size();

	if (*colorsFlag)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLOCK_COLOR);


	for (int i = 0; i < blockSize; i++)
		body[i].draw();
}


bool Block::isFallBlock()  //checks if block is falling 
{
	int blockSize = body.size();
	
	for (int i = 0; i < blockSize; i++)
	{
		int new_x = body[i].getx();
		int new_y = body[i].gety() + 1;
		char shape = body[i].getch();

		if (pBoard->get(new_x, new_y) != Keys::emptyCh && pBoard->get(new_x, new_y) != shape)
			return false;
		if (pBoard->get(new_x, new_y) == Keys::smallShipCh && blockSize > 2) {return true;}

	}
	
	return true;

}

bool Block::isWallBelow()  // checks if there is a wall below a block
{
	int blockSize = body.size();

	for (int i = 0; i < blockSize; i++)
	{
		int new_x = body[i].getx();
		int new_y = body[i].gety() + 1;
		char tmpCh = pBoard->get(new_x, new_y);

		if (tmpCh == Keys::wallCh) // return ship char
			return true;
	}

	return false;
}


char Block::whichCharBelowBlock()  // checks what kind of char below a block
{
	int blockSize = body.size();

	for (int i = 0; i < blockSize; i++)
	{
		int new_x = body[i].getx();
		int new_y = body[i].gety() + 1;
		char tmpCh = pBoard->get(new_x, new_y);

		
		if (tmpCh == Keys::smallShipCh || tmpCh == Keys::bigShipCh || ('0' <= tmpCh && tmpCh <= '9'))
			if(tmpCh != body[i].getch())
			return tmpCh;
		else if (tmpCh == Keys::HorizonalGhost || tmpCh == Keys::VerticalGhost || tmpCh == Keys::WanderingGhost) // return ghost
			return tmpCh; 
	}

	return Keys::emptyCh;	
}



void Block::moveBlock(int difx, int dify)  // move block function
{
	int i, blockSize = body.size(), size = 0;
	
	if (isFallBlock())
	{
		for (i = 0; i < blockSize; i++)
			body[i].del();
		for (i = 0; i < blockSize; i++)
			body[i].move(0, 1);
		difx = 0; dify = 0;
	}

	else
	{
		if (canMoveBlock(difx, dify, &size))
		{
			if (difx != 0 || dify != 0) 
			{
				for (i = 0; i < blockSize; i++)
					body[i].del();
				for (i = 0; i < blockSize; i++)
					body[i].move(difx, dify);
			}
		}
		else
		{
			difx = 0; dify = 0;
			carry = 0;
		}
	}
}


bool Block::canMoveBlock(int dirx, int diry, int* totalBlocksSize)  // checks if we can move the block
{
	
	int blockSize = body.size();
	int count = 0, new_x, new_y;
	char shape, nextCh;

	if (*totalBlocksSize)
		*totalBlocksSize += blockSize;
	else
		*totalBlocksSize = blockSize;

	if (*totalBlocksSize > MAX_SIZE_BIG_BLOCK)
		return false;

	for (int i = 0; i < blockSize; i++)
	{
		new_x = body[i].getx() + dirx;
		new_y = body[i].gety() + diry;
		shape = body[i].getch();
		nextCh = pBoard->get(new_x, new_y);

		if (blockSize <= SMALL_BLOCK_SIZE)
		{
			if (nextCh == Keys::emptyCh || pBoard->get(new_x, new_y) == shape)
				count++;
		}
		else
		{
			if (nextCh == Keys::emptyCh || nextCh == blockCh)
				count++;
			else if (nextCh == Keys::wallCh)
			{
				return false;
			}
		}
	}

	if (count == blockSize)
	{
		return true; 
	}
	else
	{
		return false;
	}
}

void Block::setPointsSilent()
{
	int blockSize = body.size();

	for (int i = 0; i < blockSize; i++)
	{
		body[i].setSilent(true);
	}
}



Point Block::isPushBlock(int dirx, int diry) 
{
	int blockSize = body.size();
	char resCh; //char tmpch;
	int new_x = -1, new_y = -1;

	for (int i = 0; i < blockSize; i++)
	{
		new_x = body[i].getx() + dirx;
		new_y = body[i].gety() + diry;

		resCh = pBoard->get(new_x, new_y);
		if (resCh >= '1' && resCh <= '9' && resCh != blockCh)
		{
			break;
		}

	}
	Point p(new_x, new_y, resCh);
	p.setBoard(pBoard);

	return p;
}





