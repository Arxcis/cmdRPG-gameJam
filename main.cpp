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


#include <vector>
#include <iostream>
#include <string>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

using namespace std;


//// ----------------------------- STRUCTS ------------------------------////

struct Window {

    //  ------- Struct attributes -----------

        // Here is the 2d-array that is responsible for holding the information
        //  about the window-state at any given time. 

    const vector<string> windowEmpty = {
    
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "                                                                      \n",
    "\n\n\n\n\n"
    };


        // Coordinates to important points in the windowMatrix

    const int CENTER[2] = {35, 10};
    const int UPPER_LEFT[2] = { 0, 0 };
    const int UPPER_RIGHT[2] = { 70, 0 };
    const int LOWER_LEFT[2] = { 0,20 };
    const int LOWER_RIGHT[2] = { 70,20 };

        // Arrays cannot be assigned to other arrays. So here we need to use
        //  vectors.
    vector<string> windowState = windowEmpty;


    // ---------- Struct methods  ---------

    void clearWindow() {     windowState = windowEmpty;    }


    // @param : int row - a number between 0-19, specifies which row to change
    // @param : string line - inputs a string of length 71, the entire row.
    // @return: void

    // WORKS LIKE A CHARM !!
    void setLine(int row, string line) {

        windowState[row] = line;
    }


    // @param : int row - a number between 0-19, specifies which row to change
    // @param : int column - a number between 0-69, starting post of the word.
    // @param : string word - a word of any lenght to be inserted at position.
    // @return: void

    // WORKS like A CHARM !! 
    void setWord(int column, int row, string word){

        // Debug info
        //cout << row << ", "<< column << ", " << word.length() << "\n"; 

        for (int i = column, j= 0; i < (column + word.length()); i++, j++){

            // Makes sure that the end of line is not overwritten.
            if ( i <= 69) {
                //cout << word[j];
                windowState[row][i] = word[j];
            }

        }
    }

    void coutWindow()  {

        for (int i=0; i < 20; i++){
            cout << windowState[i];
        }
    }
}; 

// ------------------------------ GLOBALS -----------------------------------//

char g_key = ' ';
Window w; 


//// ----------------------- FUNCTION DECLARATIONS ------------------------////


// -- Utility functions ----
void clearScreen();
void zzz();

// ----- View functions -----
void openingTitle();
void mainMenu();


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

    g_key = ' ';            // Resets the global key, so it works as 
                                  //  as intended. 
    for (int i=0; i < 30; i++) {  // Prints 35 \n - endline characters.
        cout << '\n';             //  effectively wipes the screen clean.
    }
}


// --------------------------------- VIEWS ----------------------------------//
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
//   ASCII - resolution:  70(+1 newline character) x 20 characters.
// 



// VIEW: openingView - The first view that meets the player after loading 
//                      the game.

void openingView(){

    int count = 1;

    while(count < 6){

        resetScreen();

        w.setWord(12, 7, "The");
        w.setWord(14, 8, "Wizard's");
        w.setWord(16, 9, "Holiday");

        if(count % 2 == 0){
            w.setWord(16, 10, "-----------            ");
        } else {
            w.setWord(16, 10, "            -----------");
        }

        w.setWord(17, 11, "Copyright 2016");

        w.coutWindow();

        count ++;

        zzz(1000);
    }

    mainMenu();
}
// VIEW: travelView between fromLocation -> toLocation, this takes length time
void travelView(string fromLocation, string toLocation, int length)
{
	
}
// VIEW: mainMenu - 
void mainMenu(){

    resetScreen();

    w.clearWindow();
    w.setWord(w.CENTER[0]-5,  8, "[N]EW GAME");
    w.setWord(w.CENTER[0]-5, 10, "[C]ONTINUE");
    w.setWord(w.CENTER[0]-5, 12, "[E]XIT"    );

    w.coutWindow();
}


//// ------------------------------ MAIN ----------------------------------////



int main()
{

    openingView();

    return 0;
}








