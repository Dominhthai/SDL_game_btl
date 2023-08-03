#ifndef EXPLOSIONOBJECT_H_INCLUDED
#define EXPLOSIONOBJECT_H_INCLUDED
#include "BaseObject.h"

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void SetClip();
    virtual bool loadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    int get_width_frame(){return width_frame;}
    int get_height_frame(){return height_frame;}
    int set_frame(const int &i) {frame = i;}
private:
    int width_frame;
    int height_frame;

    int x_pos;
    int y_pos;

    SDL_Rect frame_clip[9];
    int frame;
    SDL_Rect* currentClip;
};

#endif // EXPLOSIONOBJECT_H_INCLUDED
