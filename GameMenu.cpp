#include "GameMenu.h"
class PlayGame;


void GameMenu::printMenu() // print menu function
{
    if (colorsFlag)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "Game Menu :\n" << "(1) Start a full game\n" << "(2) Play only in board number 1\n" <<
        "(3) Play only in board number 2\n" << "(4) Play only in board number 3\n" << "(6) Set Colors\n" << 
        "(7) Set only black and white colors (default option)\n" <<"(8) Present instructions and keys\n" << "(9) EXIT" << endl;
}
void GameMenu::printPreMenu() {
    cout << "choose game mode" << endl;
    cout << "(1) load\n(2) load silent\n(3) save\n(4) exit\n";
}
void GameMenu::preUserChoice()
{
    printPreMenu();
    char userInput = getUserInput();
    ifstream MenuChoiceFile("menu.choice.txt");
    string userInputStr = "";
    int firstIter = 1;

    if (MenuChoiceFile.is_open())
    {
        getline(MenuChoiceFile, userInputStr); // read the first line
    }

    while (userInput < '1' && userInput > '4')
    {
        cout << "Please enter a correct input! try again..." << endl;
        userInput = getUserInput();
    }

    while (userInputStr == "" && (userInput == '1' || userInput == '2'))
    {
        cout << "We cant load this game!.. Try other option: ";
        userInput = getUserInput();
    }

    if (userInput == '1' || userInput == '2' || userInput == '3')
    {
        system("cls");
        hideCursor();
        userChoice(userInputStr, userInput, &firstIter);
    }

    if (userInput == '4') 
    {
        system("cls");
        cout << "Good Bye!" << endl;
    }
  
}

void GameMenu::resetMenuFile()
{
    ofstream MenuChoice("menu.choice.txt", ios_base::out | ios_base::trunc);
    MenuChoice.close();

}

void GameMenu::userChoice(string modeStr, char mode, int* firstIterFlag)  // set the game from the user choice
{
    int gameFlag = 1, iStr = 0; 
    char userInput = '1';
    int sizeStr = modeStr.size();

    if (*firstIterFlag)
        resetMenuFile();
    else
        *firstIterFlag = 0;

    ofstream MenuChoice("menu.choice.txt", ios_base::out | ios_base::app);

    while (gameFlag)
    {
        if (mode == '3')
        {
            printMenu();
            userInput = getUserInput();
        }
        else // mode == '1' || '2'
        {
            if (iStr < sizeStr)
                userInput = modeStr[iStr];
            else
                userInput = Keys::ExitGame;
        }


        switch (userInput)
        {
        case Keys::Play:
            MenuChoice << userInput;
            MenuChoice.close();
            playFullGame(&gameFlag, mode);
            break;
        case Keys::ExitGame: // player want to exit immidiatly
            MenuChoice << userInput;
            MenuChoice.close();
            goOut();
            gameFlag = 0;
            break;
        case BOARD_1:  // player want to play only with board 1 
            MenuChoice << userInput;
            MenuChoice.close();
            playSingleBoard(BOARD_1, &gameFlag, mode);
            break;
        case BOARD_2:// player want to play only with board 2
            MenuChoice << userInput;
            MenuChoice.close();
            playSingleBoard(BOARD_2, &gameFlag, mode);
            break;
        case BOARD_3: // player want to play only with board 3 
            MenuChoice << userInput;
            MenuChoice.close();
            playSingleBoard(BOARD_3, &gameFlag, mode);
            break;
        case SET_COLORS:  // player want to play  with colors
            MenuChoice << userInput;
            colorsFlag = 1;
            if (mode == '3')
            {
                cout << "color mode on!" << endl;
                Sleep(2000);
                system("cls");
            }
            break;
        case SET_BLACK_AND_WHITE:  // player want to play without colors
            MenuChoice << userInput;
            colorsFlag = 0;
            if (mode == '3')
            {
                cout << "color mode off!" << endl;
                Sleep(2000);
                system("cls");
            }
            break;
        }

        iStr++;
    }
}

string GameMenu::findBoardFile()
{
    string resStr;

    if (currLevel == '1')
        resStr = "tb01.screen.txt";
    else if (currLevel == '2')
        resStr = "tb02.screen.txt";
    else //currLevel == '3'
        resStr = "tb03.screen.txt";

    return resStr;
}


void GameMenu::playFullGame(int* flag,char mode) // player wants to play full game
{
    char life = '3';
    int currStepFile = 0, currRandFile = 0, currResFile = 0, resTest = 1;
    bool stillPlay = true, winGame = false, exitGame = false, startNewGame = true, silentFlag = false;
    string str;
    bool silent;
    system("cls");
    hideCursor();

    while (stillPlay && *flag)
    {
        str = findBoardFile();
        system("cls");
        if (mode == '1') //load
        {
            PlayGameFromFiles letsPlay(life, currLevel, &colorsFlag, str);
            letsPlay.run(&currStepFile, &currRandFile, &currResFile, silentFlag, &resTest);
            stillPlay = letsPlay.outOfLives(); // still have life
            winGame = letsPlay.playerWin(); // player win
            exitGame = letsPlay.wantToExit(); //player want to exit

        }
        else if (mode == '2') //load silent
        {           
            silentFlag = true;
            PlayGameFromFiles letsPlay(life, currLevel, &colorsFlag, str);
            letsPlay.run(&currStepFile, &currRandFile, &currResFile, silentFlag, &resTest);
            stillPlay = letsPlay.outOfLives(); // still have life
            winGame = letsPlay.playerWin(); // player win
            exitGame = letsPlay.wantToExit(); //player want to exit

        }

        else if (mode == '3') //save
        {
            if (startNewGame)
            {
                deleteDetailsFromFiles();
                startNewGame = false;
            }
            PlayRegularGame letsPlay(life, currLevel, &colorsFlag, str);
            letsPlay.run();
            stillPlay = letsPlay.outOfLives(); // still have life
            winGame = letsPlay.playerWin(); // player win
            exitGame = letsPlay.wantToExit(); //player want to exit

        }
        
        if (!winGame)
            life -= 1;

        system("cls");
        if (!stillPlay ) // loose the game
        {
            if (mode != '2' && !winGame)
            {
                cout << "<--------------------------------!!! YOU LOOSE !!!------------------------------->" << endl;
                Sleep(2000);
                system("cls");         
            }

            currStepFile = 0; currRandFile = 0;

        }
        else if (winGame) // player win 
        {
            currLevel += 1;
            if (currLevel <= '3' && mode != '2')
            {
                cout << "<------------------------------- !!! LEVEL UP !!! ---------------------------->" << endl;
                Sleep(2000);
                system("cls");
            }

            if (currLevel == '2' && mode != '2')
                cout << "<------------------------------- !!! LEVEL 2 !!! ------------------------------>" << endl;
            else if (currLevel == '3' && mode != '2')
                cout << "<------------------------------- !!! LEVEL 3 !!! ------------------------------>" << endl;
            else if (mode != '2')
            {
                cout << "<------------------------ !!! YOU FINISHED THE GAME !!! ----------------------->" << endl;
                currLevel = '1';
                Sleep(2000);
                system("cls");
            }
            currStepFile = 0; currRandFile = 0; currResFile = 0;

            stillPlay = true;
            winGame = false;
        }

        if (exitGame) // player want to exit
        {
            *flag = 0;
            if (mode != '2')
                goOut();
        }
    }

    currLevel = '1';

    if (mode == '2')
    {
        if (resTest)
            cout << "congratulation! Test Passed" << endl;
        else
            cout << "Ohh God! Test Failed" << endl;
        Sleep(2000);
        *flag = 0;
        goOut();
    }
}

// delete detais from files
void GameMenu::deleteDetailsFromFiles()
{
    ofstream file1Rand("tb01.rand.txt" , ios_base::out | ios_base::trunc);
    file1Rand.close();
    ofstream file2Rand("tb02.rand.txt", ios_base::out | ios_base::trunc);
    file2Rand.close();
    ofstream file3Rand("tb03.rand.txt", ios_base::out | ios_base::trunc);
    file3Rand.close();

    ofstream file1Res("tb01.result.txt", ios_base::out | ios_base::trunc);
    file1Res.close();
    ofstream file2Res("tb02.result.txt", ios_base::out | ios_base::trunc);
    file2Res.close();
    ofstream file3Res("tb03.result.txt", ios_base::out | ios_base::trunc);
    file3Res.close();

    ofstream file1Steps("tb01.steps.txt", ios_base::out | ios_base::trunc);
    file1Steps.close();
    ofstream file2Steps("tb02.steps.txt", ios_base::out | ios_base::trunc);
    file2Steps.close();
    ofstream file3Steps("tb03.steps.txt", ios_base::out | ios_base::trunc);
    file3Steps.close();

}


void GameMenu::playSingleBoard(char boardNum, int* flag, char mode) // player wants to play single board game
{

    char life = '3', userInput;
    int currStepFile = 0, currRandFile = 0 , currResFile = 0, resTest = 1;
    bool stillPlay = true, winGame = false, exitGame = false, startNewGame = true, silentFlag = false;;

    currLevel = boardNum - 1;
    string str = findBoardFile();

    system("cls");
    hideCursor();
    while (stillPlay && *flag)
     {           
        if (mode == '1') //load
        {
            PlayGameFromFiles letsPlay(life, currLevel, &colorsFlag, str);
            letsPlay.run(&currStepFile, &currRandFile, &currResFile, silentFlag, &resTest);
            stillPlay = letsPlay.outOfLives(); // still have life
            winGame = letsPlay.playerWin(); // player win
            exitGame = letsPlay.wantToExit(); //player want to exit
        }
        else if (mode == '2') //load silent
        {
            silentFlag = true;
            PlayGameFromFiles letsPlay(life, currLevel, &colorsFlag, str);
            letsPlay.run(&currStepFile, &currRandFile, &currResFile, silentFlag, &resTest);
            stillPlay = letsPlay.outOfLives(); // still have life
            winGame = letsPlay.playerWin(); // player win
            exitGame = letsPlay.wantToExit(); //player want to exit

        }

        else if (mode == '3') //save
        {
            if (startNewGame)
            {
                deleteDetailsFromFiles();
                startNewGame = false;
            }
            PlayRegularGame letsPlay(life, currLevel, &colorsFlag, str);
            letsPlay.run();
            stillPlay = letsPlay.outOfLives(); // still have life
            winGame = letsPlay.playerWin(); // player win
            exitGame = letsPlay.wantToExit(); //player want to exit
        }


        if (!winGame)
            life -= 1;

        system("cls");

        if (!stillPlay) // restart the game when player life == 0 (loose)
        {
            if (mode != '2' && !winGame)
            {
                cout << "<------------------------------!!! YOU LOOSE !!!------------------------------>" << endl;
                Sleep(2000);
                system("cls");
            }
            stillPlay = false;
            currStepFile = 0; currRandFile = 0; currResFile = 0;

        }
        else if (winGame) // player win 
        {
            if (mode != '2')
            {
                cout << "<--------------------------------!!! YOU WIN !!!------------------------------->" << endl;
                Sleep(2000);
                system("cls");

            }
            stillPlay = false;
            currStepFile = 0; currRandFile = 0; currResFile = 0;
        }


        if (exitGame) // player want to exit
        {
            *flag = 0;
            if (mode != '2')
                goOut();
        }
    }

    if (mode == '2')
    {
        if (resTest)
            cout << "congratulation! Test Passed" << endl;
        else
            cout << "Ohh God! Test Failed" << endl;
        Sleep(2000);
        goOut();
        *flag = 0;
    }
}


char GameMenu::getUserInput() // set the user choice from menu
{
    char userInput;
    int inInstructions = 0;
    cin >> userInput;

    while (userInput != Keys::Play && userInput != Keys::ExitGame && userInput != BOARD_1 && userInput != BOARD_2 && userInput != BOARD_3
         && userInput != SET_BLACK_AND_WHITE && userInput != SET_COLORS)
    {
        if (userInput != Keys::Instructions)
        {
            cout << "Please enter correct number!" << endl;
        }
        else // pressed 8 to instructions
        {
            inInstructions++;
            system("cls");
            printInstructions();
            cin >> userInput;
            system("cls");
            printMenu();
        }
        cin >> userInput;
    }

    return userInput;
}

void GameMenu::printInstructions() // prints the instructions
{
    cout << "Thunderbirds Instructions:\n\nYou need to drive to the exit area ('E' char)\nwith both ships (small one '@' char and big one with '#' char).\n" <<
        "You have also time limit to do it!\n\n" << "You are loosing one life when:\n1. The time finished.\n2.A big block (more than 2 chars) falls on your small ship.\n" <<
        "3.A ghost touches a ship\nYou have only 3 lifes! Be carful!\n" <<
        "\nKeys:\n\nLEFT                        |   a or A\nRIGHT                       |   d or D\nUP                          |   w or W\nDOWN                        |   x or X\nSwitched to the Big Ship    |   b or B\nSwitched to the Small Ship  |   s or S (starting ship)" <<
        "\n\nPlease enter any char to go to the menu."
        << endl;
}

void GameMenu::goOut() // player want to end the game
{
    system("cls");
    cout << "Good Bye!\n" << endl;
}



