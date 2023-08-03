#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
    width_frame = 0;
    height_frame = 0;
    x_val = 0;
    y_val = 0;
    x_pos = 0;
    y_pos = 0;
    frame = 0;
    rect.x = x_pos + SCREEN_WIDTH;
    rect.y = y_pos + 410;/// gs la chim thi cao hon nhan vat chinh (cat)
}

ThreatObject::~ThreatObject()
{

}

bool ThreatObject::loadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadObject(path, screen);
    if (ret == true)
    {
        width_frame = rect.w/3; // Bo di ti phan thua do load anh :>
        height_frame = rect.h/2;
    }
    return ret;
}

void ThreatObject::set_clip()
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

        //hang duoi
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
    }
}

void ThreatObject::Show(SDL_Renderer* des)
{
  //  rect.x = x_pos + SCREEN_WIDTH - 200;
    //rect.y = y_pos;// gs la chim thi cao hon nhan vat chinh (cat)

    //SDL_Rect* currentClip = &frame_clip[frame];
    currentClip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, width_frame/5, height_frame/5};// Reshape threat character(the bird)

    SDL_RenderCopy(des, p_object, currentClip, &renderQuad);

    ++frame;
    if(frame > 5) frame = 0;
}

void ThreatObject::ThreatMove(const int id)
{
    rect.x -= x_val; // threat di chuyen ve phia nhan vat de can duong
    if (rect.x < 0)
    {
        rect.x = SCREEN_WIDTH + id;

        //srand(time(NULL));
        int rand_y = rand()%111 + 300;// Threat appears randomly on screen from 300 to 410 y pos
        rect.y = rand_y;
    }
    //Show(screen);
}
