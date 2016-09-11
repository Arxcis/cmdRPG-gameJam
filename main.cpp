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

// struct Window {}
// Description : This struct is used to create the window object. This object
//                is very important to the game. The window object holds
//                information about what is on the screen at any given time.
//                It also holds methods to change what is on the screen.
//
struct Window {

    //  --------- Struct attributes ----------- //
    //
    // Description : Constant which works as a template, whenever we need to 
    //                "clean" the window object.
    //
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


    // Description : Constants to be used for specifying relative coordinates.
    //                Makes it really easy to change look of the game in one
    //                place. 
    //              
    const int WIDTH = 70;
    const int HEIGHT = 20;
    const int CENTER[2] = { WIDTH/2, HEIGHT/2 };
    const int UPPER_LEFT[2] = { 0, 0 };
    const int UPPER_RIGHT[2] = { WIDTH, 0 };
    const int LOWER_LEFT[2] = { 0, HEIGHT };
    const int LOWER_RIGHT[2] = { WIDTH, HEIGHT };


    // Description : A vector which holds the state of the window object.
    // A 
    // Arrays cannot be assigned to other arrays. So here we need to use
    //  a vector.
    //
    vector<string> windowState = windowEmpty;


    // ---------------- Struct methods  --------------- // 
    //
    // Description : Overwrites entire window object, with a blank template.
    //
    //
    void clearWindow() {     windowState = windowEmpty;    }


    // Description : Replaces an entire row of the window object, with a new.
    //
    // @param : int row - a number between 0-19, specifies which row to change
    // @param : string line - inputs a string of length 71, the entire row.
    // @return: void
    //
    //
    void setLine(int row, string line) {

        windowState[row] = line;
    }


    // Description : Places a word at a specified location within the window.
    //               If a word overflows the window, it gets cut off.
    //
    // @param : int row - a number between 0-19, specifies which row to change
    // @param : int column - a number between 0-69, starting pos. of the word.
    // @param : string word - a word of any lenght to be inserted at position.
    // @return: void
    //
    //
    void setWord(int column, int row, string word){

        for (int i = column, j= 0; i < (column + word.length()); i++, j++){

            
            if ( i <= 69) {          // Makes sure that the end of line is not
                                     //  overwritten.
                windowState[row][i] = word[j];
            }

        }
    }


    // Description : Prints the entire window.
    //
    //
    void coutWindow()  {

        for (int i=0; i < 20; i++){
            cout << windowState[i];
        }
    }
}; 





// ------------------------------ GLOBALS -----------------------------------//

char globalKey = ' ';
Window w; 





//// ----------------------- FUNCTION DECLARATIONS ------------------------////

// ----- View functions ----- //
void openingView();
void mainMenuView();
void travelView();

// ------ Utility functions ---- //
void zzz(int milliseconds);                   // Cross platform sleep
void resetScreen();           // Prints 30 \n-characters.








//// ------------------------ FUNCTION DEFINITIONS  ---------------------- ////

//                                                                           //
// ----------------------------- VIEW FUNCITONS -----------------------------//
//   Comment:
//    The following functions represent one view.
//     Each view - function can have the following steps:
//       1.  Clear the screen
//       2.  Print out the new view
//       3.  Ask for user key-input to globalKey;
//       4.  Make a descision based on that input
//
//    To make the game appear consistent across all views we have to     
//     standardize the width and height of each view.
//     The window object should make sure that width and high are consistent
//     across views. 
//
//   ASCII - resolution:  70(+1 newline character) x 20 characters.
//
 

// VIEW: openingView - The first view that meets the player after loading 
//                      the game.
//
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

    mainMenuView();
}


// VIEW: travelView - Shows animation of travelling between two cities.
//       @param - string fromLocation - name of starting location
//       @param - string toLocation   - name of destination
//       @param - int    length       - animation time in seconds. 
void travelView(string fromLocation, string toLocation, int length)
{
    resetScreen();
    string distance;
    int halfWay = length / 2; //this is unprecise
    w.setWord(w.CENTER[0] - fromLocation.length() - halfWay, w.CENTER[1], fromLocation);
    for (int i = 0; i < length; i++)
    {
        w.setWord(w.CENTER[0] - halfWay + i, w.CENTER[1], fromLocation + distance);
        distance += " -";
        zzz(1000);
    }
    //as 'halfWay' is unprecise we add length to the subtraction instead of just adding halfWay
    w.setWord(w.CENTER[0] - halfWay + length+1, w.CENTER[1], "> " + toLocation);
    w.coutWindow();
}


// VIEW: mainMenu - Presents important menu options for the player, such as:
//                   * New game
//                   * Continue
//                   * Exit
void mainMenuView(){

    resetScreen();
    w.clearWindow();

    w.setLine(4,
   "                   ================================                   \n");
    w.setLine(5,
   "                   |                              |                   \n");
    w.setLine(6,
   "                   |                              |                   \n");
    w.setLine(7,
   "                   *                              *                   \n");


    w.setWord(w.CENTER[0]-5,  8, "[N]EW GAME");
    w.setWord(w.CENTER[0]-5, 10, "[C]ONTINUE");
    w.setWord(w.CENTER[0]-5, 12, "[E]XIT"    );


    w.setLine(14,
   "                  *                                *                  \n");
    w.setLine(15,
   "                  |                                |                  \n");
    w.setLine(16,
   "                  ==================================                  \n");
    w.setLine(17,
   "                  [N]+enter | [C]+enter | [E]+Enter                   \n");
    w.setLine(18,
   "                  ==================================                  \n");

    w.coutWindow();
    cout << "                                ";
    
    cin >> globalKey;
    cin.ignore();    cin.clear();
}


//                                                                           //
// ---------------------------- UTILITY FUNCITONS ---------------------------//
//  Comment:                                                                  
//      Small functions that serve as tools to do specialiced tasks in other 
//      funcitons.


void zzz(int milliseconds)        // cross-platform sleep function
{
    #ifdef WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif // win32
}

void resetScreen(){

    globalKey = ' ';         // Resets the global key, so it won't have side-
                            // effects across views.

    for (int i=0; i < 30; i++) {  // Prints 30 \n - endline characters.
        cout << '\n';             //  effectively wipes the screen clean.
    }
}



//// ------------------------------ MAIN ----------------------------------////


int main(){

    openingView();
    return 0;
}








