#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED

#include<iostream>
#include<windows.h>
#include<string.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 520

//The window we'll be rendering to
static SDL_Window* gWindow = NULL;
//The surface contained by the window
//static SDL_Surface* gScreenSurface = NULL;
static SDL_Renderer* gScreen = NULL;//gScreenSurface
static SDL_Event e;

const int FRAME_PER_SECOND = 20; // fps we expected

namespace CommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}
#endif // COMMONFUNCTION_H_INCLUDED
