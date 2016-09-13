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


#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <cmath>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif                  // Used to get sleep function cross platform

using namespace std;


//// ----------------------------- STRUCTS ------------------------------////

// struct Vector2 {}
// Description :  This struct is used to create 2D points
//
struct Vector2
{
	int x = 0, y = 0;
	Vector2(int xValue = 0, int yValue = 0)
	{
		x = xValue;
		y = yValue;
	}
};

// struct Rect {}
// Description :  This struct is used to create rectangles
//				  with a defined position and size
struct Rect
{
	Vector2 position;	//position of the rectangle
	const int* x = &position.x;
	const int* y = &position.y;
	Vector2 size;		//size of rectangle
	const int* width = &size.x;
	const int* height = &size.y;

	Rect(int rectX, int rectY, int rectWidth, int rectHeight)
	{
		position = Vector2(rectX, rectY);
		size = Vector2(rectWidth, rectHeight);
	}

	int xMax() { return *x + *width - 1; }
	int yMax() { return *y + *height - 1; }

	Vector2 center() { return Vector2(*x + *width / 2, *y + *height / 2); }
	Vector2 upperLeft() { return Vector2(*x, *y); }
	Vector2 upperRight() { return Vector2(*x + *width - 1, *y); }
	Vector2 lowerLeft() { return Vector2(*x, *y + *height - 1); }
	Vector2 lowerRight() { return Vector2(*x + *width - 1, *y + *height - 1); }

};


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
	const Vector2 CENTER =		Vector2( WIDTH / 2,HEIGHT / 2 );
    const Vector2 UPPER_LEFT =	Vector2( 0, 0 );
    const Vector2 UPPER_RIGHT =	Vector2( WIDTH, 0 );
    const Vector2 LOWER_LEFT =	Vector2( 0, HEIGHT );
    const Vector2 LOWER_RIGHT = Vector2( WIDTH, HEIGHT );


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

        windowState[row] = line + "\n";
    }
	void setWindow(string lines[20]) {
		
		for (int row = 0; row < 20; row++)
		{
			windowState[row] = lines[row] + "\n";
		}
		
	}

    // Description : Places a word at a specified location within the window.
    //               If a word overflows the window, it gets cut off.
    //
	// @param : int column - a number between 0-69, starting pos. of the word.
    // @param : int row - a number between 0-19, specifies which row to change
    // @param : string word - a word of any lenght to be inserted at position.
    // @return: void
    //
    //
    void setWord(int column, int row, string word, bool centered = false){
		if (centered)
		{
			column -= word.length() / 2;
		}
        for (int i = column, j= 0; i < (column + word.length()); i++, j++){

            
            if ( i < 70) {          // Makes sure that the end of line is not
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
			std::cout << windowState[i];
        }
    }
}; 



// ------------------------------ GLOBALS -----------------------------------//

char globalKey = ' ';
Window w; 





//// ----------------------- FUNCTION DECLARATIONS ------------------------////

// ----- GUI Layer functions ----- //
void box(Rect box, bool clearView);
void borders(bool clearView);

// ----- View functions ----- //
void openingView();
void travelView(string fromLocation, string toLocation, int length);
void mainMenuView();

// ------ Utility functions ---- //
void zzz(int milliseconds);                   // Cross platform sleep
void resetScreen();           // cross platform clear-screen.








//// ------------------------ FUNCTION DEFINITIONS  ---------------------- ////


// ------------------------------ GUI LAYER FUNCITONS ------------------------------//
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
		zzz(500);
	}
	
}
void loadingBar(int x, int y, int length, int loadTime = 5000)
{
	loadingBar(Vector2(x, y), length, loadTime);
}

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
//   ASCII - resolution:  70(0-69 +1 newline character) x 20 lines (0-19).
//
 

// VIEW: openingView - The first view that meets the player after loading 
//                      the game.
//
void openingView(){

	Rect r = Rect(6, 4, 48, 11);

	box(r);
	resetScreen();

	w.setWord(12, 7, "The");
	w.setWord(14, 8, "Wizard's");
	w.setWord(16, 9, "Holiday");
	w.setWord(r.center().x, 14, "Copyright 2016", true);
	w.coutWindow();
	loadingBar(16, 10, 20, 5000);
	zzz(1000);
    mainMenuView();
}


// VIEW: travelView - Shows animation of travelling between two cities.
//       @param - string fromLocation - name of starting location
//       @param - string toLocation   - name of destination
//       @param - int    length       - animation time in seconds. 
void travelView(string fromLocation, string toLocation, int length)
{
    resetScreen();
    int halfWay = length / 2; //this is unprecise
    w.setWord(w.CENTER.x - fromLocation.length() - halfWay, w.CENTER.y, fromLocation);
	w.coutWindow();
    for (int i = 0; i < length; i++)
    {
        w.setWord(w.CENTER.x - halfWay + i, w.CENTER.y, "-");
		resetScreen();
		w.coutWindow();
        zzz(1000);
    }
    //as 'halfWay' is unprecise we add length to the subtraction instead of just adding halfWay
    w.setWord(w.CENTER.x - halfWay + length, w.CENTER.y, ">" + toLocation);
	resetScreen();
    w.coutWindow();
}

// VIEW: mainMenu - Presents important menu options for the player, such as:
//                   * New game
//                   * Continue
//                   * Exit
void mainMenuView(){

    resetScreen();
    w.clearWindow();

	box(Rect(18, 4, 34, 12)); //testing box to compare to manually made boxes

   // w.setLine(4,
   //"                   ================================                   \n");
   // w.setLine(5,
   //"                   |                              |                   \n");
   // w.setLine(6,
   //"                   |                              |                   \n");
   // w.setLine(7,
   //"                   *                              *                   \n");


    w.setWord(w.CENTER.x-5,  8, "[N]EW GAME");
    w.setWord(w.CENTER.x-5, 10, "[C]ONTINUE");
    w.setWord(w.CENTER.x-5, 12, "[E]XIT"    ); //with rects and boxes, the center could easily be relative to the rect as well


   // w.setLine(14,
   //"                  *                                *                  \n");
   // w.setLine(15,
   //"                  |                                |                  \n");
   // w.setLine(16,
   //"                  ==================================                  \n");
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
	

    return 0;
}








