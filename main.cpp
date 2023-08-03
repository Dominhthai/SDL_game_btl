#include<SDL.h>
#include<SDL_image.h>
#include "BaseObject.h"
#include "MainObject.h"
#include "Timer.h"
#include "BulletObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include<stdlib.h>
#include<random>
#include <functional>

using namespace std;

BaseObject g_background;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError();
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            std::cout << "Window could not be created! SDL_Error: %s\n" << SDL_GetError() ;
            success = false;
        }
        else
        {
                //Create/Initialize Renderer
                gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
                if(gScreen == NULL)
                {
                    success = false;
                }
                else
                {
                    SDL_SetRenderDrawColor(gScreen, 0xFF, 0xFF, 0xFF, 0xFF);

            //Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) )
			{
				std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
				success = false;
			}
                }

        }
    }

    return success;
}

//Create all the enemy objects
std::vector <ThreatObject*> ThreatList()
{
    std::vector<ThreatObject*> list_threats;
    ThreatObject* threat_obj = new ThreatObject[10];

    for (int i = 0; i < 10; i++)
    {
        ThreatObject* p_threat = (threat_obj + i);
        if(p_threat != NULL)
        {
            p_threat->loadImg("image/1x/enemy.png", gScreen);
            p_threat->set_clip();
            p_threat->set_x_val(13);

            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}

void CleanUp()
{
    g_background.Free();
    SDL_DestroyRenderer(gScreen);
    gScreen = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{

Timer fps_timer;
int num_die = 0;
//loop flag
bool is_quit = false;

    if (!init())
    {
        cout << "Failed to initialize windows\n";
        return -1;
    }

    // Load background image
    bool ret = g_background.LoadObject("image/background/background.png", gScreen);//840*600
    if (ret == false) return -2;

    //Main character initialization
    MainObject* cat = new MainObject();
    cat->loadImg("image/1x/combo.png", gScreen);
    cat->SetClip();

    std::vector<ThreatObject*> threats_list = ThreatList();// save the enemy list

    //Explosion Object
    ExplosionObject exp;
    bool rec = exp.loadImg("image/1x/explosion.png", gScreen);
    if(rec == false) return -3;
    exp.SetClip();

    while(!is_quit)
    {
        fps_timer.start();

        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                is_quit = true;
                break;
            }

            cat->HandleInputAction(e, gScreen);
            //human_object.HandleInputAction(e);

        }
        SDL_SetRenderDrawColor(gScreen, 255, 255, 255, 255);
        SDL_RenderClear(gScreen);


        //x_change -=2;
        g_background.ApplyObject(gScreen, NULL, true); // Bien bool de check xem doi tuong load co phai laf background hay ko

        cat->HandleBullet(gScreen);// shot the bullet
        cat->Show(gScreen); // show character

        SDL_Rect mRect;// Rect collison of main character
        mRect.x = cat->getRect().x;
        mRect.y = cat->getRect().y;
        mRect.w = cat->get_width_frame()/3 + 10;
        mRect.h = cat->get_width_frame()/3 + 10;

        SDL_Rect eRect;// Rect collison of explosion
        eRect.x = exp.getRect().x;
        eRect.y = exp.getRect().y;
        eRect.w = exp.get_width_frame()/3;
        eRect.h = exp.get_height_frame()/3;

    //Check va cham giua cac doi tuong (bullet and enemy; main and enemy)
        std::vector<BulletObject*> bullet_arr = cat->get_bullet();// Luu cac vien dan

        for(int i = 0; i < threats_list.size(); i++)
        {
            ThreatObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->Show(gScreen);
                p_threat->ThreatMove(i*300);

        SDL_Rect tRect;//Rect collision for threat object
        tRect.x = p_threat->getRect().x;
        tRect.y = p_threat->getRect().y;
        tRect.w = p_threat->get_width_frame()/5;
        tRect.h = p_threat->get_height_frame()/5;

        bool is_col_main = CommonFunc::CheckCollision(mRect, tRect); // Check va cham giua main character va enemy
        if (is_col_main)
        {
            //Check explosion appear when threat expose to bullet and be destroyed!!!
            /*for(int e = 0; e < 9; e++)
            {
                int x_pos = mRect.x - eRect.w + 120;//this explosion image will cover the bullet!!!
                int y_pos = mRect.y - eRect.h + 80;//this explosion image will cover the bullet!!!

                exp.set_frame(e);
                exp.setRect(x_pos, y_pos);
                exp.Show(gScreen);
                //SDL_Delay(1);
            }*/

            num_die++;
            if (num_die < life)
            {
               // SDL_Delay(1000);
                //cat->set_x_val(0);
                //cat->set_y_val(0);
                            //Check explosion appear when threat expose to bullet and be destroyed!!!
            for(int e = 0; e < 9; e++)
            {
                int x_pos = mRect.x - eRect.w + 120;//this explosion image will cover the bullet!!!
                int y_pos = mRect.y - eRect.h + 80;//this explosion image will cover the bullet!!!

                exp.set_frame(e);
                exp.setRect(x_pos, y_pos);
                exp.Show(gScreen);
                //SDL_Delay(1);
            }
                cat->Free();
                SDL_Delay(1000);
               // continue;

                //p_threat->Free();
                //threats_list.erase(threats_list.begin() + i);
                //i--;
            }
                p_threat->Free();
                threats_list.erase(threats_list.begin() + i);
                i--;
        }

        for (int b = 0; b < bullet_arr.size(); b++)
        {
            BulletObject* p_bullet = bullet_arr.at(b);
            if (p_bullet != NULL)
            {

        SDL_Rect bRect;// Rect collision for bullet
        bRect.x = p_bullet->getRect().x;
        bRect.y = p_bullet->getRect().y;
        bRect.w = p_bullet->getRect().w/15;
        bRect.h = p_bullet->getRect().h/15;

        bool is_col_bullet = CommonFunc::CheckCollision(tRect, bRect);//Check va cham giua bullet va enemy

        if (is_col_bullet)
        {
            //Check explosion appear when threat expose to bullet and be destroyed!!!
            for(int i = 0; i < 9; i++)
            {
                int x_pos = bRect.x - eRect.w * 0.3 + 18;//this explosion image will cover the bullet!!!
                int y_pos = bRect.y - eRect.h * 0.5 + 25;//this explosion image will cover the bullet!!!

                exp.set_frame(i);
                exp.setRect(x_pos, y_pos);
                exp.Show(gScreen);
                //SDL_Delay(1);
            }
                cat->RemoveBullet(b);
                p_threat->Free();
                threats_list.erase(threats_list.begin() + i);
                i--;
        }

            }
        }
            }
        }

        SDL_RenderPresent(gScreen);

            int real_fps_timer = fps_timer.get_tick();
            int expected_fps_timer = 1000 / FRAME_PER_SECOND;
        if (real_fps_timer < expected_fps_timer)
        {
            int delay_time = expected_fps_timer - real_fps_timer;

            if (delay_time >= 0)
            {
                SDL_Delay(delay_time);
            }
        }

        //Sau khi xoa het tat ca threat trong threat_lists, can khoi tao lai cac threat do
        if(threats_list.empty())
        {
            threats_list = ThreatList();
        }
        cat->loadImg("image/1x/combo.png", gScreen);
        cat->SetClip();
        //cat->set_revision(1);
    }

    CleanUp();

    return 0;
}
