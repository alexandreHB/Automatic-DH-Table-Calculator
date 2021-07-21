#ifndef DISPLAYABLE_HPP
#define DISPLAYABLE_HPP

#include "main.hpp"

class Displayable
{
    protected : 
        int angleTexture;
        string path;
        SDL_Surface* surface;
        SDL_Texture* texture;
        SDL_Rect rectangle;

    public : 
        Displayable(string path, int posX, int posY, int width, int height, SDL_Renderer* pRenderer);
        ~Displayable();

        //accessors
        SDL_Rect& getRectangle(){return this-> rectangle;}
        const SDL_Rect& getRectangle() const{return this-> rectangle;}

        int& getAngleTexture(){return this-> angleTexture;}
        const int& getAngleTexture() const{return this-> angleTexture;}

        SDL_Texture*& getTexture(){return this-> texture;}

        int& getPosX(){return this-> rectangle.x;}
        const int& getPosX() const{return this-> rectangle.x;}

        int& getPosY(){return this-> rectangle.y;}
        const int& getPosY() const{return this-> rectangle.y;}

        string& getPath(){return this-> path;}
        

        void display(SDL_Renderer* pRenderer);
        void update(SDL_Renderer* pRenderer);
        bool isMouseOn(int SourisX, int SourisY);

};

#endif