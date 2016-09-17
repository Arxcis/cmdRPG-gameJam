#ifndef VIEW_H
#define VIEW_H

#include <string>
#include <vector>
#include "window.h"
#include "global.h"

using namespace std; 

Window    w;

// ----- GUI Layer functions ----- //
void box(Rect box);
void borders();
void loadingBar(Vector2 position, int length, int loadTime = 5000);
void loadingBar(int x, int y, int length, int loadTime = 5000);

// ------ Utility functions ---- //
void zzz(int milliseconds);                   // Cross platform sleep
void clearScreen();           // cross platform clear-screen.


// ---------------------------- STRUCT VIEW -----------------------------//

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

    //  ------------------------------ View methods ------------------------- //
    //  void baseTemplate(int switcher) 
    //  void void opening()
    //  void mainMenu()
    //  void epicTravel()
    //  void travel(string fromLocation, string toLocation, const int length)
    //  ----------------------------------------------------------------------- // 


    /// VIEW: Base template - skeleton view for most scenarios
    void baseTemplate(int switcher){ 

        clearScreen();
        w.clearWindow();
                // Switch between the two ways of bordering
        switch(switcher){
            case 0: 
                box(Rect(0 , 0,                (w.WIDTH * 1/3), w.CENTER.y));
                box(Rect(0 , (w.HEIGHT * 2/4), (w.WIDTH * 1/3), w.CENTER.y));
                w.setWord(w.CENTER.x, w.CENTER.y, "Base template 0");
                break;
            case 1:
                box(Rect(w.WIDTH * 0 , 0, (w.WIDTH * 1/3), w.HEIGHT));
                w.setWord(w.CENTER.x, w.CENTER.y, "Base template 1");
                break;
        }
        box(Rect(w.WIDTH * 1/3 , 0, (w.WIDTH * 2/3), w.HEIGHT  ));

        w.coutWindow();
    }


    void opening(){

        clearScreen();
        borders();

 
        vector<string> text = { "The               ",
                                "  Wizard's        ",
                                "  Holiday         ",
                                "    Copyright 2016" };

        w.setText(w.CENTER.x-30, w.CENTER.y-3, text);

        w.coutWindow();
        loadingBar(w.CENTER.x - 30, w.CENTER.y+8, 50, 500); 

        mainMenu();
    }
    
    // VIEW: mainMenu - Presents important menu options for the player, such as:
    //                   * New game
    //                   * Continue
    //                   * Exit
    void mainMenu(){
        
        clearScreen();
        w.clearWindow();


        w.setWord(w.CENTER.x-5,  w.CENTER.y - 2, "[N]EW GAME");
        w.setWord(w.CENTER.x-5,  w.CENTER.y    , "[C]ONTINUE");
        w.setWord(w.CENTER.x-5,  w.CENTER.y + 2, "[E]XIT"    );

        w.setLine(w.CENTER.y + 4, 
    "                           [N]+enter | [C]+enter | [E]+Enter                             ");
        w.setLine(w.CENTER.y + 5, 
    "                           ==================================                            ");
        borders();
        w.coutWindow();
        cout << string (w.CENTER.x, ' ');   cin >> globalKey;
        
        switch(toupper(globalKey)){

            case 'N':
                epicTravel();
                break;
            case 'C':
                break;
            case 'E':
                break;
                cout << "  Option not available yet";


        }
        std::cin.ignore();    std::cin.clear();
    }

    
    // VIEW: epicTravel - Shows animation of travelling between York and Bergen.
    //                      It is the first thing that happens in the game.
    void epicTravel(){

        clearScreen();
        w.clearWindow();

        vector<string> text = { "Our hero starts on his dangerous journey across the seas.",
                                " Huge waves nearly destroys his boat, but luckily he makes it",
                                "  all the way across the northern sea.",
                                "    He arrives in Bergen at 15:00 o'clock. " };
        w.setText(w.CENTER.x-30, w.CENTER.y-5, text);

        w.coutWindow();
        travel("Jorvik", "Bergen", 20);

        zzz(2000);
        // bergen();
    }

    // VIEW: travelView - Shows animation of travelling between two cities.
    //       @param - string fromLocation - name of starting location
    //       @param - string toLocation   - name of destination
    //       @param - int    length       - animation time in seconds. 
    void travel(string fromLocation, string toLocation, const int length) 
    {
        int halfWay = length / 2; //this is unprecise

        clearScreen();
        w.setWord(w.CENTER.x - halfWay - fromLocation.length(), w.CENTER.y, fromLocation);
        w.coutWindow();

        for (int i = 0; i < length; i++)
        {
            clearScreen();
            w.setWord(w.CENTER.x - halfWay + i, w.CENTER.y, "-");
            w.coutWindow();
            zzz(500);
        }
        //as 'halfWay' is unprecise we add length to the subtraction instead of just adding halfWay
        clearScreen();
        w.setWord(w.CENTER.x - halfWay + length, w.CENTER.y, ">" + toLocation);
        w.coutWindow();

    }
};





// ------------------------------ GUI LAYER FUNCITONS ------------------------------//
//   Comment:
//    The following helperfunctions generate parts of a view.
//     Most GUI layer function:
//       1.  Adds parts to the buffer (string vector) without actually printing it. 
//             (that's the view-functions job).
//       2.  Are used only by the view-functions.
//       3a. Does not use zzz(...) as that can cause pauses in the view-function, causing 
//              half-printed views.
//       3b. can use zzz(...) as long as they also handle their own printing.


//   ASCII - resolution:  70(0-69 +1 newline character) x 20 lines (0-19).
//

// GUILAYER: borders - generates borders for your window.
//       @param - screenRectangle - a rectangle made from coordinates in the console 
//                 view (within 70x20)

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
        clearScreen();
        w.setWord(position.x + i+10, position.y, "=");
        w.coutWindow();
        Window();
        zzz(50);
    }
    
}

void loadingBar(int x, int y, int length, int loadTime)
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

void clearScreen(){
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


#endif