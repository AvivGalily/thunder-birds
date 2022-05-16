#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include <iostream>
#include <fstream>
#include <string>
#include "PlayRegularGame.h"
#include "PlayGameFromFiles.h"
#include "utils.h"
#include "io_utils.h"
#include "board.h"

using namespace std;

class GameMenu
{
	enum { BOARD_1 = '2' , BOARD_2 = '3', BOARD_3 = '4', SET_COLORS = '6', SET_BLACK_AND_WHITE = '7', MENU_COLOR = 6};
	int colorsFlag = 0; // default = without colors
	char currLevel = '1';
	char prevLevel = '0';

public:
	void preUserChoice();
	void printPreMenu();
	void printMenu();
	void userChoice(string modeStr, char mode, int* firstIterFlag);
	char getUserInput();
	void printInstructions();
	void goOut();
	void playFullGame(int* flag, char mode);
	void playSingleBoard(char boardNum, int* flag, char mode);
	string findBoardFile();
	void deleteDetailsFromFiles();
	void resetMenuFile();

		

};

#endif