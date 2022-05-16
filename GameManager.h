#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "io_utils.h"
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <vector>
#include "board.h"
#include "Block.h"
#include "utils.h"
#include "Timer.h"
#include "Ships.h"
#include "Ghost.h"
#include "straightGhost.h"
#include "wanderGhost.h"


using namespace std;


class GameManager
{
	enum { MAX_ROWS = 25, MAX_COLS = 81, SHIPS_MAX_NUM = 2, BLOCKS_MAX_NUM = 10, SMALL_BLOCK_MAX_SIZE = 2 };
	Board board;
	Timer timer{ 9,10,11,1, '9', '9' }; // set the timer to 999 
	Ship ships[SHIPS_MAX_NUM];
	Block* blocks;
	straightGhost* straightGhostsArr;
	wanderGhost* wanderingGhostArr;
	int activePoint = 0, dirx = 0, diry = 0, dirB_x = 0, dirB_y = 0, blocksCounter = 0, straightGhostCounter = 0, wanderingGhostCounter = 0;
	char life, boardNum, randdirx, randdiry;
	bool exitGame = false;
	int* colorsFlag;
	

public:
	GameManager(char numLife, char numBoard, int* colorsFlag1, const string& fileName);  // C'tor
	~GameManager() { delete[] blocks; delete[] straightGhostsArr; delete[] wanderingGhostArr;  }; // D'tor
	//void run();
	void drawObj();
	void runTimer(int* timeCounter, int* flag,bool silent);
	void clearBoard();
	int findBlockIdx(char ch);
	char getBoardNum() { return boardNum; }

	//move functions:
	void moveOnlyShips(char* key, char* switchShips);
	void moveTogetherBlocksAndShips(char* switchShips, char* key, int* isPlayerDied, int* colorsFlag, bool silentFlag);
	void moveGhosts(int* looseFlag, bool silentFlag, bool load);
	void updatedirs(int sizeofpile, int blocksCounter, int ship_indx);
	void setToZero6Dirs();
	string moveRandGhosts(int* looseFlag, bool load, char randidx);
	void setBlocksAndShipsSilent();
	void setGhostsSilent();

	// push blocks functions:
	int whichBlockPushed(Point pBlock);
	int PileOfBlocksUp(int ship_indx);
	int PileOfBlocksLeft(int ship_indx);
	int PileOfBlocksRight(int ship_indx);
	int PileOfBlocks(int dir_x, int dir_y, int ship_indx);

	// file functions:
	void initBoard(const string& fileName);
	void readShipsAndBlocksFromBoard();
	void insertBlocksFromBoard(int row, int col, char ch, int blockIdx, char board1[][MAX_COLS]);
	void readBoardFromFile(ifstream& file);
	void insertFullLine(int col);
	//void updateStepsFile(ofstream& file, char key);
	string findStepsFile();
	string findResultFile();
	string findRandFile();


	// checking functions:
	bool playerWin();
	bool wantToExit();
	int checkDupBlocks(int x, int y, char ch);
	bool outOfLives();
	bool isPlayerDied(int looseLifeByShips, int outOfTime, bool silentFlag);
	int isGhostDied(int idx, char ch);
	bool getExitFlag() { return exitGame; }

	void setExitFlag(bool flag) { exitGame = flag; }
	int* getColorsFlag() { return colorsFlag; }
	char getBoardCh(int x, int y) { return board.get(x, y); }

	int const GetWanderingCounter() { return wanderingGhostCounter; }

	char const getRandDirX() { return randdirx; }
	char const getRandDirY() { return randdiry; }
	void setRandDirX(char newDir) { randdirx = newDir; }
	void setRandDirY(char newDir) { randdiry = newDir; }


};


#endif

