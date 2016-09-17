
#ifndef GRAPHICS_H
#define GRAPHICS_H

using namespace std; 

//// ----------------------------- GRAPHICS ------------------------------////

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

#endif
