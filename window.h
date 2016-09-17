#ifndef WINDOW_H      // if not defined
#define WINDOW_H

#include <string>
#include <vector>
#include "shape.h"

using namespace std; 

// ------------------------- STRUCT WINDOW ---------------------------------
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

#endif
