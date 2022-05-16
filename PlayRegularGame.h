#ifndef _PLAY_REGULAR_GAME_H_
#define _PLAY_REGULAR_GAME_H_

#include "io_utils.h"
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
#include <windows.h>
#include "utils.h"
#include "GameManager.h"


using namespace std;


class PlayRegularGame : public GameManager
{
	
public:
	friend class Ghost;
	using GameManager::GameManager;  // c'tor inheritance
	void run();
	void updateStepsFile(ofstream& file, char key);
	void updateResultFile(int isDied);
	void updateRandGhostStepsFile(ofstream& file, string key);
	void ClearRandFile(ofstream& file);
	
};

#endif

