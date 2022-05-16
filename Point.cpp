#include "Point.h"
#include "Board.h"

void Point::draw() const // draw function
{
	if (!silent)
	{
		gotoxy(x, y);
		std::cout << ch;
	}

}

void Point::draw(char ch) // draw function
{
	if (!silent)
	{
		gotoxy(x, y);
		std::cout << ch;
	}
}

void Point::del() const // delete function
{
	gotoxy(x, y);
	std::cout << Keys::emptyCh;
	pBoard->set(x, y, Keys::emptyCh); //update board
}

void Point::setBoard(Board* pb) //set board foe point function 
{
	pBoard = pb;
	pb->set(x, y, ch);
}

char Point::checkNextCh(int dirx, int diry) // checks whats the next ch 
{
	return pBoard->get(x + dirx, y + diry);
}

void Point::move(int difx, int dify) // move function 
{
	int new_x = x + difx;
	int new_y = y + dify;

	if (pBoard->isWall(new_x, new_y))   // pos is already taken
		return;

	x = new_x;
	y = new_y;
	
	if (!silent) { draw(); }
	pBoard->set(x, y, ch); // update board
}

void Point::setPoint(int x, int y, char ch) // set point function
{
	pBoard->set(x, y, Keys::emptyCh); //update board
	pBoard->set(x, y, ch);
}





