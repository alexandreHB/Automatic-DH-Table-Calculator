#include "frame.hpp"
#include "main.hpp"



Frame::Frame(int x, int y) 
{
    oX = x;
    oY = y;

    angleX = 330 * PI/180; 
    angleZ = 90 * PI/180;
}

Frame::~Frame() 
{
    cout << "frame deleted" << endl;
}

void Frame::display(SDL_Renderer* pRenderer) const
{
    SDL_SetRenderDrawColor(pRenderer, R_x_axis, G_x_axis, B_x_axis, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(pRenderer, oX, oY, oX + AXIS_LENGTH * cos(angleX), oY - AXIS_LENGTH * sin(angleX));

    SDL_SetRenderDrawColor(pRenderer, R_z_axis, G_z_axis, B_z_axis, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(pRenderer, oX, oY, oX + AXIS_LENGTH *  cos(angleZ), oY - AXIS_LENGTH * sin(angleZ));

    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
}

void Frame::rotateAxis(char nameAxis, float angleRadian) 
{
    if(nameAxis == 'x')
    {
        this->getAngleX() += angleRadian * PI/180;
        
        if(this->getAngleX() > 330*PI/180)
            this->getAngleX() = 30*PI/180;

        if(this->getAngleX() < 29*PI/180)
            this->getAngleX() = 330*PI/180;
    }

    else if (nameAxis == 'z')
    {
        this->getAngleZ() += angleRadian * PI/180;
        
        if(this->getAngleZ() > 330*PI/180)
            this->getAngleZ() = 30*PI/180;

        if(this->getAngleZ() < 29*PI/180)
            this->getAngleZ() = 330*PI/180;
    }
    
}





