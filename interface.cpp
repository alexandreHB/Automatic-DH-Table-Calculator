#include "interface.hpp"
#include "displayable.hpp"
#include "main.hpp"


Interface::Interface() 
{
    //INITIALISATION SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)     
    {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        exit(EXIT_FAILURE);   
    }
    
    //INITIALISATION TTF
    TTF_Init();
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Initialisation error from TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    pWindow =  nullptr;
    pWindow = SDL_CreateWindow("DH calculator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_WINDOW, HEIGHT_WINDOW, SDL_WINDOW_SHOWN);     

    pRenderer = nullptr;
    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);


    //LOADING THE FONT
    font = TTF_OpenFont("font/arial.ttf", 22);
    if (font == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", TTF_GetError());
    }

    //WRITTING OF THE PIVOT TEXT
    textPivot = TTF_RenderText_Solid(font, "pivot link", SDL_Color{ 255, 0, 0, 255 });
    if(textPivot == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    t_textPivot = SDL_CreateTextureFromSurface(pRenderer, textPivot);
    if(t_textPivot == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(textPivot);

    rectTextPivot.x = WIDTH_BUTTON + WIDTH_LINK_BUTTON/2 - 50;
    rectTextPivot.y = (HEIGHT_WINDOW - HEIGHT_BUTTON) + 20;
    SDL_QueryTexture(t_textPivot, NULL, NULL, &rectTextPivot.w, &rectTextPivot.h);


    //WRITTING OF THE SLIDING TEXT
    textSliding = TTF_RenderText_Solid(font, "slinding link", SDL_Color{ 255, 0, 0, 255 });
    if(textSliding == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    t_textSliding = SDL_CreateTextureFromSurface(pRenderer, textSliding);
    if(t_textSliding == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(textSliding);

    rectTextSliding.x = WIDTH_BUTTON +  3*WIDTH_LINK_BUTTON/2 - 50;
    rectTextSliding.y = (HEIGHT_WINDOW - HEIGHT_BUTTON) + 20;
    SDL_QueryTexture(t_textSliding, NULL, NULL, &rectTextSliding.w, &rectTextSliding.h);


    //WRITTING OF THE Z AXIS
    textAxeZ = TTF_RenderText_Solid(font, "Z axis", SDL_Color{ R_z_axis, G_z_axis, B_z_axis, SDL_ALPHA_OPAQUE });
    if(textAxeZ == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    t_textAxeZ = SDL_CreateTextureFromSurface(pRenderer, textAxeZ);
    if(t_textAxeZ == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(textAxeZ);

    rectAxeZ.x = 100;
    rectAxeZ.y = 100;
    SDL_QueryTexture(t_textAxeZ, NULL, NULL, &rectAxeZ.w, &rectAxeZ.h);


    //WRITTING OF THE X AXIS
    textAxeX = TTF_RenderText_Solid(font, "X axis", SDL_Color{ R_x_axis, G_x_axis, B_x_axis, SDL_ALPHA_OPAQUE });
    if(textAxeX == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    t_textAxeX = SDL_CreateTextureFromSurface(pRenderer, textAxeX);
    if(t_textAxeX == nullptr)
    {
        SDL_Log("ERREUR >  %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(textAxeX);

    rectAxeX.x = 100;
    rectAxeX.y = 150;
    SDL_QueryTexture(t_textAxeX, NULL, NULL, &rectAxeX.w, &rectAxeX.h);
    

    garbage_button = new Displayable("texture/buttons/garbage.png", 0, HEIGHT_WINDOW - HEIGHT_BUTTON, WIDTH_BUTTON, HEIGHT_BUTTON, pRenderer);
    Pivot_button = new Displayable("texture/pivot/pivots.png", WIDTH_BUTTON, HEIGHT_WINDOW - HEIGHT_BUTTON, WIDTH_LINK_BUTTON, HEIGHT_BUTTON, pRenderer);
    Sliding_button = new Displayable("texture/sliding/slidings.png", WIDTH_BUTTON + WIDTH_LINK_BUTTON , HEIGHT_WINDOW - HEIGHT_BUTTON, WIDTH_LINK_BUTTON, HEIGHT_BUTTON, pRenderer);
    Go_button = new Displayable("texture/buttons/Go.png", WIDTH_WINDOW - WIDTH_BUTTON, HEIGHT_WINDOW - HEIGHT_BUTTON , WIDTH_BUTTON, HEIGHT_BUTTON, pRenderer);
}


Interface::~Interface() 
{
    cout << "Destruction of the interface and free allocated ressources" << endl;
    TTF_CloseFont(font);
    SDL_DestroyTexture(t_textPivot);
    SDL_DestroyTexture(t_textSliding);
    SDL_DestroyTexture(t_textAxeZ);
    SDL_DestroyTexture(t_textAxeX);

    delete garbage_button;
    delete Pivot_button;
    delete Sliding_button;
    delete Go_button;

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);

    TTF_Quit();
    SDL_Quit();
}


void Interface::display() 
{
    //COLOR OF THE BACKGROUND
    SDL_SetRenderDrawColor(this->pRenderer, R_background, G_background, B_background, SDL_ALPHA_OPAQUE);                               
    SDL_RenderClear(this->pRenderer);                                                        
    SDL_RenderCopy(this->pRenderer, NULL, NULL, NULL);                                         
    
    //DISPLAY THE TEXT
    SDL_RenderCopy(this->pRenderer, this->t_textPivot, NULL, &this->rectTextPivot); 
    SDL_RenderCopy(this->pRenderer, this->t_textSliding, NULL, &this->rectTextSliding); 
    SDL_RenderCopy(pRenderer, t_textAxeZ, NULL, &this->rectAxeZ);
    SDL_RenderCopy(pRenderer, t_textAxeX, NULL, &this->rectAxeX);

    //DISPLAY THE BUTTONS
    garbage_button->display(pRenderer);
    Go_button->display(pRenderer);
    Pivot_button->display(pRenderer);
    Sliding_button->display(pRenderer);
}
