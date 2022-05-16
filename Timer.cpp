#include "Timer.h"

Timer::Timer(int x1, int x2, int x3, int y, char ch1, char ch2) // C'tor
{
	timerBody[0] = Point(x1, y, ch1);
	timerBody[1] = Point(x2, y, ch2);
	timerBody[2] = Point(x3, y, ch2);
}

void Timer::setBoard(Board* pb) 
{
	for (int i = 0; i < TimerSize; i++)
		timerBody[i].setBoard(pb);

	pboard = pb;
}

void Timer::draw(char units, char tens, char hundreds) // draw timer on board
{
	timerBody[0].draw(hundreds);
	timerBody[1].draw(tens);
	timerBody[2].draw(units);
}

void Timer::changeTime(int* flag, bool silent)
{
	char hundreds = pboard->get(9, 1);
	char tens = pboard->get(10, 1);
	char units = pboard->get(11, 1);
	bool isDown = true;


	if (units == '0' && tens == '0' && hundreds != Keys::emptyCh)
	{
		hundreds = hundreds - 1;
		units = tens = '9';

		if (hundreds == '0')
			hundreds = Keys::emptyCh;
		isDown = false;
	}
	else if (units == '0' && tens >= '1' && isDown)
	{
		tens = tens - 1;
		units = '9';

		if (tens == '0' && hundreds == Keys::emptyCh)
			tens = Keys::emptyCh;
		isDown = false;
	}

	else if (units >= '1' && isDown)
	{
		units = units - 1;
		isDown = false;
	}

	if (units == '0' && tens == Keys::emptyCh && hundreds == Keys::emptyCh)
		*flag = Keys::flag; // exit

	timerBody[0].setPoint(9, 1, hundreds);
	timerBody[1].setPoint(10, 1, tens);
	timerBody[2].setPoint(11, 1, units);
	if (!silent) 
	{
	draw(units, tens, hundreds);
    }
}
