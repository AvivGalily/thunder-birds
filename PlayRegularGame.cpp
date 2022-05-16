#include "PlayRegularGame.h"


/*
PlayGame::PlayGame(char numLife, char numBoard, int* colorsFlag1, const string& fileName) // C'tor
{
	initBoard(fileName);
	timer.setBoard(&board);
	colorsFlag = colorsFlag1;
	life = numLife;
	boardNum = numBoard;
}*/

void PlayRegularGame::run() // run the game
{
	string stepsFileStr = findStepsFile();
	char key = 0;
	ofstream stepsFile(stepsFileStr, ios_base::out | ios_base::app);
	string RandFileStr = findRandFile();
	ofstream RandFile(RandFileStr, ios_base::out | ios_base::app);
	char switchShips = Keys::switchToSmallShip; // set default to small ship
	bool playGame = true, isAlive = true, pauseMode = true, exitGame = getExitFlag();
	int timeCounter = 1, outOfTime = 0, looseGame = 0, dieFlag = 0;
	int* colorsFlag = getColorsFlag(), numIter = 0;
	bool silent = false; char randidx = '0';
	drawObj();
	string s;
	bool load = false;
	while (playGame && !exitGame)
	{
		if (_kbhit())
		{
			key = _getch();
			updateStepsFile(stepsFile, key);

			while (key == Keys::ESC && pauseMode) // pause the game
			{
				system("cls");
				cout << "Game paused, press ESC again to continue or 9 to Exit" << endl;

				key = _getch();
				updateStepsFile(stepsFile, key);

				while (pauseMode)
				{
					if (key == Keys::ExitGame) // exit the game
					{
						exitGame = true;
						setExitFlag(exitGame);
						playGame = false;
						pauseMode = false;
					}
					else if (key == Keys::ESC)
					{
						system("cls");
						//drawObj();
						setToZero6Dirs(); //stop the elements
						pauseMode = false;
					}

					if (!exitGame)
					{
						key = _getch();
						updateStepsFile(stepsFile, key);
					}
				}
			}
			pauseMode = true;
			key = tolower(key);
			moveOnlyShips(&key, &switchShips);
			
			s = "G";
			moveGhosts(&looseGame, silent, load);
			s = moveRandGhosts( &looseGame,  load,  randidx);
			updateRandGhostStepsFile(RandFile, s);
		}
		runTimer(&timeCounter, &outOfTime,silent);		
		moveTogetherBlocksAndShips(&switchShips, &key, &looseGame, colorsFlag, silent);
		moveGhosts(&looseGame, silent, load);
		s = moveRandGhosts(&looseGame, load, randidx);
		 updateRandGhostStepsFile(RandFile, s);

		Sleep(80);
		dieFlag = isPlayerDied(looseGame, outOfTime, silent);
		playGame = (dieFlag && !playerWin()); // if the player win or the player die - go out the loop				
	}
	stepsFile.close();
	RandFile.close();
	updateResultFile(dieFlag);
	system("cls");

}

void PlayRegularGame::updateStepsFile(ofstream& file, char key)
{
	string currMoveStr = "";
	//ofstream stepsFile(stepsFileStr, ios_base::out | ios_base::app);

	if (file.is_open())
	{
		currMoveStr += getBoardCh(9, 1);
		currMoveStr += getBoardCh(10, 1);
		currMoveStr += getBoardCh(11, 1);
		currMoveStr += key;
		file << currMoveStr << endl; // timer + key
	}
	else
	{
		cout << "could not create steps file !" << endl;
	}

}
void PlayRegularGame::updateRandGhostStepsFile(ofstream& file, string key)
{
	string currMoveStr = "";
	//ofstream stepsFile(stepsFileStr, ios_base::out | ios_base::app);

	if (file.is_open())
	{
		currMoveStr += key;
		
		file << currMoveStr; // timer + key
	}
	else
	{
		cout << "could not create steps file !" << endl;
	}

}

void PlayRegularGame::updateResultFile(int dieFlag)
{
	string resFileStr = findResultFile(), tmpStr = "";
	ofstream resFile(resFileStr, ios_base::out | ios_base::app);
	char result = 'D'; // dead

	tmpStr += getBoardCh(9, 1);
	tmpStr += getBoardCh(10, 1);
	tmpStr += getBoardCh(11, 1); 

	if (getExitFlag()) // the user press exit
		result = Keys::ExitCh;
	else if (dieFlag)  // not die and finished the game = Win
		result = 'W';


	if (resFile.is_open())
	{
		tmpStr += result;
		resFile << tmpStr << endl; // resCh + timer
	}
	else
	{
		cout << "could not create steps file !" << endl;
	}


}
