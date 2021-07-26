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

/*
void Robot::cleanMatrices() 
{
    for(int i = 1; i < listeSolid.size()-1; i++)
        listeSolid[i]->cleanMatrix();
}
*/

void Robot::printMatrices() 
{
    for(int i = 1; i < listeSolid.size()-1; i++)
    {
        cout << "___________________________________________________________" << endl;
        cout << "Homogeneous Transformation Matrix from solid " << i-1 << " to solid " << i << " : \n" << endl;
        //listeSolid[i]->printMatrix();
        printMatrix(this->listeSolid[i]->homogeneous_transformation);
        cout << " " << endl;
    }
}

/*
void Robot::matrixProduct(shared_ptr<Solid> next_solid) 
{
    string res[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            res[i][j] = ' ';
            for(int k = 0; k < 4; k++)
            {
                if(k != 0)
                    res[i][j] += '+';
                res[i][j] += this->geometrical_model[i][k] + next_solid->homogeneous_transformation[k][j];
            }
        }

        for(int l = 0; l < 4; l++)
            for(int m = 0; m < 4; m++)
                this->geometrical_model[l][m] = res[l][m];
}
*/

/*
void Robot::computeGeometricalModel() 
{
    this->computeMatrices();
    this->cleanMatrices();
    this->printMatrices();

    //pour les remetres avec mes - et ()
    this->computeMatrices();

    //model geo = 0T1
    cout << " "<< endl;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            this->geometrical_model[i][j] = this->listeSolid[1]->homogeneous_transformation[i][j];
    printMatrix(this->geometrical_model);
    cout << " "<< endl;


    //0T2
    this->matrixProduct(listeSolid[2]);
    printMatrix(geometrical_model);
    

    //this->matrixProduct(listeSolid[3]);
    //printMatrix(geometrical_model);
    /*for(int k = 1; k < listeSolid.size()-1; k++)
    {
        this->matrixProduct(this->listeSolid[k+1]);

        cout << "___________________________________________________________" << endl;
        cout << "Homogeneous Transformation Matrix from solid " << 0 << " to solid " << k << " : \n" << endl;
        printMatrix(geometrical_model);
        //cout << " " << endl;
    }
    
}
*/



void Robot::computeGeometricalModel() 
{
    this->computeMatrices();        //compute tt les matrices T i-1->i
    this->printMatrices();          //affiche la version propres des matrices sans alterer leur valeurs

    //attriubution de T0->1 a GeoModel
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            this->geometrical_model[i][j] = this->listeSolid[1]->homogeneous_transformation[i][j];

    string** temp = new string*[4];
    for (int i = 0; i < 4; i++) {
        temp[i] = new string[4];
    }
    temp = matrixProduct(this->listeSolid[1]->homogeneous_transformation, this->listeSolid[2]->homogeneous_transformation);
    
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            geometrical_model[i][j] = temp[i][j];
    printSansModif(geometrical_model);
    printMatrix(geometrical_model);
    

    /*
    for(int k = 1; k < listeSolid.size()-1; k++)
    {
        this->matrixProduct(this->listeSolid[k+1]);     //calcul du nouveau GM (T0->i) + affciahge

        cout << "___________________________________________________________" << endl;
        cout << "Homogeneous Transformation Matrix from solid " << 0 << " to solid " << k << " : \n" << endl;
        printMatrix(geometrical_model);
        //printSansModif(geometrical_model);
        cout << " " << endl;
    }
    */

}


