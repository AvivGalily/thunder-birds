#include "board.h"


bool Board::isWall(int x, int y) // checks if this is wall
{
	if (board[y][x] == Keys::wallCh)
		return true;

	return false;
}

void Board::printBoard(int* colorsFlag) // print board function
{
	if (*colorsFlag)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BOARD_COLOR);

	for (int row = 0; row < 25; ++row) 
		cout << board[row];

}

int Board::findHowManyBlocks() // fib=nd how many blocks on the board
{
	char tmpBoard[MAX_HIGHT][MAX_WIDTH];
	char currCh;
	int i, j, counter = 0;

	for (i = 0; i < MAX_HIGHT; i++)
		for (j = 0; j < MAX_WIDTH; j++)
			tmpBoard[i][j] = board[i][j];

	for (i = 0; i < MAX_HIGHT; i++)
		for (j = 0; j < MAX_WIDTH; j++)
		{
			currCh = tmpBoard[i][j];

			if (currCh >= '1' && currCh <= '9')
			{
				counter++;
				deleteBlockFromBoard(i, j, currCh, tmpBoard);
			}
		}

	return counter;
}



void Board::deleteBlockFromBoard(int row, int col, char ch, char board[][MAX_WIDTH]) // delete blocks from the board function
{
	if (ch != board[row][col])
		return;
	else
	{	
		 if (board[row][col + 1] == ch) // check right
		 {
			board[row][col] = Keys::emptyCh;
			deleteBlockFromBoard(row, col + 1, ch, board);
		 }
		else if (board[row + 1][col] == ch) // check down
		{
			board[row][col] = Keys::emptyCh;
			deleteBlockFromBoard(row + 1, col, ch, board);
		}
		else if (board[row - 1][col] == ch)
		{
			board[row][col] = Keys::emptyCh;
			deleteBlockFromBoard(row-1, col , ch, board);
		}
		else if (board[row][col - 1] == ch)
		{
			board[row][col] = Keys::emptyCh;
			deleteBlockFromBoard(row, col - 1, ch, board);
		}
		else if (board[row - 1][col] == ch)
		{
			board[row][col] = Keys::emptyCh;
			deleteBlockFromBoard(row - 1, col, ch, board);
		}
		else 
		{
			board[row][col] = Keys::emptyCh;
			return;
		}
	}
}




