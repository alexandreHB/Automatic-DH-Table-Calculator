#ifndef PIVOT_HPP
#define PIVOT_HPP

#include "frame.hpp"
#include "displayable.hpp"
#include "solid.hpp"
#include "main.hpp"

class Frame;
class Displayable;
class Solid;

class Pivot : public Solid
{
    protected : 
        

    public : 
        Pivot(int posX, int posY, int width, int height, SDL_Renderer* pRenderer);

        void compute_One_Line_DH(shared_ptr<Solid> next_solid)
        {
            this->computeTheta(next_solid);
            if(theta_i == "0")
                theta_i = "Q" + to_string(numeroSolid+1);
            else
                theta_i = "Q" + to_string(numeroSolid+1) + this->theta_i;

            this->computeD(next_solid);
            if(d_i == "+l")
                d_i = "l" + to_string(this->numeroSolid+1);

            this->computeA(next_solid);
            if(a_i == "+l")
                a_i = "l" + to_string(this->numeroSolid+1);

            this->computeAlpha(next_solid);
        } 
};

#endif