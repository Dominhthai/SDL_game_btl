#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
    width_frame = 0;
    height_frame = 0;
    x_pos = 0;
    y_pos = 0;
    frame = 0;
}

ExplosionObject::~ExplosionObject()
{
    ;
}

bool ExplosionObject::loadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadObject(path, screen);
    if (ret == true)
    {
        width_frame = (rect.w)/3; // hoi bi thua hinh xiu nen tru them 5 kkk :3
        height_frame = (rect.h)/3;
    }
    return ret;
}

void ExplosionObject::SetClip()
{
    if (width_frame > 0 && height_frame > 0)
    {
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame;
        frame_clip[0].h = height_frame;

        frame_clip[1].x = width_frame;
        frame_clip[1].y = 0;
        frame_clip[1].w = width_frame;
        frame_clip[1].h = height_frame;

        frame_clip[2].x = 2*width_frame;
        frame_clip[2].y = 0;
        frame_clip[2].w = width_frame;
        frame_clip[2].h = height_frame;

        //hang t2
        frame_clip[3].x = 0;
        frame_clip[3].y = height_frame;
        frame_clip[3].w = width_frame;
        frame_clip[3].h = height_frame;

        frame_clip[4].x = width_frame;
        frame_clip[4].y = height_frame;
        frame_clip[4].w = width_frame;
        frame_clip[4].h = height_frame;

        frame_clip[5].x = 2*width_frame;
        frame_clip[5].y = height_frame;
        frame_clip[5].w = width_frame;
        frame_clip[5].h = height_frame;

        //hang cuoi
        frame_clip[6].x = 0;
        frame_clip[6].y = 2*height_frame;
        frame_clip[6].w = width_frame;
        frame_clip[6].h = height_frame;

        frame_clip[7].x = width_frame;
        frame_clip[7].y = 2*height_frame;
        frame_clip[7].w = width_frame;
        frame_clip[7].h = height_frame;

        frame_clip[8].x = 2*width_frame;
        frame_clip[8].y = 2*height_frame;
        frame_clip[8].w = width_frame;
        frame_clip[8].h = height_frame;
    }
}

void ExplosionObject::Show(SDL_Renderer* des)
{
    //rect.x = x_pos;
    //rect.y = y_pos;

    //SDL_Rect* currentClip = &frame_clip[frame];
    currentClip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, width_frame/3, height_frame/3};// Reshape main character(the blue cat)

    SDL_RenderCopy(des, p_object, currentClip, &renderQuad);

    //++frame;
    //if(frame > 8) frame = 0;
}
