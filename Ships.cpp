#include "Ships.h"

void Ship::setShipPoint(Board* pb, int x1, int y1, char ch) // set the original board game to small ship
{
	body.push_back(Point(x1, y1, ch));
	setBoard(pb);
	size++;
	body.resize(size);
}

void Ship::setBoard(Board* pb) // set board for ship function
{
	int shipSize = body.size();

	for (int i = 0; i < shipSize; i++)
		body[i].setBoard(pb);

	pboard = pb;
}

void Ship::draw(int* colorsFlag) // draw function
{
	int shipSize = body.size();

	if (*colorsFlag && shipSize > SMALL_SHIP_SIZE)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BIG_SHIP_COLOR);
	else if (*colorsFlag && shipSize == SMALL_SHIP_SIZE)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SMALL_SHIP_COLOR);


	for (int i = 0; i < shipSize; ++i)
		body[i].draw();
}


bool Ship::canMove(int dirx, int diry, int* ghostFlag) // check if the ship can move
{
	int shipSize = body.size();
	char nextCh;

	for (int i = 0; i < shipSize; i++)
	{
		int new_x = body[i].getx() + dirx;
		int new_y = body[i].gety() + diry;

		nextCh = pboard->get(new_x, new_y);

		if (shipSize <= SMALL_SHIP_SIZE)
		{
			if (nextCh == Keys::HorizonalGhost || nextCh == Keys::WanderingGhost || nextCh == Keys::VerticalGhost)
			{
				*ghostFlag == Keys::flag2;
				return false;
			}
			else if (nextCh != Keys::emptyCh && nextCh != Keys::smallShipCh)
				return false;
		}
		else // SIZE_BIG_SHIP
		{
			if (nextCh == Keys::HorizonalGhost || nextCh == Keys::WanderingGhost || nextCh == Keys::VerticalGhost)
			{
				*ghostFlag == Keys::flag2;
				return false;
			}
			else if (nextCh != Keys::emptyCh && nextCh != Keys::bigShipCh)
				return false;
		}

	}
	return true;
}

void Ship::move(int difx, int dify, int* ghostFlag) // move function
{
	int i, shipSize = body.size();
	
	if (canMove(difx, dify, ghostFlag))
	{
		for (i = 0; i < shipSize; i++)
			body[i].del();
		for (i = 0; i < shipSize; i++)
			body[i].move(difx, dify);
	}
	
}

Point Ship::isPushBlock(int dirx, int diry, int* ghostFlag) // checks if the ship push block and return the point that pushed
{
	int shipSize = body.size();
	char resCh = Keys::emptyCh; 
	int new_x = -1, new_y = -1;
	
	for (int i = 0; i < shipSize; i++)
	{
			new_x = body[i].getx() + dirx;
			new_y = body[i].gety() + diry;

			 resCh = pboard->get(new_x, new_y);
			if (resCh >= '1' && resCh <= '9')
			{
				break;
			}
			else if (resCh == Keys::HorizonalGhost || resCh == Keys::VerticalGhost || resCh == Keys::WanderingGhost)
			{
				*ghostFlag = Keys::flag2;
				break;
			}	
	}
	Point p(new_x, new_y, resCh);
	p.setBoard(pboard);

	return p;
}

bool Ship::canPushBlock(int dirx, int diry, int* ghostFlag)
{
	int shipSize = body.size();
	char resCh = Keys::emptyCh;
	int new_x = -1, new_y = -1;

	for (int i = 0; i < shipSize; i++)
	{
		new_x = body[i].getx() + dirx;
		new_y = body[i].gety() + diry;

		resCh = pboard->get(new_x, new_y);
		if (resCh >= '1' && resCh <= '9')
		{
			return true;
		}
	}

	return false;
}

bool Ship::win() // win checking
{
	int shipSize = body.size();

	for (int i = 0; i < shipSize; i++)
	{
		for (int dirx = -1; dirx <= 1; dirx++)
			for (int diry = -1; diry <= 1; diry++)
			{
				int new_x = body[i].getx() + dirx;
				int new_y = body[i].gety() + diry;

				if (pboard->get(new_x, new_y) == Keys::ExitCh)
					return true;
			}
	}

	return false;
}

void Ship::setPointsSilent()
{
	int shipSize = body.size();

	for (int i = 0; i < shipSize; i++)
	{
		body[i].setSilent(true);
	}
}
