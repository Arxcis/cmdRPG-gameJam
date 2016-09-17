// File    : main.cpp
// Created : 12.09.2016
//      by : Jonas Solsvik
//
// Authors : Arxcis, Stektpotet, Amici, Marco
// 
// Description : This is a version of the game proposed at the cmdRPG-gamejam,
//                held at baserom on saturday and sunday.
//                
//                This version has gone multi-file


// ------------ STANDARD LIB INCLUDES ------------ //

#define MAIN           // main.cpp

#include <iostream>
#include <fcntl.h>
#include <string>
#include <vector>
#include <cmath>

#ifdef WIN32                    // Used to get sleep function cross platform
#include <windows.h>
#else
#include <unistd.h>
#endif                  // Used to get sleep function cross platform

// ------------ LOCAL LIB INCLUDES ------------ //
#include "global.h"
#include "shape.h"
#include "window.h"
#include "view.h"
#include "input.h"



using namespace std; 

View view;

void testing(){


    view.baseTemplate(0);
    zzz(2000);
    view.baseTemplate(1);
    zzz(2000);
    view.baseTemplate(0);
    zzz(2000);
    view.baseTemplate(1);

}

int main(){

    testing();
    return 0;
}
