#include "BaseObject.h"

BaseObject::BaseObject()
{
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    p_object = NULL;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadObject(std::string file_path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;

    SDL_Surface* load_image = NULL;

    load_image = IMG_Load(file_path.c_str());

    if (load_image == NULL)std::cout << "Unable to load image ! SDL_image Error:\n" << file_path.c_str() << IMG_GetError();
    else
    {

   SDL_SetColorKey(load_image, SDL_TRUE, SDL_MapRGB(load_image->format, 128, 0, 128));// purple

   new_texture = SDL_CreateTextureFromSurface(screen, load_image);
   if (new_texture != NULL)
   {
       rect.w = load_image->w;
       rect.h = load_image->h;
   }

   SDL_FreeSurface(load_image);

    }
    p_object = new_texture;
    return p_object != NULL;
}

void BaseObject::ApplyObject(SDL_Renderer* des, const SDL_Rect* clip, bool back_check)//Renderer background game
{

    if (run_screen == true && back_check == true)
    {
        rect.x -= 3; // cho background chay/ troi theo cat
        if (rect.x <= -(3200 - SCREEN_WIDTH)) // 3200 la do rong cua anh background(background width)
        {
            run_screen = false;
        }
        else
        {
        //stretch the image to fit the size of the windows screen
    SDL_Rect stretchRect = {rect.x, rect.y, rect.w, rect.h};

    SDL_RenderCopy(des, p_object, clip, &stretchRect);//The texture(p_object) will be stretched to fill the given rectangle(stretchRect)
      //SDL_RenderCopy(des, p_object, clip, NULL);
        }
    }
    else if (run_screen == true && back_check == false)
    {
        //back_check is false
        //IF IT IS NOT THE BACKGROUND, RUN THIS!!!
        //stretch the image to fit the size of the windows screen, look like it's bullet load :>
    SDL_Rect stretchRect = {rect.x, rect.y, rect.w/15, rect.h/15};

    SDL_RenderCopy(des, p_object, clip, &stretchRect);//The texture(p_object) will be stretched to fill the given rectangle(stretchRect)
      //SDL_RenderCopy(des, p_object, clip, NULL);
    }

    else
    {
    // Truong hop run_screen is false, load man hunh giu nguyen, ko cho chay nua
    //stretch the image to fit the size of the windows screen
    SDL_Rect stretchRect = {rect.x, rect.y, rect.w, rect.h};

    SDL_RenderCopy(des, p_object, clip, &stretchRect);//The texture(p_object) will be stretched to fill the given rectangle(stretchRect)

    }
}

void BaseObject::Free()
{
    if (p_object != NULL)
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}
