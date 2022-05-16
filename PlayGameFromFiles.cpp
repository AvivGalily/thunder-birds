#include "PlayGameFromFiles.h"

// run the game from files
void PlayGameFromFiles::run(int* currStepFile, int* currRandGhostFile, int* currResFile, bool silentFlag, int* resTest) 
{
	string stepsFileStr = findStepsFile(), randFileStr = findRandFile(), currLine, nextLine, currLineRand, nextLineRand, tmpStr;
	char key = '0', nextKey = '0', timerUnits = '0', timerHundreds = '1', timerTens = '0', switchShips = Keys::switchToSmallShip, randidx;;
	ifstream stepsFile(stepsFileStr); 
	ifstream randFile(randFileStr);
	stepsFile.seekg(*currStepFile, std::ios::beg);
	randFile.seekg(*currRandGhostFile, std::ios::beg);
	bool playGame = true, isAlive = true, pauseMode = true, exitGame = getExitFlag(), load = true, silent = false;
	int timeCounter = 1, outOfTime = 0, looseGame = 0, dieFlag = 0, nextBoard;
	int* colorsFlag = getColorsFlag();

	if (!silentFlag)
		drawObj();
	else
		silent = true;

	if (!stepsFile.eof())
	{
		std::getline(stepsFile, currLine); // read the first line
		*currStepFile = stepsFile.tellg();
		if (currLine != "") // empty file
			key = currLine[3];

		if (!stepsFile.eof())
		{
			std::getline(stepsFile, nextLine);
			if (currLine != "") // empty file 
				nextKey = nextLine[3];
		}
	}

	while (playGame && !exitGame)
	{
		timerHundreds = getBoardCh(9, 1); timerTens = getBoardCh(10, 1); timerUnits = getBoardCh(11, 1); // update the curr timer ticks

		if (timerHundreds == nextLine[0] && timerTens == nextLine[1] && timerUnits == nextLine[2]) // the timer arrived to the next step time
		{
			if (!stepsFile.eof() && key != Keys::ESC)
			{
				key = nextKey;
				currLine = nextLine;
				*currStepFile = stepsFile.tellg();
				std::getline(stepsFile, nextLine);
				if (nextLine != "")
					nextKey = nextLine[3];
			}
		}

		if (timerHundreds == currLine[0] && timerTens == currLine[1] && timerUnits == currLine[2])
		{
			while (key == Keys::ESC && pauseMode) // pause the game
			{
				std::system("cls");
				std::cout << "Game paused, press ESC again to continue or 9 to Exit" << std::endl;

				if (!stepsFile.eof() && nextKey != Keys::ExitCh)
				{
					key = nextKey;
					currLine = nextLine;
					*currStepFile = stepsFile.tellg();
					std::getline(stepsFile, nextLine);
					if (nextLine != "")
						nextKey = nextLine[3];
				}

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
						std::system("cls");
						//drawObj();
						setToZero6Dirs(); //stop the elements
						pauseMode = false;
					}

					if (!exitGame)
						if (!stepsFile.eof())
						{
							key = nextKey;
							currLine = nextLine;
							*currStepFile = stepsFile.tellg();
							std::getline(stepsFile, nextLine);
							if (nextLine != "")
								nextKey = nextLine[3];
						}
				}
			}

			pauseMode = true;
			key = tolower(key);
			moveOnlyShips(&key, &switchShips);
			moveGhosts(&looseGame, silent, load);
			int i = 0;

			while (!randFile.eof() && i < GetWanderingCounter())
			{
				//key = nextKey;
				currLineRand = nextLineRand;
				std::getline(randFile, nextLineRand);
				*currRandGhostFile = randFile.tellg();
				if (nextLineRand != "") {
					randidx = nextLineRand[1];
					setRandDirX(nextLineRand[3]);
					setRandDirY(nextLineRand[4]);
					moveRandGhosts(&looseGame, load, randidx);
				}
				i++;
			}

		}

		runTimer(&timeCounter, &outOfTime, silent);
		moveTogetherBlocksAndShips(&switchShips, &key, &looseGame, colorsFlag, silent);
		moveGhosts(&looseGame, silent, load);
		int i = 0;
		while (!randFile.eof() && i < GetWanderingCounter())
		{
			//key = nextKey;
			currLineRand = nextLineRand;
			std::getline(randFile, nextLineRand);
			*currRandGhostFile = randFile.tellg();
			if (nextLineRand != "") {
				randidx = nextLineRand[1];
				setRandDirX(nextLineRand[3]);
				setRandDirY(nextLineRand[4]);
				moveRandGhosts(&looseGame, load, randidx);
			}
			i++;
		}
		if (!silentFlag)
			Sleep(80);
		dieFlag = isPlayerDied(looseGame, outOfTime, silentFlag);
		playGame = (dieFlag && !playerWin()); // if the player win or the player die - go out the loop
	}

	timerHundreds = getBoardCh(9, 1); timerTens = getBoardCh(10, 1); timerUnits = getBoardCh(11, 1);
	if (silent)
	{
		tmpStr += timerHundreds; tmpStr += timerTens; tmpStr += timerUnits;
		silentCheck(tmpStr, currResFile, resTest, dieFlag);
	}
	stepsFile.close();
	randFile.close();
	std::system("cls");
}

void PlayGameFromFiles::silentCheck(string stepLine, int* currResFile, int* resTest, int dieFlag)
{
	char key = ' ';
	string resStr = findResultFile(), resLine;
	ifstream resFile(resStr);
	resFile.seekg(*currResFile, std::ios::beg);

	if (!resFile.eof())
	{
		std::getline(resFile, resLine); // read the first line
		*currResFile = resFile.tellg();
		if (resLine != "") // empty file
			key = resLine[3];
	}

	if (*resTest)
		*resTest = checkKey(stepLine, resLine, key, dieFlag);

	resFile.close();
}

int PlayGameFromFiles::checkKey(string stepLine, string resLine, char key, bool dieFlag)
{
	int res = 0;

	if (stepLine[0] == resLine[0] && stepLine[1] == resLine[1] && stepLine[2] == resLine[2])
	{
		if (dieFlag == 0 && key == 'D')
			res = 1;
		else if (getExitFlag() && key == Keys::ExitCh)
			res = 1;
		else if (playerWin() && key == 'W')
			res = 1;
	}

	return res;

}



