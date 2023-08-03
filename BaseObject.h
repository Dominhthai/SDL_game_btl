#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "CommonFunction.h"

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();

    bool LoadObject(std::string file_name, SDL_Renderer* screen);
    void ApplyObject(SDL_Renderer* des, const SDL_Rect* clip = NULL, bool check_background = true);// Render
    void Free();

    void setRect(const int &x, const int &y)
    {
        rect.x = x;
        rect.y = y;
        //rect.w = w;
        //rect.h = h;
    }

    SDL_Rect getRect()
    {
        return rect;
    }

    SDL_Texture* getObject()
    {
        return p_object;
    }

protected:
   //SDL_Surface* p_object;// thuoc tinh khoi tao doi tuong
   SDL_Texture* p_object;
   SDL_Rect rect; // thuoc tinh ve kich thuoc, vi tri doi tuong
   bool run_screen = true; // check screen chay theo man hinh

};
#endif // BASEOBJECT_H_INCLUDED
