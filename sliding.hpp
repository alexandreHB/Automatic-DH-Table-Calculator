#ifndef SLIDING_HPP
#define SLIDING_HPP


#include "frame.hpp"
#include "displayable.hpp"
#include "solid.hpp"
#include "main.hpp"

class Frame;
class Displayable;
class Solid;

class Sliding : public Solid
{
    protected : 
        

    public : 
        Sliding(int posX, int posY, int largeur, int hauteur, SDL_Renderer* pRenderer);

        void compute_One_Line_DH(shared_ptr<Solid> next_solid)
        {
            this->computeTheta(next_solid);
            
            this->computeD(next_solid);
            if(this->d_i != "+l")
                d_i = "Q"+to_string(numeroSolid+1);
                //d_i = "Q";
            
            this->computeA(next_solid);
            if(a_i == "+l")
                a_i = "l" + to_string(numeroSolid+1);
                //a_i = "l";

            this->computeAlpha(next_solid);
        } 

};

#endif