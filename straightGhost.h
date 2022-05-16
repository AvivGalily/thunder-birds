#ifndef _STRAIGHT_GHOST_H_
#define _STRAIGHT_GHOST_H_

#include "Ghost.h"

class straightGhost : public Ghost
{
	//friend class PlayRegularGame;
	bool isAlive = true, load = false;
	char straightdirx, straightdiry;
	int dirx, diry, idxGhost = -1;
public:
	//void setGhostPoint(Board* pb, int x1, int y1, char ch);  ооеощ баб
	void setDirs(char ch) override;
	string moveGhost(int* flag, int* ghostFlag, bool load) override;
	bool canGhostMove(int dirx, int diry, int* flag) override;
	//void drawGhost(int* colorsFlag); ооеощ баб    
	//void setIdxGhost(int idx) { idxGhost = idx; }
	//int GetColor() { return GHOST_COLOR; }
	//string moveRandomGhost(int* flag, int* ghostFlag, bool load, char randdirx, char randdiry);
	//void setSilent() { GhostBody.setSilent(true); }


	int const getIdxGhost() override;
	void setIdxGhost(int idx) override;
	//char const getChGhost() { return ghostCh; }
};

#endif

