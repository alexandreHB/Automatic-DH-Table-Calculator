#include "main.hpp"
#include "interface.hpp"
#include "displayable.hpp"
#include "frame.hpp"
#include "frame.hpp"
#include "solid.hpp"
#include "pivot.hpp"
#include "sliding.hpp"
#include "robot.hpp"


int main()
{
    Interface interface;
    Robot robot = Robot(interface.pRenderer);

    bool hold = false;              //does the mouse is hold or not
    int solid_selected = -2;        //last solid selected by clicking on it
    bool isOpen = true;             //does the application is open or not


    string s1 = "(-c1)1+(-s1)10+s100+l1c10+l1(-s2)+0s2(-c1)+l1(-c1)+0s1+l1+l2+(-c1)+(-s1)+01";
    cout << "avant traitement : " << s1 << endl;
    cleanString(s1);
    cout << "apres traitement : " << s1 << endl;

    /*
    string s2 = "l1(-c1)";
    cout << "avant traitement : " << s2 << endl;
    cleanString(s2);
    cout << "apres traitement : " << s2 << endl;
    */
    

    while (isOpen)  
    {
        while (SDL_PollEvent(&interface.events))
        {
            switch (interface.events.type)
            {
                case SDL_QUIT:
                    isOpen = false;    
                    break;

                case SDL_KEYDOWN:
                   //ROTATION OF SOLID
                    if (interface.events.key.keysym.sym == SDLK_r && solid_selected != -2)
                        robot.listeSolid[solid_selected+1]->getDisplayable()->getAngleTexture() += 3; //angle given in degree

                    if (interface.events.key.keysym.sym == SDLK_e && solid_selected != -2) 
                        robot.listeSolid[solid_selected+1]->getDisplayable()->getAngleTexture() -= 3;

                    //ROTATION OF Z-AXIS
                    if (interface.events.key.keysym.sym == SDLK_z && solid_selected != -2)
                        robot.listeSolid[solid_selected+1]->getFrame()->rotateAxis('z', -60);
                    if (interface.events.key.keysym.sym == SDLK_a && solid_selected != -2)
                        robot.listeSolid[solid_selected+1]->getFrame()->rotateAxis('z', 60);

                    //ROTATION OF X-AXIS
                    if (interface.events.key.keysym.sym == SDLK_s && solid_selected != -2)
                        robot.listeSolid[solid_selected+1]->getFrame()->rotateAxis('x', -60);
                    if (interface.events.key.keysym.sym == SDLK_q && solid_selected != -2)
                        robot.listeSolid[solid_selected+1]->getFrame()->rotateAxis('x', 60);

                    //CHANGE OF SOLID'S TEXTURE
                    if (interface.events.key.keysym.sym == SDLK_c && solid_selected != -2)
                        robot.listeSolid[solid_selected+1]->changeTexture(interface.pRenderer);                  
                    /*
                    //TEST
                    if (interface.events.key.keysym.sym == SDLK_t)
                    {
                        
                    }
                    */
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    hold = true;
                    
                    //CREATION OF A NEW SOLID
                    if(interface.Pivot_button->isMouseOn(interface.events.button.x, interface.events.button.y))
                        robot.listeSolid.push_back(shared_ptr<Pivot>(make_shared<Pivot>(WIDTH_WINDOW - 200, 50, TEXTURE_SOLID_SIDE, TEXTURE_SOLID_SIDE, interface.pRenderer)));                         
                    if(interface.Sliding_button->isMouseOn(interface.events.button.x, interface.events.button.y))    
                        robot.listeSolid.push_back(shared_ptr<Sliding>(make_shared<Sliding>(WIDTH_WINDOW - 200, 250, TEXTURE_SOLID_SIDE, TEXTURE_SOLID_SIDE, interface.pRenderer)));

                    //LAST SOLID SELECTED
                    for(int i = 0; i < robot.listeSolid.size(); i++)
                        if(robot.listeSolid[i]->getDisplayable()->isMouseOn(interface.events.button.x, interface.events.button.y))
                        {    
                            solid_selected = robot.listeSolid[i]->getNumSolid();
                            cout << "last solid selected  : " << solid_selected << endl;
                        }

                    //COMPUTATION 
                    if(interface.Go_button->isMouseOn(interface.events.button.x, interface.events.button.y))
                    {
                        robot.computeDH_Table();
                        robot.printDH_Table();
                        //robot.computeGeometricalModel();
                    }
                    break;

                case SDL_MOUSEBUTTONUP : 
                    hold = false;
                    break;

                case SDL_MOUSEMOTION :
                        //MOVING A SOLID
                        if(hold && robot.listeSolid[solid_selected+1]->getDisplayable()->isMouseOn(interface.events.button.x, interface.events.button.y)) 
                            robot.listeSolid[solid_selected+1]->move(interface.events.button.x, interface.events.button.y);
                    break;

                default : 
                    break;
            }
        }
        
        //DELETING A SOLID BY PUTTING IT IN THE TRASH
        for(int i = 0; i < robot.listeSolid.size(); i++)
        {
            if( robot.listeSolid[i]->getDisplayable()->getPosX() + (robot.listeSolid[i]->getDisplayable()->getRectangle().w) < WIDTH_BUTTON &&
                robot.listeSolid[i]->getDisplayable()->getPosY() > HEIGHT_WINDOW - HEIGHT_BUTTON) 
            {   
                robot.listeSolid.erase(robot.listeSolid.begin()+i);
                robot.updateNumeroSolid();
            }
        }

        //DISPLAY
        interface.display();
        robot.display(interface.pRenderer);
        SDL_SetRenderDrawColor(interface.pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(interface.pRenderer , 0, HEIGHT_WINDOW - HEIGHT_BUTTON - 3, WIDTH_WINDOW, HEIGHT_WINDOW - HEIGHT_BUTTON- 3);
        SDL_RenderPresent(interface.pRenderer);
    }
    return EXIT_SUCCESS;
}

