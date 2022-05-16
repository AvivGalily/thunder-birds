#ifndef _GHOST_H_
#define _GHOST_H_

#include <vector> 
#include "Point.h"
#include "utils.h"
#include "board.h"
#include "io_utils.h"


class Ghost 
{
	enum { GHOST_COLOR = 3 };
	Board* pboard = nullptr;
	Point GhostBody;
	char ghostCh;

public:
	//virtual ~Ghost() {}
	void setGhostPoint(Board* pb, int x1, int y1, char ch, int idx);
	char const getChGhost() { return ghostCh; }
	char const getGhostCh() { return ghostCh; }
	void setSilent() { GhostBody.setSilent(true); }
	void setGhostCh(char ch) { ghostCh = ch; }
	int GetColor() { return GHOST_COLOR; }
	void drawGhost(int* colorsFlag);
	Point* getGhostBody() { return &GhostBody; }
	char const getBoardCh(int x, int y) { return pboard->get(x, y); }
	int const getx() { return GhostBody.getx(); }
	int const gety() { return GhostBody.gety(); }
	void delGhostBody() { GhostBody.del(); }
	void moveGhostP(int dirx, int diry) { GhostBody.move(dirx, diry); }
	void drawP() { GhostBody.draw(); }


	virtual void setDirs(char ch) = 0;
	virtual string moveGhost(int* flag, int* ghostFlag, bool load) = 0;
	virtual bool canGhostMove(int dirx, int diry, int* flag) = 0;

	//virtual string randMove(int* dirx, int* diry) = 0;
	//virtual void setIdxGhost(int idx); // { idxGhost = idx; }
	virtual int const getIdxGhost() = 0;// { return idxGhost; }
	virtual void setIdxGhost(int idx) = 0;
	//virtual char const getChGhost();//{ return ghostCh; }
	//virtual string moveRandomGhost(int* flag, int* ghostFlag, bool load, char randdirx, char randdiry);


	void setGhostBodyPoint(int dirx, int diry) { GhostBody.setPoint(dirx, diry, ghostCh); }

};

#endif