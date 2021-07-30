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


void Solid::printOneLineDH() 
{
        //theta_i 
        cout << "   " << theta_i;
        for(int k = 0; k < 8 - theta_i.size(); k++)
            cout << " ";
        cout << "|";

        // d_i
        cout << "   " << d_i;
        for(int k = 0; k < 8 - d_i.size(); k++)
            cout << " ";
        cout << "|";

        //a_i
        cout << "   " << a_i;
        for(int k = 0; k < 8 - a_i.size(); k++)
            cout << " ";
        cout << "|";

        //alpha_i
        cout << "   " << alpha_i;
        for(int k = 0; k < 8 - alpha_i.size(); k++)
            cout << " ";
        cout << "|" << endl;
}



void Solid::computeMatrix() 
{
    string num = to_string(this->getNumSolid()+1);
    string cosAlpha;
    string sinAlpha;
    string cosTheta;
    string sinTheta;

    // alpha value assignment
    if(alpha_i == "0")
    {
        cosAlpha = "1";
        sinAlpha = "0";
    }
    else if(alpha_i == "-PI/2")
    {
        cosAlpha = "0";
        sinAlpha = "(-1)";
    }
    else if(alpha_i == "+PI/2")
    {
        cosAlpha = "0";
        sinAlpha = "1";
    }

    //theta value assignment
    if(theta_i == "0")
    {
        cosTheta = "1";
        sinTheta = "0";
    }
    else if(theta_i == "-PI/2")
    {
        cosTheta = "0";
        sinTheta = "(-1)";
    }
    else if(theta_i == "+PI/2")
    {
        cosTheta = "0";
        sinTheta = "1";
    }
    else if(theta_i == ("Q"+num))
    {
        cosTheta = "c" + num;
        sinTheta = "s" + num;
    }
    else if(theta_i == ("Q" + num + "-PI/2"))
    {
        cosTheta = "s" + num;
        sinTheta = "(-c" + num + ")";
    }
    else if(theta_i == ("Q" + num + "+PI/2"))
    {
        cosTheta = "(-s" + num + ")";
        sinTheta = "c" + num;
    }


    //filling the matrix by line
    homogeneous_transformation[0][0] = cosTheta;
    homogeneous_transformation[0][1] = "(-" + sinTheta + ")" + cosAlpha;
    homogeneous_transformation[0][2] = sinTheta + sinAlpha;
    homogeneous_transformation[0][3] = a_i + cosTheta;

    homogeneous_transformation[1][0] = sinTheta;
    homogeneous_transformation[1][1] = cosTheta + cosAlpha;
    homogeneous_transformation[1][2] = "(-" + cosTheta + ")" + sinAlpha;
    homogeneous_transformation[1][3] = a_i + sinTheta;

    homogeneous_transformation[2][0] = "0";
    homogeneous_transformation[2][1] = sinAlpha;
    homogeneous_transformation[2][2] = cosAlpha;
    homogeneous_transformation[2][3] = d_i;

    homogeneous_transformation[3][0] = "0";
    homogeneous_transformation[3][1] = "0";
    homogeneous_transformation[3][2] = "0";
    homogeneous_transformation[3][3] = "1";
}




void printMatrix(string matrix[4][4]) 
{
    string res[4][4];
    //pre treatment of the string to be more visual
    for(int m = 0; m < 4; m++)
        for(int n = 0; n < 4 ; n++)
        {
            string s = matrix[m][n];

            int found = s.find("0");
            if(found >= 0)
                s = "0";
            
            int x = count(s.begin(), s.end(), '(');
            s.erase(remove(s.begin(), s.end(), '('), s.end());
            s.erase(remove(s.begin(), s.end(), ')'), s.end());
            s.erase(remove(s.begin(), s.end(), '-'), s.end());

            if(x%2 == 1)
                s = '-' + s;

            for(int i = 0; i < s.size()-1 ; i++)
            {
                if(s.at(i+1) == '1')
                    if((s.at(i) == '0' || s.at(i) == '1' || s.at(i) == '2' || s.at(i) == '3' || s.at(i) == '4' || s.at(i) == '5' 
                        || s.at(i) == '6' || s.at(i) == '7' || s.at(i) == '8' || s.at(i) == '9'))
                        s.erase(i+1, 1);
            }
            res[m][n] = s;
        }



    //print the res matrix which stays in the scope of the function
    for(int i = 0; i < 4; i++)
    {
        cout << "|";
        for (int j = 0; j < 4; j++)
        {
            //cout << "   " << matrix[i][j];
            cout << "   " << res[i][j];
            //for(int k = 0; k < 28 - matrix[i][j].size(); k++)
            for(int k = 0; k < 28 - res[i][j].size(); k++)
                cout << " ";
        }
        cout << "| " << endl;
    }
}

void printSansModif(string matrix[4][4]) 
{
    for(int i = 0; i < 4; i++)
    {
        cout << '|';
        for (int j = 0; j < 4; j++)
        {
            cout << "   " << matrix[i][j];
            for(int k = 0; k < 28 - matrix[i][j].size(); k++)
                cout << ' ';
        }
        cout << "| " << endl;
    }
}


/*
void Solid::matrixProduct(shared_ptr<Solid> next_solid)
{
    string res[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            res[i][j] = " ";
            for(int k = 0; k < 4; k++)
            {
                if(k != 0)
                    res[i][j] += "+";

                res[i][j] += this->homogeneous_transformation[i][k] + next_solid->homogeneous_transformation[k][j];
            }
        }
}
*/

void cleanString(string& s) 
{
    int begin = s.find('+');
    int end = s.find_last_of('+');
    int numberOfMinus;

    if(begin == -1)
    {
        if(count(s.begin(), s.end(), '0') >= 1)
            s = "0";
        else
        {
            numberOfMinus = count(s.begin(), s.end(), '(');
            s.erase(remove(s.begin(), s.end(), '('), s.end());
            s.erase(remove(s.begin(), s.end(), '-'), s.end());
            s.erase(remove(s.begin(), s.end(), ')'), s.end());

            if(numberOfMinus % 2 == 1)
                s.insert(s.begin(), '-');
        }
        return;
    }

    // 1) Replace the first term by 'X's if it's equal to 0 
    if(s.find('0') < begin && s.find('0') != -1)
        for(int i = 0; i < begin; i++)
            s.at(i) = 'X';
    
    // 2) Replace the last term by 'X's if it's equal to 0 
    if(s.find_last_of('0') > end && s.find('0') != -1)
        for(int i = end+1; i < s.size(); i++)
            s.at(i) = 'X';
    
    // 3) Replace the terms between the first and the last '+' by 'X's if they are equal to 0 
    int sub_begin = begin;
    int sub_end = s.find('+', sub_begin+1); 
    while(sub_begin != -1 && sub_end !=-1)
    {
        if(s.find('0', sub_begin) > sub_begin && s.find('0', sub_begin) < sub_end && s.find('0') != -1)
            for(int i = sub_begin+1; i < sub_end; i++)
                s.at(i) = 'X';

        sub_begin = s.find('+', sub_begin+1);
        sub_end = s.find('+', sub_end+1);
    }

    // 4) Delete the 'X's
    s.erase(remove(s.begin(), s.end(), 'X'), s.end());

    // 5) Delete several '+' in a row and the last + without terms
    bool hadToDelete = false;
    for(int i = 0; i < s.size()-1; i++)
    {
        if(s.at(i) == '+' && s.at(i+1) == '+')
            hadToDelete = true;   

        if(hadToDelete)
        {
            s.erase(s.begin()+i+1);
            i--;
        }
    hadToDelete = false;
    }
    if(s.at(s.size()-1) == '+')
        s.erase(s.size()-1);

    // 6) Deletion of x1 multiplication
    for(int i = 0; i < s.size()-1 ; i++)
        if(s.at(i+1) == '1')
            if((s.at(i) == '0' || s.at(i) == '1' || s.at(i) == '2' || s.at(i) == '3' || s.at(i) == '4' || s.at(i) == '5' 
                || s.at(i) == '6' || s.at(i) == '7' || s.at(i) == '8' || s.at(i) == '9' || s.at(i) == ')'))
                    s.erase(s.begin()+i+1);

    cout << "pour l'instant : " << s << endl; 

    // 7) Simplifation of each term of the summ: treatment of  - and  (  ) betwen the first and the last +
    sub_begin = s.find('+');
    sub_end = s.find('+', sub_begin+1); 
    while(sub_end !=-1)
    {
        cout << "sub_begin : " << sub_begin << endl;
        cout << "sub_end : " << sub_end << endl;
        cout << "avant traitement : " << endl;
        cout << s.substr(sub_begin+1, sub_end-sub_begin-1) << endl;
        
        
        numberOfMinus = count(s.begin()+sub_begin, s.begin()+sub_end, '(');
        s.erase(remove(s.begin()+sub_begin, s.begin()+sub_end, '('), s.begin()+sub_end);
        s.erase(remove(s.begin()+sub_begin, s.begin()+sub_end, '-'), s.begin()+sub_end);
        s.erase(remove(s.begin()+sub_begin, s.begin()+sub_end, ')'), s.begin()+sub_end);

        //cout << "number of ( : " << numberOfMinus << endl;
        if(numberOfMinus%2 == 1 || sub_end-sub_end == 2)
        {
            s.insert(s.begin()+sub_begin+1, '-');
            //s.erase(s.begin()+sub_begin);
        }

        cout << "apres traitement : " << endl;
        cout << s.substr(sub_begin+1, sub_end-sub_begin-1) << endl;

        sub_begin = s.find('+', sub_begin+1);
        sub_end = s.find('+', sub_end+1);
        
    }


    // 8) Simplifation of each term of the summ: treatment of  - and  (  ) before the first +
    begin = 5;
    numberOfMinus = count(s.begin(), s.begin()+begin, '(');

    s.erase(remove(s.begin(), s.begin()+begin-1, '('), s.begin()+begin-1);
    s.erase(remove(s.begin(), s.begin()+begin-1, '-'), s.begin()+begin-1);
    s.erase(remove(s.begin(), s.begin()+begin-1, ')'), s.begin()+begin-1);

    if(numberOfMinus%2 == 1)
        s.insert(s.begin(),'-');


    cout << "pour l'instant : " << s << endl;
    // 9) Simplifation of each term of the summ: treatment of  - and  (  ) before the first +
    end = s.find_last_of('+');
    numberOfMinus = count(s.begin()+end, s.end(), '(');
    s.erase(remove(s.begin()+end, s.end(), '('), s.end());
    s.erase(remove(s.begin()+end, s.end(), '-'), s.end());
    s.erase(remove(s.begin()+end, s.end(), ')'), s.end());

    if(numberOfMinus%2 == 1)
        s.insert(s.begin()+end+1,'-');
    
    
    // 10) Delete the + when a - is following
    hadToDelete = false;
    for(int i = 0; i < s.size()-1; i++)
    {
        if(s.at(i) == '+' && s.at(i+1) == '-')
            hadToDelete = true;   

        if(hadToDelete)
        {
            s.erase(s.begin()+i);
            i--;
        }
    hadToDelete = false;
    }


        
    
}


string** matrixProduct(string m1[4][4], string m2[4][4]) 
{
    string res[4][4];
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            res[i][j] = " ";
            for(int k = 0; k < 4; k++)
            {
                if(k != 0)
                    res[i][j] += "+";

                res[i][j] += m1[i][k] + m2[k][j];
            }
        }

    string** p_res = new string*[4];
    for (int i = 0; i < 4; i++) {
        p_res[i] = new string[4];
    }

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            p_res[i][j] = res[i][j];

    return p_res;
}


/*
void Solid::cleanMatrix() 
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            cleanString(homogeneous_transformation[i][j]);
}
*/






