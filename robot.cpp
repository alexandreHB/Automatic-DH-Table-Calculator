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
        listeSolid.erase(listeSolid.begin()+i);
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


void Robot::cleanMatrices() 
{
    for(int i = 1; i < listeSolid.size()-1; i++)
        cleanMatrix(this->listeSolid[i]->homogeneous_transformation);
}


void Robot::printMatrices() 
{
    for(int i = 1; i < listeSolid.size()-1; i++)
    {
        cout << "___________________________________________________________" << endl;
        cout << "Homogeneous Transformation Matrix from solid " << i-1 << " to solid " << i << " : \n" << endl;
        printMatrix(this->listeSolid[i]->homogeneous_transformation);
        cout << " " << endl;
    }
}




void Robot::computeGeometricalModel() 
{
    this->computeMatrices();
    this->cleanMatrices();
    this->printMatrices();

    //attriubution de T0->1 a GeoModel
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            this->geometrical_model[i][j] = this->listeSolid[1]->homogeneous_transformation[i][j];

    cout << "___________________________________________________________" << endl;
    cout << "Homogeneous Transformation Matrix from solid " << 0 << " to solid " << 1 << " : \n" << endl;
    cleanMatrix(geometrical_model);
    printMatrix(geometrical_model);
    cout << " " << endl;


    string** temp = new string*[4];
    for (int i = 0; i < 4; i++)
        temp[i] = new string[4];

    for(int k = 2; k < listeSolid.size()-1; k++)
    {
        temp = matrixProduct(this->geometrical_model, this->listeSolid[k]->homogeneous_transformation);
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                geometrical_model[i][j] = temp[i][j];

        cout << "___________________________________________________________" << endl;
        cout << "Homogeneous Transformationfonctionalité Matrix from solid " << 0 << " to solid " << k << " : \n" << endl;
        cleanMatrix(geometrical_model);
        printMatrix(geometrical_model);
        cout << " " << endl;
    }
}


