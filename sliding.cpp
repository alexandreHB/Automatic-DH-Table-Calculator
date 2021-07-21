#include "sliding.hpp"
#include "main.hpp"



Sliding::Sliding(int posX, int posY, int width, int height, SDL_Renderer* pRenderer) : Solid(posX, posY, width, height, pRenderer)
{
    paths[0] = "texture/sliding/sliding1.png";
    paths[1] = "texture/sliding/sliding2.png";
    paths[2] = "texture/sliding/sliding3.png";
    paths[3] = "texture/sliding/sliding4.png";
    displayable = new Displayable(paths[numeroTexture], posX, posY, width, height, pRenderer);
}
