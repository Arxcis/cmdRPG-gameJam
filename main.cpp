


// File    : main.cpp
// Created : 12.09.2016
//      by : Jonas Solsvik
//
// Authors : 
// 
// Description : This is a version of the game proposed at the cmdRPG-gamejam,
//                held at baserom on saturday and sunday.
//                This version tries to keep the entire source-code in a
//                single file. 


#include <iostream>
#include <ncurses.h>   // Have to add "-lncurses" in Build Settings under 
                       //  other Linker flags.

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

using namespace std;

//// ----------------------- FUNCTION DECLARATIONS ------------------------////

void clearScreen();
void zzz();

void openingTitle();
void mainMenu();

void newGame1();
void newGame2();

// ------------------------------ GLOBALS -----------------------------------//

namespace global {
    char key = ' ';
} 

//// ------------------------------ MAIN ----------------------------------////


int main(){

    // ----- INIT ncurses and openingSequence
    initscr();
    openingTitle();

    return 0;
}


//// ------------------------ FUNCTION DEFINITIONS  ---------------------- ////

void zzz(int milliseconds)        // cross-platform sleep function
{
    #ifdef WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif // win32
}

void resetScreen(){

    global::key = ' ';            // Resets the global key, so it works as 
                                  //  as intended. 
    for (int i=0; i < 35; i++) {  // Prints 35 \n - endline characters.
        cout << '\n';             //  effectively wipes the screen clean.
    }
}


// ----------------------------- VIEWCARDS ----------------------------------//
//   Comment:
//    The following functions represent one view.
//     Each view - function has the following steps:
//       1.  Clear the screen
//       2.  Print out the view
//       3.  Ask for user key-input
//       4.  Make a descision based on that input
//
//    To make the game appear consistent across all views we have to     
//     standardize the width and height of each view.
//
//   ASCII - resolution:  68 x 20 characters.
// 


void openingTitle(){

    resetScreen();       // Always call resetScreen() on top of a card.

cout<< "===================================================================\n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                  THE                                              \n"
    << "                    WIZARDS                                        \n"
    << "                     HOLLIDAY                                      \n"
    << "                    ----------                                     \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                      Enter to continue.....       \n"
    << "===================================================================\n";

    cin.ignore(); cin.clear();
    mainMenu();
}

void mainMenu(){

    // Make sure that a valid key has been entered.
    while(toupper(global::key) != 'N' && 
          toupper(global::key) != 'Q'){

        resetScreen();       // Always call resetScreen() on top of a card.


cout<< "===================================================================\n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                         MAIN MENU                                 \n"
    << "                    -------------------                            \n"
    << "                                                                   \n"
    << "                       [N]EW GAME                                  \n"
    << "                                                                   \n"
    << "                       [Q]UIT                                      \n"
    << "                                                                   \n"
    << "                    -------------------                            \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                      [N , Q] + Enter              \n"
    << "===================================================================\n";
    cin >> global::key;  
    cin.ignore(); cin.clear();

    }   
        // Switch descision statement after the while-loop is broken.
    switch(toupper(global::key)){

        case 'N':
            newGame1();
            break;

        case 'Q':
            openingTitle();
            break;
        default:
            break;
    }
}

void newGame1(){

    resetScreen();       // Always call resetScreen() on top of a card.

cout<< "===================================================================\n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "   In the year of 1399 an English magician serves as               \n"
    << "    a luxury guard for an English noble’s son. At the              \n"
    << "    age of 5, the son, full with pranks and the attitude           \n"
    << "    of a spoiled brat, annoys the magician to insanity.            \n"
    << "    Through sheer desperation and a longing for peace,             \n"
    << "    the magician sets out on a vacation to Norway,                 \n"
    << "    the only remote enough country he knows of, and                \n"
    << "    where he hopes to find absolutely nothing that                 \n"
    << "       can bother him but rain, wind and snow....                  \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "===================================================================\n";

    cin.ignore(); cin.clear();

    newGame2();
}

void newGame2(){

    int y, x;          // Store position of cursor
    resetScreen();       // Always call resetScreen() on top of a card.


        // Here it would have been awesome with som sort of animation.
        //  using sleep and line jumping in some sort of clever way.

cout<< "===================================================================\n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "    Sailing the seas...                                            \n"
    << "                                                                   \n"
    << "                                                                   \n";
    getyx(stdscr, y, x);              // save current pos

cout<< "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "                                                                   \n"
    << "===================================================================\n";

    cout << x << " , " <<y;

    int i;
    while(1){

        move(y, 0);            // ncurses - move(x,y)  - moves the cursor.

        // Y U NO WORK MOVE(y, x) :'(  ???????????? 

        clrtoeol();            // ncurses - clrtoeol() - clears a line.

        if(i % 2 == 0){

cout <<"       YORK  - - - - - - - -  >  BERGEN                            \n";

        }

        zzz(1000);
        i++;
    }

    cin.ignore(); cin.clear();

    mainMenu();
}