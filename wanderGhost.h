#ifndef _WANDER_GHOST_H_
#define _WANDER_GHOST_H_

#include "Ghost.h"
#include <time.h> 


class wanderGhost : public Ghost
{
	//friend class PlayRegularGame;
	enum { GHOST_COLOR = 3 };
	bool isAlive = true, load = false;
	char randdirx, randdiry;
	int dirx, diry, idxGhost = -1;

public:
	void setDirs(char ch) override;
	string moveGhost(int* flag, int* ghostFlag, bool load) override;
	bool canGhostMove(int dirx, int diry, int* flag) override;
	string randMove(int* dirx, int* diry);
	int const getIdxGhost() override;
	void setIdxGhost(int idx) override;
	void setDirsCh(char dirx, char diry) { randdirx = dirx; randdiry = diry; };
	//string moveRandomGhost(int* flag, int* ghostFlag, bool load, char randdirx, char randdiry) override;


};


#endif


