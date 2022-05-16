#ifndef _TIMER_H_
#define _TIMER_H_

#include "Point.h"
#include "utils.h"
#include "board.h"
#include "io_utils.h"

class Timer
{
	Board* pboard = nullptr;
	enum { TimerSize = 3 , TIME_COLOR = 4};
	Point timerBody[TimerSize];
	int* colorsFlag;

public:
	Timer(int x1, int x2, int x3, int y ,char ch1, char ch2);
	void setBoard(Board* pb); // set board
	void draw(char units, char tens, char hundreds);
	void changeTime(int* flag, bool silent);
};

#endif