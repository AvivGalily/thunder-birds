#include "wanderGhost.h"


void wanderGhost::setDirs(char ch)
{
	srand(time(NULL));
	string tmp = randMove(&dirx, &diry);
}

string wanderGhost::randMove(int* dirx, int* diry) // random move for the wandering ghost
{
	string resStr = "";
	*dirx = rand() % 3;
	*diry = rand() % 3;

	if (*dirx == 2) { *dirx = -1; randdirx = 'L'; }
	if (*diry == 2) { *diry = -1; randdiry = 'U'; }

	if (*dirx == 1) { randdirx = 'R'; }
	if (*diry == 1) { randdiry = 'D'; }
	if (*dirx == 0) { randdirx = '0'; }
	if (*diry == 0) { randdiry = '0'; }
	resStr += randdirx; resStr += randdiry;
	return resStr;
}

/*
string wanderGhost::moveRandomGhost(int* flag, int* ghostFlag, bool load, char randdirx, char randdiry)
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

	if (*dirx == 1) { randdirx = 'R'; }
	if (*diry == 1) { randdiry = 'D'; }
	if (*dirx == 0) { randdirx = '0'; }
	if (*diry == 0) { randdiry = '0'; }
	s.append(randdirx); s.append(randdiry);
	return s;
}*/

string wanderGhost::moveGhost(int* flag, int* ghostFlag, bool load) // move function
{
	string resStr;
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
		if (!load) {
			resStr = randMove(&dirx, &diry);
			while (!canGhostMove(dirx, diry, flag))
			{
				resStr = randMove(&dirx, &diry);
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
		delGhostBody();
		moveGhostP(dirx, diry);
		drawP();
	}
	return resStr;
}

int const wanderGhost::getIdxGhost()
{
	return idxGhost;
}

void wanderGhost::setIdxGhost(int idx)
{
	idxGhost = idx;
}

bool wanderGhost::canGhostMove(int dirx, int diry, int* flag) // checks if the ghost can move
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
		*flag = Keys::flag2;
		return true;
	}
	else if (getBoardCh(curr_x, curr_y - 1) == Keys::smallShipCh || getBoardCh(curr_x, curr_y - 1) == Keys::bigShipCh)
	{
		*flag = Keys::flag2;
		return true;
	}
	else if (getBoardCh(curr_x + 1, curr_y) == Keys::smallShipCh || getBoardCh(curr_x + 1, curr_y) == Keys::bigShipCh)
	{
		*flag = Keys::flag2;
		return true;
	}
	else if (getBoardCh(curr_x - 1, curr_y) == Keys::smallShipCh || getBoardCh(curr_x - 1, curr_y) == Keys::bigShipCh)
	{
		*flag = Keys::flag2;
		return true;
	}
	else
		return true;

}
