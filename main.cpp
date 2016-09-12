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
#include <string>
#include <vector>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif                  // Used to get sleep function cross platform

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


    void setWindow(string lines[20]) {
        
        for (int row = 0; row < 20; row++)
        {
            windowState[row] = lines[row] + "\n";
        }
        
    }

    void howAboutWritingSetWindowLikeThis(vector<string> stringvec20Lines){

        windowState = stringvec20Lines;

    }

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


    // Description : Places a string at a specified location within the window.
    //               If a str overflows the window, it gets cut off.
    //
    // @param : int row - a number between 0-19, specifies which row to change
    // @param : int column - a number between 0-69, starting pos. of the word.
    // @param : string str - a string of any lenght to be inserted at position.
    // @return: void
    //
    //
    void setString(int column, int row, string str){

        for (int i = column, j= 0; i < (column + str.length()); i++, j++){

            if ( i <= 69) {          // Makes sure that the end of line is not
                                     //  overwritten.
                windowState[row][i] = str[j];
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


struct Vector2 {
    
    int x = 0, y = 0;
};


struct Rect {

	Vector2 position;	//position of the rectangle
	const int* x = &position.x;
	const int* y = &position.y;
	Vector2 size;		//size of rectangle
	const int* width = &size.x;
	const int* height = &size.y;
	int xMax()
	{
		return *x + *width - 1;
	}
	int yMax()
	{
		return *y + *height - 1;
	}
	Rect(int rectX, int rectY, int rectWidth, int rectHeight)
	{
		position.x = rectX;
		position.y = rectY;
		size.x = rectWidth;
		size.y = rectHeight;
	}
};



// ------------------------------ GLOBALS -----------------------------------//

char globalKey = ' ';
Window w; 





//// ----------------------- FUNCTION DECLARATIONS ------------------------////

// ----- Design functions ------- // 
void borders(bool resetView = false);
void box(Rect screenRectangle, bool resetView = false);

// ----- View functions ----- //
void openingView();
void travelView(string fromLocation, string toLocation, int length);
void mainMenuView();

// ------ Utility functions ---- //
void zzz(int milliseconds);                   // Cross platform sleep
void resetScreen();           // Prints 30 \n-characters.








//// ------------------------ FUNCTION DEFINITIONS  ---------------------- ////


// --------------------------- DESIGN VIEW FUNCITONS------------------------//
//   Comment:
//    The following helperfunctions generate parts of a view.
//     Each design view function:
//       1.	 Defaults to not reseting the view, as they're suppose to work in 
//            layers.
//       2.  Prints out part of a view e.g. a box around some text from a 
//            view-function.
//
//    To make the game appear consistent across all views we have to     
//     standardize the width and height of each view.
//     The window object should make sure that width and high are consistent
//     across views. 
//
//   ASCII - resolution:  70(0-69 +1 newline character) x 20 lines (0-19).
//

// DESIGN: borders - generates borders for your window.
//       @param - resetView - force the view to clear before making borders
void box(Rect screenRectangle, bool resetView)
{
	if (resetView)
	{
		resetScreen();
	}
	string horizLine = "+";
	for (int i = 1; i < *screenRectangle.width - 1; i++)
	{
		horizLine += "-";
	}
	horizLine += "+";

	w.setString(*screenRectangle.x, *screenRectangle.y, horizLine);
	for (int i = 1; i < *screenRectangle.height; i++)
	{
		w.setString(*screenRectangle.x, *screenRectangle.y + i, "|");
		w.setString(screenRectangle.xMax(), *screenRectangle.y + i, "|");
	}
	w.setString(*screenRectangle.x, screenRectangle.yMax(), horizLine);
	w.coutWindow();
}


// DESIGN: borders - generates borders for your window.
//       @param - resetView - force the view to clear before making borders
void borders(bool resetView)
{
	box(Rect(0, 0, 70, 20));//BOX the whole screen
	//if (resetView)
	//{
	//	resetScreen();
	//}
	//w.setLine(0, "+--------------------------------------------------------------------+");
	//for (int i = 1; i < 19; i++)
	//{
	//	w.setString(0, i, "|");
	//	w.setString(69, i, "|");
	//}
	//w.setLine(19, "+--------------------------------------------------------------------+");
	//w.coutWindow();
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

    int count = 1;

    while(count < 6){

        resetScreen();

        w.setString(12, 7, "The");
        w.setString(14, 8, "Wizard's");
        w.setString(16, 9, "Holiday");

        if(count % 2 == 0){
            w.setString(16, 10, "-----------            ");
        } else {
            w.setString(16, 10, "            -----------");
        }

        w.setString(17, 11, "Copyright 2016");

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
    int halfWay = length / 2; //this is unprecise
    w.setString(w.CENTER[0] - fromLocation.length() - halfWay, w.CENTER[1], fromLocation);
	w.coutWindow();
    for (int i = 0; i < length; i++)
    {
        w.setString(w.CENTER[0] - halfWay + i, w.CENTER[1], "-");
		resetScreen();
		w.coutWindow();
        zzz(1000);
    }
    //as 'halfWay' is unprecise we add length to the subtraction instead of just adding halfWay
    w.setString(w.CENTER[0] - halfWay + length, w.CENTER[1], ">" + toLocation);
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

    w.setLine(4,
   "                   ================================                   \n");
    w.setLine(5,
   "                   |                              |                   \n");
    w.setLine(6,
   "                   |                              |                   \n");
    w.setLine(7,
   "                   *                              *                   \n");


    w.setString(w.CENTER[0]-5,  8, "[N]EW GAME");
    w.setString(w.CENTER[0]-5, 10, "[C]ONTINUE");
    w.setString(w.CENTER[0]-5, 12, "[E]XIT"    );


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
	//openingView();

	//Add design layers - These you could potentially use inside the view-functions aswell
	borders();
	box(Rect(10, 6, 40, 7));

    return 0;
}








