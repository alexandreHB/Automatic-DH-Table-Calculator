#ifndef FRAME_HPP
#define FRAME_HPP

#include "main.hpp"

class Frame
{
    protected : 
        int oX;
        int oY;
    
        //angles in radians relative to the horizontal
        float angleX;
        float angleZ;

    public : 
        Frame(int x, int y);
        ~Frame();
        
        int& getOx(){return this-> oX;}
        const int& getOx() const{return this-> oX;}

        int& getOy(){return this-> oY;}
        const int& getOy() const{return this-> oY;}

        float& getAngleX(){return this-> angleX;}
        const float& getAngleX() const{return this-> angleX;}

        float& getAngleZ(){return this-> angleZ;}
        const float& getAngleZ() const{return this-> angleZ;}


        void display(SDL_Renderer* pRenderer) const;
        void rotateAxis(char nameAxis, float angleRadian);
};


#endif