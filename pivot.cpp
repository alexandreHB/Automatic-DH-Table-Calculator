#include "pivot.hpp"
#include "main.hpp"


Pivot::Pivot(int posX, int posY, int width, int height, SDL_Renderer* pRenderer) : Solid(posX, posY, width, height, pRenderer)
{
    paths[0] = "texture/pivot/pivot1.png";
    paths[1] = "texture/pivot/pivot2.png";
    paths[2] = "texture/pivot/pivot3.png";
    paths[3] = "texture/pivot/pivot4.png";
    displayable = new Displayable(paths[numeroTexture], posX, posY, width, height, pRenderer); 
}



