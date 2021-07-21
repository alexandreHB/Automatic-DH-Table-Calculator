#include "solid.hpp"
#include "main.hpp"

int Solid::compteur = -2;

Solid::Solid(int posX, int posY, int width, int height, SDL_Renderer* pRenderer)
{   
    numeroSolid = ++compteur;
    cout << "Number of solid : "<< numeroSolid+1 << "\n" << endl;
    numeroTexture = 0;
    frame = new Frame(posX+TEXTURE_SOLID_SIDE/2, posY+TEXTURE_SOLID_SIDE/2);
}

//constructor for the solid Base 
Solid::Solid(string path, int posX, int posY, int width, int height, SDL_Renderer* pRenderer)
{   
    numeroSolid = ++compteur;
    cout << "Number of solid: "<< numeroSolid+1 << "\n" << endl;
    displayable = new Displayable(path, posX, posY, width, height, pRenderer);
    frame = new Frame(posX+TEXTURE_SOLID_SIDE/2, posY+TEXTURE_SOLID_SIDE/2);
}


Solid::~Solid() 
{
    cout << "--------------------------------" << endl;
    cout << "Destruction of a solid: \n" << endl;
    delete displayable;
    delete frame;
    compteur --;
    cout << "Solid deleted \n" << endl;
    cout << "Number of solid remaining : "<< compteur+1 << "\n" << endl;
    cout << "-------------------------------- \n \n" << endl;
}


void Solid::display(SDL_Renderer* pRenderer) 
{
    this->getDisplayable()->display(pRenderer);
    this->getFrame()->display(pRenderer);

}


void Solid::changeTexture(SDL_Renderer* pRenderer) 
{    
    this->getDisplayable()->getAngleTexture() = 0;
    this->getNumeroTexture() = (++this->getNumeroTexture()) % NB_TEXTURE_LINK;

    char* temp = const_cast<char*>(this->getDisplayable()->getPath().c_str());
    strcpy(temp, (this->paths[this->getNumeroTexture()]).c_str());

    this->getDisplayable()->update(pRenderer);
}


void Solid::move(int x, int y) 
{
    this->getDisplayable()->getPosX() = x - TEXTURE_SOLID_SIDE/2;
    this->getDisplayable()->getPosY() = y - TEXTURE_SOLID_SIDE/2;
    this->getFrame()->getOx() = x;
    this->getFrame()->getOy() = y;
}



void Solid::computeAlpha(shared_ptr<Solid> next_solid)  
{
    //in degree
    float angleXiPlus1 = next_solid->getFrame()->getAngleX()*180/PI;
    float diffAngleZ = (next_solid->getFrame()->getAngleZ() - this->getFrame()->getAngleZ())*180/PI;

    if(diffAngleZ >= 180)
        diffAngleZ -= 360; 
    if(diffAngleZ <= -180)
        diffAngleZ += 360;

    // if axe zi+1 and zi are colinear 
    if((diffAngleZ >= -1 && diffAngleZ <= 1) || (diffAngleZ >= 179 && diffAngleZ <= 181))
        alpha_i = "0";

    //if xi+1 axis is pointing backward or pointing downward
    else if ((angleXiPlus1 > 29 && angleXiPlus1 < 31)  || (angleXiPlus1 > 149 && angleXiPlus1 < 151) || (angleXiPlus1 > 269 && angleXiPlus1 < 271) )
    {
        if(diffAngleZ > 0.001 && diffAngleZ != 180)
            alpha_i = "-PI/2";
        
        else if(diffAngleZ < -0.001 && diffAngleZ != 180)
            alpha_i = "+PI/2";
    }
    //if xi+1 axis is pointing forward or pointing upward
    else if ((angleXiPlus1 > 209 && angleXiPlus1 < 211) || (angleXiPlus1 > 329 && angleXiPlus1 < 331) || (angleXiPlus1 > 89 && angleXiPlus1 < 91) )
    {
        if(diffAngleZ > 0.001 && diffAngleZ != 180)
            alpha_i = "+PI/2";


        else if(diffAngleZ < -0.001 && diffAngleZ != 180)
            alpha_i = "-PI/2";
    }
}

void Solid::computeTheta(shared_ptr<Solid> next_solid)  
{                           
    //in degree                             
    float angleZi = this->getFrame()->getAngleZ()*180/PI;      
    float diffAngleX = (next_solid->getFrame()->getAngleX() - this->getFrame()->getAngleX())*180/PI;

    if(diffAngleX >= 180)
        diffAngleX -= 360; 
    if(diffAngleX <= -180)
        diffAngleX += 360;

    // if axe xi+1 and xi are colinear 
    if((diffAngleX >=  -1 && diffAngleX < 1) || (diffAngleX >= 179 && diffAngleX <= 181))
        theta_i = "0";

    //if zi axis is pointing backward or pointing downward
    else if ((angleZi > 29 && angleZi < 31) || (angleZi > 269 && angleZi < 271) || (angleZi > 149 && angleZi < 151) )
    {
        if(diffAngleX >= 0.001 && diffAngleX != 180)
            theta_i = "-PI/2";
        
        else if(diffAngleX <= -0.001 && diffAngleX != 180)
            theta_i = "+PI/2";
    }
    //if zi axis is pointing forward or pointing upward
    else if ((angleZi > 209 && angleZi < 211) || (angleZi > 89 && angleZi < 91) || (angleZi < 329 && angleZi < 331))
    {
        if(diffAngleX >= 0.001 && diffAngleX != 180)
            theta_i = "+PI/2";

        else if(diffAngleX < -0.001 && diffAngleX != 180)
            theta_i = "-PI/2";
    }
}


void Solid::computeD(shared_ptr<Solid> next_solid) 
{
    float dX = next_solid->getFrame()->getOx() - this->getFrame()->getOx();
    float dY = next_solid->getFrame()->getOy() - this->getFrame()->getOy();
    float norm = sqrt(dX*dX + dY*dY);
    float angleZi = this->getFrame()->getAngleZ() * 180/PI;

    //angle between the line which links the origins of the two frames and the horizontal
    float angle = acos(dX/norm) * 180/PI;

    //convert the symetrical [0;180] range of value of acos function into [0;360] range of value
    if(dY > 0)
        angle = 360 - angle;

    if(abs(angleZi - angle) < 30)
        this->d_i = "+l" ;
    else
        this->d_i = "0";
}



void Solid::computeA(shared_ptr<Solid> next_solid)  
{
    float dX = next_solid->getFrame()->getOx() - this->getFrame()->getOx();
    float dY = next_solid->getFrame()->getOy() - this->getFrame()->getOy();

    float norm = sqrt(dX*dX + dY*dY);
    float angleXiPlus1 = next_solid->getFrame()->getAngleX() * 180/PI;

    //angle between the line which links the origins of the two frames and the horizontal
    float angle = acos(dX/norm) * 180/PI;

    //convert the symetrical [0;180] range of value of acos function into [0;360] range of value
    if(dY > 0)
        angle = 360 - angle;

    if(abs(angleXiPlus1 - angle) < 30)    
        this->a_i = "+l";
    else
        this->a_i = "0";
}

