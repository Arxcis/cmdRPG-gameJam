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
            //                with a defined position and size
            // Why is this so messy =??=?????
struct Rect {
    
    Vector2 position;                       //position of the rectangle
    const int* x = &position.x;
    const int* y = &position.y;
    Vector2 size;                           //size of rectangle
    const int* width = &size.x;
    const int* height = &size.y;

    Rect(int rectX, int rectY, int rectWidth, int rectHeight){

        position = Vector2(rectX, rectY);
        size = Vector2(rectWidth, rectHeight);
    }

    int xMax() { return *x + *width - 1; }
    int yMax() { return *y + *height - 1; }

    Vector2 center()     { return Vector2(*x + *width / 2, *y + *height / 2); }
    Vector2 upperLeft()  { return Vector2(*x, *y);                            }
    Vector2 upperRight() { return Vector2(*x + *width - 1, *y);               }
    Vector2 lowerLeft()  { return Vector2(*x, *y + *height - 1);              }
    Vector2 lowerRight() { return Vector2(*x + *width - 1, *y + *height - 1); }
};


// struct Window {}
// Description : This struct is used to create the window object. This object
//                is very important to the game. The window object holds
//                information about what is on the screen at any given time.
//                It also holds methods to change what is on the screen.
//
struct Window {

    const int WIDTH  = 90;       // Constants to be used for specifying relative coordinates.
    const int HEIGHT = 30;
    const Vector2 CENTER   = Vector2( WIDTH / 2, HEIGHT / 2 );
    const Vector2 U_LEFT   = Vector2( 0, 0 );
    const Vector2 U_RIGHT  = Vector2( WIDTH, 0 );
    const Vector2 L_LEFT   = Vector2( 0, HEIGHT );
    const Vector2 L_RIGHT  = Vector2( WIDTH, HEIGHT );
    
    const string         ZERO_LINE   = string         (WIDTH , ' '      );
    const vector<string> ZERO_WINDOW = vector<string> (HEIGHT, ZERO_LINE);

    vector<string> windowState = ZERO_WINDOW;  // Initialize state of window object


    //  ------------------------------ Window methods ------------------------- // 
    //  void clearWindow()
    //  void setWindow()
    //  void setline()
    //  void setWord()
    //  void setText()
    //  void coutWindow()
    //  ----------------------------------------------------------------------- // 

        // Description : Overwrites entire window object, with a blank template.
    void clearWindow() {     windowState = ZERO_WINDOW;    }

        // Description : Overwrites entire window object with a custom template.
    void setWindow(vector <string> newState) {     windowState = newState;   }

        // Description : Replaces an entire row of the window object, with a new.
    void setLine(int row, string line) {    windowState[row] = line + "\n";     }

        // Description : Places a string at a specified location within the window.
        //               If a str overflows the window, it gets cut off.
        //
        // @param : int column - a number between 0-69, starting pos. of the word.
        // @param : int row - a number between 0-19, specifies which row to change
        // @param : string str - a word of any lenght to be inserted at position.
        // @param : bool centered - makes the word shift over so, 'column' will be 
        //            in the center of the word
        // @return: void

    void setWord(int column, int row, string str, bool centered = false){
        if (centered)
        {
            column -= str.length() / 2;
        }
        for (int i = column, j= 0; i < (column + str.length()); i++, j++){

            
            if ( i < WIDTH) {          // Makes sure that the end of line is not
                                     //  overwritten.
                windowState[row][i] = str[j];
            }
        }
    }

    void setText(int column, int row, vector<string> stringList){

        string str;
        unsigned long length = stringList.size(); // the return type of  is 'ulong'

        for (int i = row, j = 0; j < length && i < HEIGHT; i++, j++) {
            str = stringList[j];

            for (int k = column, l = 0; k < (column + str.length()); k++, l++){

                windowState[i][k] = str[l];
            };
        };
    }


    // Description : Prints the entire window.
    //
    //
    void coutWindow()  {

        for (int i=0; i < HEIGHT; i++){
            std::cout << windowState[i] << '\n';
        }
    }
}; 


// ------------------------------ GLOBALS -----------------------------------//

char globalKey = ' ';
Window w; 



//// ----------------------- FUNCTION DECLARATIONS ------------------------////


// ----- GUI Layer functions ----- //
void box(Rect box);
void borders();
void loadingBar(Vector2 position, int length, int loadTime = 5000);
void loadingBar(int x, int y, int length, int loadTime = 5000);

// ----- View functions ----- //
void openingView();
void travelView(string fromLocation, string toLocation, int length);
void mainMenuView();

// ------ Utility functions ---- //
void zzz(int milliseconds);                   // Cross platform sleep
void resetScreen();           // cross platform clear-screen.

void testing();




//// ------------------------ FUNCTION DEFINITIONS  ------------------------- ////

// ------------------------------ GUI LAYER FUNCITONS ------------------------------//
//   Comment:
//    The following helperfunctions generate parts of a view.
//     Most GUI layer function:
//       1.  Adds parts to the buffer (string vector) without actually printing it. 
//             (that's the view-functions job).
//       2.  Are used only by the view-functions.
//       3a. Does not use zzz(...) as that can cause pauses in the view-function, causing half-printed views.
//       3b. can use zzz(...) as long as they also handle their own printing.
//
//     To make the game appear consistent across all views we have to     
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
    box(Rect(0, 0, w.WIDTH, w.HEIGHT));//BOX the whole screen
}

// GUILAYER: loading bar - Displays a loading bar with a load time.
//       @param - position - on which coordinates should the starting position be
//       @param - length - how many ticks does the loading bar need to get full
//       @param - loadTime - how long does each tick take
void loadingBar(Vector2 position, int length, int loadTime)
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

void loadingBar(int x, int y, int length, int loadTime)
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
struct View {

    void opening(){

        std::cout << "\nResize screen!\n";
        zzz(3000);
        resetScreen();
        borders();

        vector<string> text = { "The               ",
                                "  Wizard's        ",
                                "  Holiday         ",
                                "    Copyright 2016" };

        w.setText(w.CENTER.x-30, w.CENTER.y-3, text);

        w.coutWindow();
        loadingBar(w.CENTER.x - 30, w.CENTER.y+8, 50, 10000);

        

    }


    // VIEW: travelView - Shows animation of travelling between two cities.
    //       @param - string fromLocation - name of starting location
    //       @param - string toLocation   - name of destination
    //       @param - int    length       - animation time in seconds. 
    void travel(string fromLocation, string toLocation, const int length)
    {
        int halfWay = length / 2; //this is unprecise

        resetScreen();
        w.setWord(w.CENTER.x - halfWay - fromLocation.length(), w.CENTER.y, fromLocation);
        w.coutWindow();
        for (int i = 0; i < length; i++)
        {
            resetScreen();
            w.setWord(w.CENTER.x - halfWay + i, w.CENTER.y, "-");
            w.coutWindow();
            zzz(500);
        }
        //as 'halfWay' is unprecise we add length to the subtraction instead of just adding halfWay
        resetScreen();
        w.setWord(w.CENTER.x - halfWay + length, w.CENTER.y, ">" + toLocation);
        w.coutWindow();
    }

    // VIEW: mainMenu - Presents important menu options for the player, such as:
    //                   * New game
    //                   * Continue
    //                   * Exit
    void mainMenu(){
        
        resetScreen();
        w.clearWindow();

        box(Rect(10, 2, w.WIDTH * (7/10), w.HEIGHT * (7/10))); 

        w.setWord(w.CENTER.x-5,  w.CENTER.y - 2, "[N]EW GAME");
        w.setWord(w.CENTER.x-5,  w.CENTER.y    , "[C]ONTINUE");
        w.setWord(w.CENTER.x-5,  w.CENTER.y + 2, "[E]XIT"    );

        w.setLine(w.CENTER.y + 4, 
    "                            [N]+enter | [C]+enter | [E]+Enter                            \n");
        w.setLine(w.CENTER.y + 5, 
    "                            ==================================                           \n");
        w.coutWindow();
        cout << "                                ";
            cin >> globalKey;
        cin.ignore();    cin.clear();
    }
};

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
    globalKey = ' ';    // Resets the global key, so it won't have side-
                        // effects across views.
#ifdef WIN32
    system("cls");

#else     
    for (int i=0; i < 30; i++) {  // Prints 30 \n - endline characters.
        cout << '\n';             //  effectively wipes the screen clean.
    }
#endif // WIN32
}

//// ------------------------------ MAIN ----------------------------------////



int main(){

    testing();
    return 0;
}


void testing(){

    View view;

    view.opening();
    //view.travel("Bergen", "Oslo", 15);
}







