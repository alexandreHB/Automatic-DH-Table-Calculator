#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "main.hpp"
#include "solid.hpp"

class Frame;
class Displayable;
class solid;


class Robot
{
    public :
        vector<shared_ptr<Solid>> listeSolid; 
        string geometrical_model[4][4];
        
        Robot(SDL_Renderer* pRenderer);
        ~Robot();
        void updateNumeroSolid();
        void display(SDL_Renderer* pRenderer);

        void computeDH_Table();
        void printDH_Table();

        void computeMatrices();
        void cleanMatrices();
        void printMatrices();
        void computeGeometricalModel();
};

#endif
