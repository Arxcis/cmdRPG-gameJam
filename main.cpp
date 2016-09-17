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

            // Local includes
#include "globals.h"

#include "graphics.h"
#include "window.h"
#include "view.h"

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
