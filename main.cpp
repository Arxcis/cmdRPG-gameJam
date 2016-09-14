// File    : main.cpp
// Created : 12.09.2016
//      by : Jonas Solsvik
//
// Authors : Arxcis, Stektpotet, Amici, Marco
// 
// Description : This is a version of the game proposed at the cmdRPG-gamejam,
//                held at baserom on saturday and sunday.
//                This version tries to keep the entire source-code in a
//                single file. 


// ------------ STANDARD LIB INCLUDES ------------ //

#include <iostream>
#include <fcntl.h>
#include <string>
#include <vector>
#include <cmath>

#ifdef win32                    // Used to get sleep function cross platform
#include <windows.h>
#else
#include <unistd.h>
#endif                  


// ----------------- LOCAL INCLUDES ------------------ // 

#include "view/graphics.h"
#include "view/views.h"

using namespace std;


// ------------------------ GLOBALS ----------------------------//

char globalKey = ' ';
Window w; 



//// ----------------------- FUNCTION DECLARATIONS ------------------------////


void box(Rect box);                 // GUI Layer functions 
void borders();
                                    // Utility functions 
void zzz(int milliseconds);         // Cross platform sleep
void resetScreen();                 // cross platform clear-screen.

void testing();


//// ------------------------ FUNCTION DEFINITIONS  ---------------------- ////

// -------------------------- GUI LAYER FUNCITONS ---------------------------//
//   Comment:
//    The following helperfunctions generate parts of a view.
//     Most GUI layer function:
//       1.  Adds parts to the buffer (string vector) without actually printing it. (that's the view-functions job).
//		 2.  Are used only by the view-functions.
//		 3a. Does not use zzz(...) as that can cause pauses in the view-function, causing half-printed views.
//		 3b. can use zzz(...) as long as they also handle their own printing.
//
//	   To make the game appear consistent across all views we have to     
//     standardize the width and height of each view.
//     The window object should make sure that width and high are consistent
//     across views. 
//
//   ASCII - resolution:  70(0-69 +1 newline character) x 20 lines (0-19).
//

// GUILAYER: borders - generates borders for your window.
//       @param - screenRectangle - a rectangle made from coordinates in the console view (within 70x20)
void box(Rect screenRectangle)
{
	string horizLine = "+";
	for (int i = 1; i < *screenRectangle.width - 1; i++)
	{
		horizLine += "=";
	}
	horizLine += "+";

	w.setWord(*screenRectangle.x, *screenRectangle.y, horizLine);
	for (int i = 1; i < *screenRectangle.height; i++)
	{
		w.setWord(*screenRectangle.x, *screenRectangle.y + i, "[");
		w.setWord(screenRectangle.xMax(), *screenRectangle.y + i, "]");
	}
	w.setWord(*screenRectangle.x, screenRectangle.yMax(), horizLine);
}


// GUILAYER: borders - generates borders for your window.
void borders()
{
	box(Rect(0, 0, 70, 20));//BOX the whole screen
}

// GUILAYER: loading bar - Displays a loading bar with a load time.
//       @param - position - on which coordinates should the starting position be
//		 @param - length - how many ticks does the loading bar need to get full
//		 @param - loadTime - how long does each tick take
void loadingBar(Vector2 position, int length, int loadTime = 5000)
{
	
	w.setWord(position.x, position.y, "LOADING: [");
	w.setWord(position.x + length + 10, position.y, "]");

	for (int i = 0; i < length; i++)
	{
		resetScreen();
		w.setWord(position.x + i+10, position.y, "=");
		w.coutWindow();
		zzz(50);
	}
	
}
void loadingBar(int x, int y, int length, int loadTime = 5000)
{
	loadingBar(Vector2(x, y), length, loadTime);
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

#ifdef WIN32
	system("cls");
#else
    globalKey = ' ';         // Resets the global key, so it won't have side-
                            // effects across views.

    for (int i=0; i < 30; i++) {  // Prints 30 \n - endline characters.
        cout << '\n';             //  effectively wipes the screen clean.
    }
#endif // WIN32
}

//// ------------------------------ MAIN ----------------------------------////


int main(){
	//Add design layers - These you could potentially use inside the view-functions aswell
	borders();

	openingView();
	
    testing(); 

    return 0;
}

void testing(){
	w.clearWindow();//starting fresh here in testing

    // This is meant to be a function with no other purpose than to pump
    //  out dirty function calls. 

    //Add design layers - These you could potentially use inside the view-functions aswell
    borders();
    box(Rect(10, 6, 40, 7));

    zzz(1000);

    borders();

    resetScreen();    // Bumps old frame out of sight
            

    vector<string> text = { 
                "My name is Jonas,", 
                " and I'm carrying the wheel.",
                "  Thanks for all you've shown us,",
                "   This is how it feels... ! :)"};
    w.setText(10, 3, text);                      
    w.coutWindow();


}







