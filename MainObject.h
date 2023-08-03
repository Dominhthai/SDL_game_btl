#ifndef MAINOBJECT_H_INCLUDED
#define MAINOBJECT_H_INCLUDED

#include "BaseObject.h"
#include "BulletObject.h"
#define life 10

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    virtual bool loadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void SetClip();

    //Function specified for shooting bullet
    void set_bullet(std::vector <BulletObject*> bullets)
    {
        p_bullet = bullets;
    }

    std::vector<BulletObject*> get_bullet() const
    {
        return p_bullet;
    }

    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int &index);

    int get_width_frame(){return width_frame;}
    int get_height_frame() {return height_frame;}

    void set_x_val(int xVal) {x_val = xVal;}
    void set_y_val(int yVal) {y_val = yVal;}

    int get_stop() {return is_stop;}

    void set_revision(const int &is_revive){revive = is_revive;}

private:

    std::vector<BulletObject*> p_bullet; //Luu tru cac vien dan(bullet)

    int x_val;// width
    int y_val;//height

    int x_pos;
    int y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[6];
    int frame;
    SDL_Rect* currentClip;

    //check whether main character va cham voi enemy da het mang song hay chua
    int is_stop = 0;
    int gravity = 0;
    int revive = 0;
};

#endif // MAINOBJECT_H_INCLUDED
