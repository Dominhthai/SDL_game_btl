#include "MainObject.h"
#include "BulletObject.h"

MainObject::MainObject()
{
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    width_frame = 0;
    height_frame = 0;
    x_val = 0;
    y_val = 0;
}

MainObject::~MainObject()
{
    ;
}

bool MainObject::loadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadObject(path, screen);
    if (ret == true)
    {
        width_frame = (rect.w)/3 - 5; // hoi bi thua hinh xiu nen tru them 5 kkk :3
        height_frame = (rect.h)/2 ;
    }
    return ret;
}

void MainObject::SetClip()
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

void MainObject::Show(SDL_Renderer* des)
{
    rect.x = x_pos + 50;
    rect.y = y_pos + 405;

    //SDL_Rect* currentClip = &frame_clip[frame];
    currentClip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect.x, rect.y, width_frame/3 + 10, height_frame/3 + 10};// Reshape main character(the blue cat)

    SDL_RenderCopy(des, p_object, currentClip, &renderQuad);

    ++frame;
    if(frame > 5) frame = 0;
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        if (events.key.keysym.sym == SDLK_UP)
        {
            if (rect.y > 340 && gravity == 0) // gioi han chi nhay 1 lan, (neu bam giu) se khong de no nhay ra khoi man hinh
            {
            y_pos -= 70;
            frame = 5;
            gravity = 1;
            //SDL_Delay(500);
            } else
            {
                y_pos = 0;
                //revive = 0;
                //SDL_Delay(100);
                //frame = 0;
            }
        }
        else if (events.key.keysym.sym == SDLK_SPACE)
        {
            //Ban dan- Shot the bullet
            BulletObject* bullet = new BulletObject();
            bullet->LoadObject("image/2x/bullet.png", screen);
            bullet->setRect(this->rect.x + width_frame - 200, this->rect.y + height_frame/10 );
            bullet->set_x_val(20);
            bullet->set_is_move(true);
            p_bullet.push_back(bullet);
           // CreateBullet();
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
        case SDLK_UP:
            y_pos = 0;
            frame = 0;
            gravity = 0;
            break;
        }
    }
    else if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        if (events.button.button == SDL_BUTTON_RIGHT)
        {
            //Ban dan- Shot the bullet
            BulletObject* bullet = new BulletObject();
            int ret = bullet->LoadObject("image/2x/bullet.png", screen);
            if (ret == false) std::cout << "NO\n";
            bullet->setRect( this->rect.x + width_frame - 200, this->rect.y + height_frame/10 );
            bullet->set_x_val(20);
            bullet->set_is_move(true);

            p_bullet.push_back(bullet);// Them cac vien dan vao vector luu tru cac vien dan
            //CreateBullet();
        }
    }
    else if (events.type == SDL_MOUSEBUTTONUP)
    {

    }
    else
    {
        ;
    }
}

void MainObject::HandleBullet(SDL_Renderer* des)
{
    //std::cout << p_bullet.size() << "\n";
    for (int i = 0; i < p_bullet.size(); i++)
    {
        BulletObject* shot_bullet = p_bullet.at(i);
        if (shot_bullet != NULL)
        {
            if (shot_bullet->get_is_move() == true)
            {
                shot_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);// kt xem dan co tran ra khoi man hinh k
                shot_bullet->ApplyObject(des, NULL, false);

            }
            else
            {
                p_bullet.erase(p_bullet.begin() + i);
                if (shot_bullet != NULL)
                {
                    delete shot_bullet;
                    shot_bullet = NULL;
                }
            }
        }
    }
}

void MainObject::RemoveBullet(const int &idx)
{
    int len = p_bullet.size();
    if (len > 0 && idx < len)
    {
        //BulletObject* removed_bullet = p_bullet.at(idx);
        p_bullet.erase(p_bullet.begin() + idx);
    }
}


