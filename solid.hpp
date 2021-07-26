#ifndef solid_HPP
#define solid_HPP

#include "frame.hpp"
#include "displayable.hpp"
#include "main.hpp"

class Frame;class Displayable;

class Solid
{
    protected : 
        int numeroTexture;
        int numeroSolid;
        Frame* frame;
        Displayable* displayable;
        
    public : 
        string theta_i;
        string d_i;
        string a_i;
        string alpha_i;

        string homogeneous_transformation[4][4];

        static int compteur;
        string paths[NB_TEXTURE_LINK];


        Solid(string path, int posX, int posY, int width, int height, SDL_Renderer* pRenderer);
        Solid(int posX, int posY, int width, int height, SDL_Renderer* pRenderer);
        ~Solid();

        //accessors
        int& getNumSolid(){return this-> numeroSolid;}
        const int& getNumSolid() const{return this-> numeroSolid;}

        int& getNumeroTexture(){return this-> numeroTexture;}
        const int& getNumeroTexture() const{return this-> numeroTexture;}

        Displayable*& getDisplayable(){return this-> displayable;}
        Frame*& getFrame(){return this->frame;}

        //display
        virtual void display(SDL_Renderer* pRenderer);
        void changeTexture(SDL_Renderer* pRenderer);
        void move(int x, int y);

        //computing DH table
        void computeAlpha(shared_ptr<Solid> next_solid);
        void computeTheta(shared_ptr<Solid> next_solid);
        void computeD(shared_ptr<Solid> next_solid);
        void computeA(shared_ptr<Solid> next_solid);
        virtual void compute_One_Line_DH(shared_ptr<Solid> next_solid){}
        void printOneLineDH();

        //homegeneous transformation matrix
        void computeMatrix();
        //void matrixProduct(shared_ptr<Solid> next_solid);
        void cleanMatrix();
};

void printMatrix(string matrix[4][4]);
void printSansModif(string matrix[4][4]);
void cleanString(string& s);
string** matrixProduct(string m1[4][4], string m2[4][4]);


#endif