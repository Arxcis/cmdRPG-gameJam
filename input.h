#ifndef INPUT_H
#define INPUT_H



#include <stdio.h>
#include "global.h"


void pollEvents(){

    while( SDL_PollEvent( &e) != 0) {   // While keyevent queue has contents

        if (e.type == SDL_QUIT) {        // Rød knapp oppe i venstre hjørne(mac), 
                                         //  høyre hjørnet windows
            quit = true;
        }
                                // User presses a key 
        if( e.type == SDL_KEYDOWN){

            switch( e.key.keysym.sym ) {

                case SDLK_UP:

                    printf("Up-key\n");
                    break;

                case SDLK_DOWN:

                    printf("Down-key\n");
                    break;

                case SDLK_LEFT:
            
                    printf("Left-key\n");
                    break;

                case SDLK_RIGHT:

                    printf("Right-key\n");
                    break;

                default:
                    printf("Default-key\n");
                    break;
            }
        }
    }
}


bool init(){

    bool success = true;

    if  ( SDL_Init(0) < 0 )  {        //Initialize SDL library
        std::cout << "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
        success = false;
    }

    else {

        if(SDL_InitSubSystem( SDL_INIT_EVENTS ) < 0){

            std::cout << "ERROR on subsystem! SDL_Error: %s\n", SDL_GetError();
            success = false;
        }

    }

    return success;    // bool
}


#endif