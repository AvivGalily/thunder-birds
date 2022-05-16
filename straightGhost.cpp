#include "straightGhost.h"


void straightGhost::setDirs(char ch)
{
	if (ch == Keys::HorizonalGhost)
	{
		dirx = -1; diry = 0;
	}
	else if (ch == Keys::VerticalGhost)
	{
		dirx = 0; diry = -1;
	}
}

string straightGhost::moveGhost(int* flag, int* ghostFlag, bool load) // move function
{

	if (*ghostFlag)
	{
		isAlive = false;
		setGhostCh(Keys::emptyCh);
		dirx = 0; diry = 0;
		delGhostBody();
		//char ghostCh = getGhostCh();
		setGhostBodyPoint(dirx, diry);
	}

	if (isAlive)
	{
		if (getGhostCh() == Keys::HorizonalGhost)
		{
			if (!canGhostMove(dirx, diry, flag))
			{
				dirx *= -1;
			}
		}
		else if (getGhostCh() == Keys::VerticalGhost)
		{
			if (!canGhostMove(dirx, diry, flag))
			{
				diry *= -1;
			}
		}

		delGhostBody();
		moveGhostP(dirx, diry);
		drawP();
	}

	return "";

}

int const straightGhost::getIdxGhost()
{
	return idxGhost; 
}

void straightGhost::setIdxGhost(int idx)
{
	idxGhost = idx;
}

/*
string Ghost::moveRandomGhost(int* flag, int* ghostFlag, bool load, char randdirx, char randdiry)
{
	string s;
	if (*ghostFlag)
	{
		isAlive = false;
		ghostCh = Keys::emptyCh;
		dirx = 0; diry = 0;
		GhostBody.del();
		GhostBody.setPoint(dirx, diry, ghostCh);
	}

	if (isAlive)
	{
		if (!load) {
			s = randMove(&dirx, &diry);
			while (!canGhostMove(dirx, diry, flag))
			{
				s = randMove(&dirx, &diry);
			}
		}
		if (load)
		{
			if (randdirx == '0') { dirx = 0; }
			if (randdiry == '0') { diry = 0; }
			if (randdirx == 'R') { dirx = 1; }
			if (randdiry == 'U') { diry = -1; }
			if (randdirx == 'L') { dirx = -1; }
			if (randdiry == 'D') { diry = 1; }
		}
		GhostBody.del();
		GhostBody.move(dirx, diry);
		GhostBody.draw();
	}
	return s;
}

string Ghost::randMove(int* dirx, int* diry) // random move for the wandering ghost
{
	string s = "";
	*dirx = rand() % 3;
	*diry = rand() % 3;

	if (*dirx == 2) { *dirx = -1; randdirx = 'L'; }
	if (*diry == 2) { *diry = -1; randdiry = 'U'; }

	if (*dirx == 1) {randdirx = 'R'; }
	if (*diry == 1) {randdiry = 'D';}
	if (*dirx == 0) { randdirx = '0'; }
	if (*diry == 0) { randdiry = '0'; }
	s.append(randdirx); s.append(randdiry);
	return s;
}
*/

bool straightGhost::canGhostMove(int dirx, int diry, int* flag) // checks if the ghost can move
{
	Point* ghostBody = getGhostBody();
	int curr_x = ghostBody->getx(), curr_y = ghostBody->gety();
	char nextCh = getBoardCh(curr_x + dirx, curr_y + diry);

	if (nextCh == Keys::wallCh || (nextCh >= '1' && nextCh <= '9'))
	{
		return false;
	}
	else if (getBoardCh(curr_x, curr_y + 1) == Keys::smallShipCh || getBoardCh(curr_x, curr_y + 1) == Keys::bigShipCh)
	{
		if (getChGhost() == Keys::VerticalGhost)
		{
			*flag = Keys::flag2;
			return true;
		}
	}
	else if (getBoardCh(curr_x, curr_y - 1) == Keys::smallShipCh || getBoardCh(curr_x, curr_y - 1) == Keys::bigShipCh)
	{

		if (getChGhost() == Keys::VerticalGhost)
		{
			*flag = Keys::flag2;
			return true;
		}
	}
	else if (getBoardCh(curr_x + 1, curr_y) == Keys::smallShipCh || getBoardCh(curr_x + 1, curr_y) == Keys::bigShipCh)
	{
		if (getChGhost() == Keys::HorizonalGhost)
		{
			*flag = Keys::flag2;
			return true;
		}
	}
	else if (getBoardCh(curr_x - 1, curr_y) == Keys::smallShipCh || getBoardCh(curr_x - 1, curr_y) == Keys::bigShipCh)
	{
		if (getChGhost() == Keys::HorizonalGhost)
		{
			*flag = Keys::flag2;
			return true;
		}
	}
	else
		return true;

}

