#ifndef THREATOBJECT_H_INCLUDED
#define THREATOBJECT_H_INCLUDED

#include "CommonFunction.h"
#include "BaseObject.h"
#include <time.h>
#include <stdlib.h>

#define FRAME_NUM 6
#define THREAT_SPEED 10

class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

    void set_x_val(const int &xVal)
    {
        x_val = xVal;
    }

    void set_y_val(const int &yVal)
    {
        y_val = yVal;
    }

    void set_x_pos(int xPos) { x_pos = xPos;}
    void set_y_pos(int yPos) { y_pos = yPos;}
    int get_x_pos() {return x_pos;}
    int get_y_pos() {return y_pos;}

    virtual bool loadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void set_clip();

    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}

    void ThreatMove(const int index);
private:
    int x_pos;
    int y_pos;
    int x_val;// enemy se tu dong di chuyen ve phia nhan vat de can duong
    int y_val;// enemy se tu dong di chuyen ve phia nhan vat de can duong
    //int come_back_time;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[FRAME_NUM];
    int frame;
    SDL_Rect* currentClip;
};

#endif // THREATOBJECT_H_INCLUDED
