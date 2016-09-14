
// graphics.h is supposed to take care anything that has to be drawn to 
//  the screen. 


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
struct Rect
{
    Vector2 position;   //position of the rectangle
    const int* x = &position.x;
    const int* y = &position.y;
    Vector2 size;       //size of rectangle
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
    const Vector2 CENTER =      Vector2( WIDTH / 2,HEIGHT / 2 );
    const Vector2 UPPER_LEFT =  Vector2( 0, 0 );
    const Vector2 UPPER_RIGHT = Vector2( WIDTH, 0 );
    const Vector2 LOWER_LEFT =  Vector2( 0, HEIGHT );
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
    // @param : int column - a number between 0-69, starting pos. of the word.
    // @param : int row - a number between 0-19, specifies which row to change
    // @param : string str - a word of any lenght to be inserted at position.
    // @param : bool centered - makes the word shift over so 'column' will be in the center of the word
    // @return: void
    //
    //
    void setWord(int column, int row, string str, bool centered = false){
        if (centered)
        {
            column -= str.length() / 2;
        }
        for (int i = column, j= 0; i < (column + str.length()); i++, j++){

            
            if ( i < 70) {          // Makes sure that the end of line is not
                                     //  overwritten.
                windowState[row][i] = str[j];
            }
        }
    }

    void setText(int column, int row, vector<string> stringList){

        string str;
        unsigned long length = stringList.size(); // the return type is 'ulong'

        for (int i = row, j = 0; j < length && i <= 19; i++, j++) {
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

        for (int i=0; i < 20; i++){
            std::cout << windowState[i];
        }
    }
}; 

