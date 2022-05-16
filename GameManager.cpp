#include "GameManager.h"



GameManager::GameManager(char numLife, char numBoard, int* colorsFlag1, const string& fileName) // C'tor
{
	initBoard(fileName);
	timer.setBoard(&board);
	colorsFlag = colorsFlag1;
	life = numLife;
	boardNum = numBoard;
}

string GameManager::findStepsFile()
{
	string resFile;

	if (boardNum == '1')
		resFile = "tb01.steps.txt";
	else if (boardNum == '2')
		resFile = "tb02.steps.txt";
	else // boardNum == '3'
		resFile = "tb03.steps.txt";

	return resFile;
}
string GameManager::findRandFile()
{
	string resFile;

	if (boardNum == '1')
		resFile = "tb01.rand.txt";
	else if (boardNum == '2')
		resFile = "tb02.rand.txt";
	else // boardNum == '3'
		resFile = "tb03.rand.txt";

	return resFile;
}

void GameManager::setGhostsSilent()
{
	for (int i = 0; i < wanderingGhostCounter; i++)
		wanderingGhostArr[i].setSilent();
	for (int i = 0; i < straightGhostCounter; i++)
		straightGhostsArr[i].setSilent();
}


void GameManager::moveGhosts(int* looseFlag, bool silentFlag, bool load) // move ghost function
{

	if (silentFlag)
		setGhostsSilent();
	int ghostFlag = 0;
	
	for (int i = 0; i < straightGhostCounter; i++)
	{
		ghostFlag = isGhostDied(i, Keys::VerticalGhost);
		if (*colorsFlag)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), straightGhostsArr->GetColor());
		straightGhostsArr[i].moveGhost(looseFlag, &ghostFlag, load);
	}

	for (int i = 0; i < wanderingGhostCounter; i++)
	{
		ghostFlag = isGhostDied(i, Keys::WanderingGhost);
		if (*colorsFlag)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), straightGhostsArr->GetColor());
		wanderingGhostArr[i].moveGhost(looseFlag, &ghostFlag, load);
	}
	
}
string GameManager::moveRandGhosts(int* looseFlag, bool load, char randidx) 
{
	int ghostFlag = 0;
	string randMoveStr;
	if (!load) 
	{
		for (int i = 0; i < wanderingGhostCounter; i++)
		{
			if (*colorsFlag)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wanderingGhostArr->GetColor());

			randMoveStr += "G";
			int idxG = wanderingGhostArr[i].getIdxGhost();
			randMoveStr += to_string(idxG);
			randMoveStr += " ";
			wanderingGhostArr[i].setDirsCh(randdirx, randdiry);
			randMoveStr += wanderingGhostArr[i].moveGhost(looseFlag, &ghostFlag, load);
			randMoveStr += "\n";
			
		}
		return randMoveStr;
	}
	else
	{
		int randomidx = randidx - '0';
		for (int i = 0; i < wanderingGhostCounter; i++) {
			if (wanderingGhostArr[i].getIdxGhost() == randomidx && wanderingGhostArr[i].getChGhost() == Keys::WanderingGhost)
			{
				wanderingGhostArr[i].setDirsCh(randdirx, randdiry);
				wanderingGhostArr[i].moveGhost(looseFlag, &ghostFlag, load);
			}
		}
	}
	return randMoveStr;
}

void GameManager::drawObj() // draw objects function
{
	board.changeLife(life);
	board.changeBoardNum(boardNum);
	board.printBoard(colorsFlag);

	for (int i = 0; i < SHIPS_MAX_NUM; i++)
		ships[i].draw(colorsFlag);
	for (int j = 0; j < blocksCounter; j++)
		if (blocks[j].whatSize() > 0)
		{
			blocks[j].drawBlock(colorsFlag);
		}
	for (int g = 0; g < straightGhostCounter; g++)
		straightGhostsArr[g].drawGhost(colorsFlag);
	for (int g = 0; g < wanderingGhostCounter; g++)
		wanderingGhostArr[g].drawGhost(colorsFlag);
}

void GameManager::moveOnlyShips(char* key, char* switchShips) // move only ships function
{

	switch (*key) //move ships
	{
	case Keys::Up:
		dirx = 0;
		diry = -1;
		break;
	case Keys::Right:
		dirx = 1;
		diry = 0;
		break;
	case Keys::Down:
		dirx = 0;
		diry = 1;
		break;
	case Keys::Left:
		dirx = -1;
		diry = 0;
		break;
	case Keys::switchToBigShip: // switch ships
	{
		if (*switchShips != Keys::switchToBigShip)
		{
			*switchShips = Keys::switchToBigShip;
			setToZero6Dirs(); //initilize dirs - means stop the old ship + the blocks
		}
		break;
	}
	case Keys::switchToSmallShip: // switch ships
	{
		if (*switchShips != Keys::switchToSmallShip)
		{
			*switchShips = Keys::switchToSmallShip;
			setToZero6Dirs(); //initilize dirs - means stop the old ship + the blocks
		}
		break;
	}
	}
}

void GameManager::setToZero6Dirs() // set directions to zero
{
	dirx = 0; diry = 0;

	for (int i = 0; i < blocksCounter; i++)
	{
		blocks[i].setDirX(0);
		blocks[i].setDirY(0);
	}
}

int GameManager::isGhostDied(int idx, char ch) // checks if ghost died
{
	int x, y;
	if (ch == Keys::WanderingGhost)
	{
		x = wanderingGhostArr[idx].getx();
		y = wanderingGhostArr[idx].gety();

		char boardCh = board.board[y - 1][x];

		if (boardCh >= '1' && boardCh <= '9')
		{
			Point tmpP(x, y - 1, boardCh);
			int idxBlock = whichBlockPushed(tmpP);
			if (!blocks[idxBlock].isWallBelow())
				return 1;
		}
	}

	else if  (ch == Keys::VerticalGhost)
	{
		x = straightGhostsArr[idx].getx();
		y = straightGhostsArr[idx].gety();

		char boardCh = board.board[y - 1][x];

		if (boardCh >= '1' && boardCh <= '9')
		{
			Point tmpP(x, y - 1, boardCh);
			int idxBlock = whichBlockPushed(tmpP);
			if (!blocks[idxBlock].isWallBelow())
				return 1;
		}
	}


	return 0;
}

void GameManager::setBlocksAndShipsSilent()
{
	for (int i = 0; i < blocksCounter; i++) 
		blocks[i].setPointsSilent();

	for (int i = 0; i < SHIPS_MAX_NUM; i++)
		ships[i].setPointsSilent();
}

void GameManager::moveTogetherBlocksAndShips(char* switchShips, char* key, int* isPlayerDied, int* colorsFlag, bool silentFlag) // move blocks and ships function
{
	int totalPushedBlocksSize = 0; int BigShipIndx = 1; int SmallShipIndx = 0;

	if (silentFlag)
		setBlocksAndShipsSilent();

	for (int i = 0; i < blocksCounter; i++) //check if big block above small ship 
	{
		for (int j = 0; j < ships[SmallShipIndx].getSize(); j++) {
			int tmpy = 0; int tmpx = 0;
			Point p = ships[SmallShipIndx].getPoint(j);
			tmpx = p.getx();
			tmpy = p.gety();
			char tmpch = blocks[i].getBlockCh();
			int tmpindx = checkDupBlocks(tmpx, tmpy - 1, tmpch);
			int sizeonsmallship = PileOfBlocksUp(SmallShipIndx);
			if (tmpindx >= 0) {
				if (sizeonsmallship > 2)
					*isPlayerDied = Keys::flag;
			}
		}
	}


	if (*switchShips == Keys::switchToSmallShip) // small ship case
	{
		for (int i = 0; i < blocksCounter; i++) { blocks[i].setCarry(0); }
		int sizeofpile = PileOfBlocks(dirx, diry, SmallShipIndx);
		updatedirs(sizeofpile, blocksCounter, SmallShipIndx);
		if(sizeofpile > 2)
			*isPlayerDied = Keys::flag;

		if (*key == Keys::Up) // move up together
		{
			for (int i = 0; i < blocksCounter; i++) //check if small block above small ship
			{
				if (blocks[i].getCarry() == 1) { blocks[i].moveBlock(blocks[i].getDirX(), blocks[i].getDirY()); }
				if (*colorsFlag) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ships->GetSmallShipColor()); }
			}
			ships[0].move(dirx, diry, isPlayerDied);
			if (*colorsFlag) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ships->GetBigShipColor()); }
		}
		else // move down or left or right
		{
			for (int i = 0; i < blocksCounter; i++) { blocks[i].setCarry(0); }
			if (ships[0].canMove(dirx, diry, isPlayerDied) || ships[0].canPushBlock(dirx, diry, isPlayerDied))
			{
				int sizeofpile = PileOfBlocks(dirx, diry, SmallShipIndx);
				updatedirs(sizeofpile, blocksCounter, SmallShipIndx);
			}

			if (*colorsFlag) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ships->GetSmallShipColor()); }
			ships[0].move(dirx, diry, isPlayerDied);
			for (int i = 0; i < blocksCounter; i++) //check if small block above small ship
			{
				if (*colorsFlag) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blocks->GetColor()); }

				if (blocks[i].getCarry() == 1) { blocks[i].moveBlock(blocks[i].getDirX(), blocks[i].getDirY()); }
				else if (blocks[i].isFallBlock()) {
					blocks[i].setDirX(0);
					blocks[i].setDirY(-1);
					blocks[i].moveBlock(blocks[i].getDirX(), blocks[i].getDirY());
				}
			}
		}


	}
	else if (*switchShips == Keys::switchToBigShip) // big ship case
	{
		int BigShipIndx = 1;
		int sizeOfPileSmall;


		if (*key == Keys::Up)
		{

			for (int i = 0; i < blocksCounter; i++) { blocks[i].setCarry(0);}
			int sizeofpile = PileOfBlocks(dirx, diry, BigShipIndx);
			updatedirs(sizeofpile, blocksCounter, BigShipIndx);

			for (int i = 0; i < blocksCounter; i++) //check if small block above big ship
			{
				if (*colorsFlag) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blocks->GetColor()); }
				if (blocks[i].getCarry() == 1) { blocks[i].moveBlock(blocks[i].getDirX(), blocks[i].getDirY()); }
			}

			if (*colorsFlag) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ships->GetBigShipColor()); }
			ships[1].move(dirx, diry, isPlayerDied);

			sizeOfPileSmall = PileOfBlocks(0, 1, SmallShipIndx);
			if (sizeOfPileSmall > 2)
				*isPlayerDied = Keys::flag;
		}
		else
		{

			for (int i = 0; i < blocksCounter; i++) { blocks[i].setCarry(0); }
			if (ships[1].canMove(dirx, diry, isPlayerDied) || ships[1].canPushBlock(dirx, diry, isPlayerDied))
			{
				int sizeofpile = PileOfBlocks(dirx, diry, BigShipIndx);
				updatedirs(sizeofpile, blocksCounter, BigShipIndx);
			}

			if (*colorsFlag) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ships->GetBigShipColor()); }
			ships[1].move(dirx, diry, isPlayerDied);
			for (int i = 0; i < blocksCounter; i++) //check if small block above small ship
			{
				if (*colorsFlag) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), blocks->GetColor()); }

				if (blocks[i].getCarry() == 1) { blocks[i].moveBlock(blocks[i].getDirX(), blocks[i].getDirY()); }
				else if (blocks[i].isFallBlock() && blocks[i].getCarry() == 0) {
					blocks[i].setDirX(0); 
					blocks[i].setDirY(-1);
					blocks[i].moveBlock(blocks[i].getDirX(), blocks[i].getDirY());
				}
			}
			sizeOfPileSmall = PileOfBlocks(0, 1, SmallShipIndx);
			if (sizeOfPileSmall > 2)
				*isPlayerDied = Keys::flag;

		}

	}
}
void GameManager::updatedirs(int sizeofpile, int blocksCounter, int ship_indx) {
	for (int i = 0; i < blocksCounter; i++) //check if small block above big ship
	{

		if ((sizeofpile <= 6) && (ship_indx == 1))
		{
			if (blocks[i].getCarry() == 1) {
				blocks[i].setDirX(dirx);
				blocks[i].setDirY(diry);
			}
		}
		else if ((sizeofpile <= 2) && (ship_indx == 0))
		{
			if (blocks[i].getCarry() == 1)
			{
				blocks[i].setDirX(dirx);
				blocks[i].setDirY(diry);
			}
		}
		else
		{
			blocks[i].setDirX(0);
			blocks[i].setDirY(0);

		}
	}
}

// fuction for carry blocks on ships
int GameManager::PileOfBlocks(int dir_x, int dir_y, int ship_indx) {
	int sizeofpile = 0; int sizeofpush = 0;
	if (dir_x == 1)
		sizeofpush = PileOfBlocksRight(ship_indx);
	else	if (dir_x == -1)
		sizeofpush = PileOfBlocksLeft(ship_indx);
	sizeofpile = PileOfBlocksUp(ship_indx);
	if (dir_x == 1 || dir_x == -1)
		return sizeofpush;
	return sizeofpile;
}

// fuction for carry blocks on ships 
int GameManager::PileOfBlocksUp(int ship_indx) {
	int i = 0; int blocksize = 0; char ch; int SizeOfPile = 0; int a = 0; int idx; char secship = '@';
	while (a < ships[ship_indx].getSize()) {
		int y = ships[ship_indx].getPoint(a).gety();
		int x = ships[ship_indx].getPoint(a).getx();
		if (ship_indx == 0) { secship = Keys::bigShipCh; };
		if (ship_indx == 1) { secship = Keys::smallShipCh; };
		while (((board.board[y][x] != Keys::emptyCh) && board.board[y][x] != Keys::wallCh) && (board.board[y][x] != secship) && (y > 0))
		{
			{
				ch = board.board[y][x];
				idx = checkDupBlocks(x, y, ch);
				if (idx != -1) {
					blocksize = blocks[idx].whatSize();
					if (blocks[idx].getCarry() == 0) {
						SizeOfPile += blocks[idx].whatSize();
						blocks[idx].setCarry(1);
					}
				}
			}
			y--;
		}
		a++;
	}
	return SizeOfPile;


}

// fuction for carry blocks on ships 
int GameManager::PileOfBlocksLeft(int ship_indx) {
	int i = 0; int blocksize = 0; char ch; int SizeOfPile = 0; int a = 0; int idx; char secship = '@';
	while (a < ships[ship_indx].getSize()) {
		int y = ships[ship_indx].getPoint(a).gety();
		int x = ships[ship_indx].getPoint(a).getx();
		if (ship_indx == 0) { secship = Keys::bigShipCh; };
		if (ship_indx == 1) { secship = Keys::smallShipCh; };
		while (((board.board[y][x] != Keys::emptyCh) && board.board[y][x] != Keys::wallCh) && (board.board[y][x] != secship) && (x > 0))
		{
			{
				ch = board.board[y][x];
				idx = checkDupBlocks(x, y, ch);
				if (idx != -1) {
					blocksize = blocks[idx].whatSize();
					if (blocks[idx].getCarry() == 0) {
						SizeOfPile += blocks[idx].whatSize();
						blocks[idx].setCarry(1);
					}
				}
			}
			x--;
		}
		a++;
	}
	return SizeOfPile;
}

// fuction for carry blocks on ships 
int GameManager::PileOfBlocksRight(int ship_indx) {
	int i = 0; int blocksize = 0; char ch; int SizeOfPile = 0; int a = 0; int idx; char secship = '@'; int maxboard_x = 80;
	while (a < ships[ship_indx].getSize()) {
		int y = ships[ship_indx].getPoint(a).gety();
		int x = ships[ship_indx].getPoint(a).getx();
		if (ship_indx == 0) { secship = Keys::bigShipCh; };
		if (ship_indx == 1) { secship = Keys::smallShipCh; };
		while (((board.board[y][x] != Keys::emptyCh) && board.board[y][x] != Keys::wallCh) && (board.board[y][x] != secship) && (x < maxboard_x))
		{
			{
				ch = board.board[y][x];
				idx = checkDupBlocks(x, y, ch);
				if (idx != -1) {
					blocksize = blocks[idx].whatSize();
					if (blocks[idx].getCarry() == 0) {
						SizeOfPile += blocks[idx].whatSize();
						blocks[idx].setCarry(1);
					}
				}
			}
			x++;
		}
		a++;
	}
	return SizeOfPile;
}


int GameManager::checkDupBlocks(int x, int y, char ch) {
	int i, j; int size; Point tmpP, Pcheck;
	Pcheck = { x,y,ch };
	for (i = 0; i < blocksCounter; i++) {
		size = blocks[i].whatSize();
		for (j = 0; j < size; j++)
		{
			tmpP = blocks[i].getPoint(j);
			if (Pcheck == tmpP)
				return i;
		}
	}
	return -1;
}


void GameManager::runTimer(int* timeCounter, int* flag,bool silent) // run timer function
{
	if (*timeCounter % 1 == 0) //run timer
	{
		timer.changeTime(flag,silent);
		*timeCounter = 0;
	}

	(*timeCounter)++;

}

int GameManager::whichBlockPushed(Point pBlock) // checks which block is pushed
{
	for (int i = 0; i < blocksCounter; i++)
	{
		int blockSize = blocks[i].whatSize();
		for (int j = 0; j < blockSize; j++)
		{
			if (pBlock == blocks[i].getPoint(j))
			{
				return i;
			}
		}
	}

	return Keys::flag;
}


bool GameManager::outOfLives() // checks if the player out of lives
{
	if (life == '1' || life == '0')
		return false;
	else
		return true;
}

bool GameManager::isPlayerDied(int looseLifeByShips, int outOfTime, bool silentFlag) // checks if the player died
{
	if (looseLifeByShips == Keys::flag)  // check if small ship died
	{
		if (!silentFlag)
		{
			system("cls");
			cout << "You killed The Small Ship!\n\nYou loose one life, be careful for next time!" << endl;
			Sleep(3500);
			system("cls");
		}
		return false;
	}
	else if (outOfTime == Keys::flag) // check if out of time
	{
		if (!silentFlag)
		{
			system("cls");
			cout << "Time's Up!\n\nYou loose one life, be faster for next time!" << endl;
			Sleep(3500);
			system("cls");
		}
		return false;
	}
	else if (looseLifeByShips == Keys::flag2)
	{
		if (!silentFlag)
		{
			system("cls");
			cout << "You killed By The Scary Ghost!\n\nYou loose one life, be careful for next time!" << endl;
			Sleep(3500);
			system("cls");
		}
		return false;
	}
	return true;
}

bool GameManager::playerWin() // checks if the player win
{
	if (ships[0].win() && ships[1].win())
		return true;
	else
		return false;
}

bool GameManager::wantToExit() // checks if the player want to exit the game
{
	if (exitGame)
		return true;
	else
		return false;
}


void GameManager::clearBoard() // clear board function
{
	for (int i = 0; i < MAX_ROWS; i++)
		for (int j = 0; j < MAX_COLS; j++)
			board.board[i][j] = ' ';

	board.ROWS = board.COLS = 0;
	board.ghostCounter = 0;
	board.blocksCounter = 0;
}

void GameManager::initBoard(const string& fileName) // initilize the board from the file
{
	clearBoard();

	ifstream file;
	file.open(fileName);

	readBoardFromFile(file);
	readShipsAndBlocksFromBoard();

	file.close();
}

void GameManager::readShipsAndBlocksFromBoard() // read the blocks and the ships from the board
{
	int currCol = 0, smallShipSize = 0, bigShipSize = 0, numOfBlocks = 0, blockIdx = 0, currRow = 0, idxG_S = 0, idxG_W = 0, i, j;
	char currCh;
	char cpyBoard[MAX_ROWS][MAX_COLS];

	for (i = 0; i < MAX_ROWS; i++)
		for (j = 0; j < MAX_COLS; j++)
			cpyBoard[i][j] = board.board[i][j];

	blocksCounter = board.findHowManyBlocks();

	blocks = new Block[blocksCounter];
	straightGhostsArr = new straightGhost[straightGhostCounter];
	wanderingGhostArr = new wanderGhost[wanderingGhostCounter];

	for (i = 0; i < MAX_ROWS; i++)
		for (j = 0; j < MAX_COLS; j++)
		{
			currCh = cpyBoard[i][j];

			if (currCh >= '1' && currCh <= '9')
			{
				insertBlocksFromBoard(i, j, currCh, blockIdx, cpyBoard);
				blockIdx++;
			}
			else if (currCh == Keys::smallShipCh)
			{
				ships[0].setShipPoint(&board, j, i, currCh);
			}
			else if (currCh == Keys::bigShipCh)
			{
				ships[1].setShipPoint(&board, j, i, currCh);
			}
			else if (currCh == Keys::HorizonalGhost || currCh == Keys::VerticalGhost)
			{
				straightGhostsArr[idxG_S].setGhostPoint(&board, j, i, currCh, idxG_S);
				idxG_S++;
			}
			else if (currCh == Keys::WanderingGhost)
			{
				wanderingGhostArr[idxG_W].setGhostPoint(&board, j, i, currCh, idxG_W);
				idxG_W++;
			}
		}
}

void GameManager::insertBlocksFromBoard(int row, int col, char ch, int blockIdx, char board1[][MAX_COLS]) // insert blocks from board function
{
	if (ch != board1[row][col])
	{
		return;
	}
	else
	{
		if (board1[row + 1][col - 1] == ch)
		{
			blocks[blockIdx].setBlockPoint(&board, col, row, ch);
			board1[row][col] = Keys::emptyCh;
			insertBlocksFromBoard(row + 1, col - 1, ch, blockIdx, board1);
		}
		else if (board1[row - 1][col] == ch)
		{
			blocks[blockIdx].setBlockPoint(&board, col, row, ch);
			board1[row][col] = Keys::emptyCh;
			insertBlocksFromBoard(row - 1, col, ch, blockIdx, board1);
		}
		else if (board1[row][col + 1] == ch) // check right
		{
			blocks[blockIdx].setBlockPoint(&board, col, row, ch);
			board1[row][col] = Keys::emptyCh;
			insertBlocksFromBoard(row, col + 1, ch, blockIdx, board1);
		}
		else if (board1[row + 1][col] == ch) // check down
		{
			blocks[blockIdx].setBlockPoint(&board, col, row, ch);
			board1[row][col] = Keys::emptyCh;
			insertBlocksFromBoard(row + 1, col, ch, blockIdx, board1);
		}
		else if (board1[row][col - 1] == ch)
		{
			blocks[blockIdx].setBlockPoint(&board, col, row, ch);
			board1[row][col] = Keys::emptyCh;
			insertBlocksFromBoard(row, col - 1, ch, blockIdx, board1);
		}
		else
		{
			blocks[blockIdx].setBlockPoint(&board, col, row, ch);
			board1[row][col] = Keys::emptyCh;
			return;
		}
	}
}

void GameManager::readBoardFromFile(ifstream& file) // read board from file function
{
	int currCol = 0, smallShipSize = 0, bigShipSize = 0, numOfBlocks = 0, blockIdx = 0;
	bool isHeader = true;
	unsigned char character;

	while (!file.eof()) // get the walls to the board
	{
		character = file.get();

		if (isHeader) // if the line is over the three line of the board
		{

			while (character != '\n')
			{
				if (character != '&')
					board.board[board.ROWS][currCol] = character;
				else
					board.board[board.ROWS][currCol] = Keys::emptyCh;

				currCol++;

				if (board.ROWS == 0)
					board.COLS++;

				character = file.get();
			}

			board.board[board.ROWS][currCol] = '\0';
			board.ROWS++;
			currCol = 0;
			if (board.ROWS == 3)
				isHeader = false;
		}
		else
		{
			if (character == Keys::wallCh)
			{
				board.board[board.ROWS][currCol] = character;
			}
			else if (character == '\n')
			{
				board.board[board.ROWS][currCol] = '\0';
				currCol = 0;
				board.ROWS++;
			}
			else if (character == Keys::ExitCh)
				board.board[board.ROWS][currCol] = character;
			else if (character == Keys::bigShipCh || character == Keys::smallShipCh)
				board.board[board.ROWS][currCol] = character;
			else if (character >= '1' && character <= '9')
				board.board[board.ROWS][currCol] = character;
			else if (character == Keys::HorizonalGhost || character == Keys::VerticalGhost)
			{
				board.board[board.ROWS][currCol] = character;
				straightGhostCounter++;
			}
			else if (character == Keys::WanderingGhost)
			{
				board.board[board.ROWS][currCol] = character;
				wanderingGhostCounter++;
			}

			if (character != '\n')
				currCol++;
		}
	}
}

int GameManager::findBlockIdx(char ch) // find block idx
{
	int size = blocksCounter, res = 0, i;

	for (i = 0; i < size; i++)
		if (blocks[i].getBlockCh() == ch)
			res = i;

	return res;
}

void GameManager::insertFullLine(int col) // insert full line function
{
	while (col < board.COLS)
	{
		board.board[board.ROWS][col] = Keys::emptyCh;
		col++;
	}
}

string GameManager::findResultFile()
{
	string resFile;

	if (boardNum == '1')
		resFile = "tb01.result.txt";
	else if (boardNum == '2')
		resFile = "tb02.result.txt";
	else // boardNum == '3'
		resFile = "tb03.result.txt";

	return resFile;
}


