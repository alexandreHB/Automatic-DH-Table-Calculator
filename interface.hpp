#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "main.hpp"

class Displayable;

class Interface
{
    public : 
        SDL_Window* pWindow;
        SDL_Renderer* pRenderer;
        SDL_Event events;
        TTF_Font* font;

        SDL_Surface* textPivot;
        SDL_Texture* t_textPivot;
        SDL_Rect rectTextPivot;

        SDL_Surface* textSliding;
        SDL_Texture* t_textSliding;
        SDL_Rect rectTextSliding;

        SDL_Surface* textAxeZ;
        SDL_Texture* t_textAxeZ;
        SDL_Rect rectAxeZ;

        SDL_Surface* textAxeX;
        SDL_Texture* t_textAxeX;
        SDL_Rect rectAxeX;
        
        Displayable* garbage_button;
        Displayable* Pivot_button;
        Displayable* Sliding_button;
        Displayable* Go_button;
        
        Interface();
        ~Interface();

        void display();
};



#endif