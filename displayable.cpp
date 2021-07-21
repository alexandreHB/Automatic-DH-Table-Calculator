#include "displayable.hpp"
#include "main.hpp"


Displayable::Displayable(string path, int posX, int posY, int width, int height, SDL_Renderer* pRenderer)
{
    this->path = path;
    this->angleTexture = 0.0f;

    SDL_Rect rect{posX, posY, width, height};
    this-> rectangle = rect;

    this -> surface = NULL;
    this -> texture = NULL;

    this -> surface = IMG_Load(path.c_str());
    if(surface == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    if(texture == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
}

Displayable::~Displayable() 
{
    SDL_DestroyTexture(texture);
    cout << "displayable deleted" << endl;
}


void Displayable::display(SDL_Renderer* pRenderer)
{
    SDL_RenderDrawRect(pRenderer, &(this->getRectangle()));
    SDL_QueryTexture(this->getTexture(), NULL, NULL, &(this->getRectangle()).w, &(this->getRectangle()).h);
    SDL_RenderCopyEx(pRenderer, this->getTexture(), nullptr, &this->getRectangle(), this->getAngleTexture(), nullptr ,SDL_FLIP_NONE);
}


//called once you change the texture of a solid
void Displayable::update(SDL_Renderer* pRenderer)  
{
    this -> surface = NULL;
    this -> surface = IMG_Load(path.c_str());
    if(surface == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    if(texture == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
}


bool Displayable::isMouseOn(int SourisX, int SourisY)
{
    if( SourisX > this->getPosX() && 
        SourisX < this->getPosX() + this->getRectangle().w && 
        SourisY > this->getPosY() && 
        SourisY < this->getPosY() + this->getRectangle().h)
        return true;
    else
        return false;
}

