#include "robot.hpp"
#include "main.hpp"

Robot::Robot(SDL_Renderer* pRenderer)
{
    listeSolid.push_back(shared_ptr<Solid>(make_shared<Solid>("texture/buttons/R0.png", (WIDTH_WINDOW - TEXTURE_SOLID_SIDE)/2 - 400, HEIGHT_WINDOW - 400, TEXTURE_SOLID_SIDE, TEXTURE_SOLID_SIDE, pRenderer)));
}


Robot::~Robot() 
{
    cout << "********************************" << endl;
    cout << "********************************" << endl;
    cout << "Destruction of the robot ! \n" << endl;

    for(int i = listeSolid.size()-1; i > 0; i--)
    {
        listeSolid.erase(listeSolid.begin()+i);
    }
    listeSolid.clear();

    if(listeSolid.size() == 0)
        cout << "The list of solid of the robot has been emptied" << endl;
    cout << "Robot deleted ! \n" << endl;
    cout << "********************************" << endl;
    cout << "********************************" << endl;
}

void Robot::updateNumeroSolid() 
{
    for(int i = 0; i < listeSolid.size(); i++)
        listeSolid[i]->getNumSolid() = i-1;
}


void Robot::display(SDL_Renderer* pRenderer) 
{
    for(int i = 0; i < listeSolid.size(); ++i)
    {
        listeSolid[i]->display(pRenderer);
        if(i >= 1)
        {
                    
            if(i%2 == 0)
                SDL_SetRenderDrawColor(pRenderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
            else
                SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);


            SDL_RenderDrawLine(pRenderer, listeSolid[i-1]->getDisplayable()->getPosX() + TEXTURE_SOLID_SIDE/2, listeSolid[i-1]->getDisplayable()->getPosY() + TEXTURE_SOLID_SIDE/2,
                                listeSolid[i]->getDisplayable()->getPosX() + TEXTURE_SOLID_SIDE/2,  listeSolid[i]->getDisplayable()->getPosY() + TEXTURE_SOLID_SIDE/2);
        
            if(i%2 == 0)
                SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
            else
                SDL_SetRenderDrawColor(pRenderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
        }
    }
}



void Robot::computeDH_Table() 
{
    for(int i = 1; i < listeSolid.size()-1; i++)
        listeSolid[i]->compute_One_Line_DH(listeSolid[i+1]);
}



void Robot::printDH_Table() 
{
    cout << "****************************************************" << endl;
    cout << "                DH TABLE OF THE ROBOT               " << endl;
    cout << "____________________________________________________" << endl;
    cout << " i |  Theta_i  |    d_i    |    a_i    |  Alpha_i  |" << endl;

    for(int i = 1; i <  listeSolid.size()-1; i++)
    {
        cout << " " << i << " |";
        listeSolid[i]->printOneLineDH();
    }

    cout << "____________________________________________________" << endl;
}


void Robot::computeMatrices()
{
    for(int i = 1; i < listeSolid.size()-1; i++)
        listeSolid[i]->computeMatrix();
}

void Robot::printMatrices() 
{
    for(int i = 1; i < listeSolid.size()-1; i++)
    {
        cout << "___________________________________________________________" << endl;
        cout << "Homogeneous Transformation Matrix from solid " << i-1 << " to solid " << i << " : \n" << endl;
        listeSolid[i]->printMatrix();
    }
}



/*
void Robot::computeGeometricalModel() 
{

}
*/



