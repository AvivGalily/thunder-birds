#ifndef _PLAY_GAME_FROM_FILES_H_
#define _PLAY_GAME_FROM_FILES_H_

#include "io_utils.h"
#include <cctype>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "utils.h"
#include "GameManager.h"


using namespace std;


class PlayGameFromFiles : public GameManager
{
public:
	using GameManager::GameManager;  // c'tor inheritance
	
	void run(int* currStepFile, int* currRandGhostFil, int* currResFile, bool silentFlag, int* resTest);
	void silentCheck(string stepLine, int* currResFile, int* resTest, int dieFlag);
	int checkKey(string stepLine, string resLine, char key, bool dieFlag);


};

#endif

