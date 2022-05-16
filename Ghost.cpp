#include "Ghost.h"


void Ghost::setGhostPoint(Board* pb, int x1, int y1, char ch, int idx) // set the original board game to small ship
{	
	setDirs(ch);
	setIdxGhost(idx);
	ghostCh = ch;
	pboard = pb;
	Point tmpP(x1, y1, ch);
	GhostBody = tmpP;
	GhostBody.setBoard(pb);

}

void Ghost::drawGhost(int* colorsFlag) // draw the ghost 
{
	if (*colorsFlag)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GHOST_COLOR);

	GhostBody.draw();
}

