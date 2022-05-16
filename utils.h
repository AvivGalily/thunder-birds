#ifndef _UTILS_H_
#define _UTILS_H_

struct Keys {
	constexpr static int ESC = 27;
	constexpr static char Up = 'w';
	constexpr static char Right = 'd';
	constexpr static char Down = 'x';
	constexpr static char Left = 'a';
	constexpr static int Instructions = '8';
	constexpr static int Play = '1';
	constexpr static char ExitGame = '9';
	constexpr static char smallShipCh = '@';
	constexpr static char bigShipCh = '#';
	constexpr static char wallCh = 'W';
	constexpr static char emptyCh = ' ';
	constexpr static int flag = -1;
	constexpr static int flag2 = -2;
	constexpr static char switchToSmallShip = 's';
	constexpr static char switchToBigShip = 'b';
	constexpr static char smallBlockCh = '1';
	constexpr static char bigBlockCh = '2';
	constexpr static char ExitCh = 'E';
	constexpr static char HorizonalGhost = '$';
	constexpr static char VerticalGhost = '!';
	constexpr static char WanderingGhost = '%';

};

#endif