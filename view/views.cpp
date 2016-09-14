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
 

#include "views.h"

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

