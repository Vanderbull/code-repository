#pragma once

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <utility>
using namespace std;

#include "Global\Global.h"
#include "starmap\starmap.h"
#include "techmap\techmap.h"

// Screens
#include "tech\Technology.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Game.h"
#include "SpaceShip.h"
#include "ControlGfx.h"
#include "Audio.h"
#include "Objects.h"
#include "Enemies\Powerup.h"
#include "Enemies.h"
#include "Timers.h"
//#include "Paralaxlayers.h"
#include "Animals.h"
#include "Enemies\Cubes.h"
#include "Triangles.h"
#include "Bullets.h"
#include "MainMenu.h"
#include "Credits.h"
#include "GameOver.h"
#include "Load.h"
#include "Save.h"
#include "Collision.h"
#include "OutroFinish.h"
#include "GetInput.h"
#include "World\CWorld.h"

#ifdef _WIN32
#ifdef _DEBUG
   #include <crtdbg.h>
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
   #define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

Gamestate gamestate;
Game Engine;

void InitNewGame()
{
    /*
    for (int x = 0; x < 7; ++x)
    {
        for (int k = 0; k < 7; ++k)
        {
            //q value for quality
            //t value for type

            world_array[1080 * x + k].q_value = rand() % 100;
            world_array[1080 * x + k].t_value = rand() % 100;
            world_array_two_dimensional[x][k] = world_array[1080 * x + k];
        }
    }
    std::copy(world_array, world_array + 1166400, reinterpret_cast<world_tile*>(world_array_two_dimensional));
    */

    Engine.Map = new StarMap(1920 / 64 - 5, 1080 / 64 - 5);
    TechMap *techy = new TechMap(6, 99);
    techy->Update();
}

Gamestate::Gamestate()
{
	//GameState.push(MENU_MAIN_STATE);
    GameState.push(GAME_CREDITS_STATE);

	Parallax = 0.0f;
	DeltaTime = 0.0f;
}

void Gamestate::KeyMapping(SDL_Event _event)
{
	bool KEYS[322];  // 322 is the number of SDLK_DOWN events

	for(int i = 0; i < 322; i++) { // init them all to false
	   KEYS[i] = false;
	}

	SDL_EnableKeyRepeat(0,0); // you can configure this how you want, but it makes it nice for when you want to register a key continuously being held down

	switch (_event.type) 
	{
		case SDL_KEYDOWN:
			KEYS[_event.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            KEYS[_event.key.keysym.sym] = false;
            break;
	}  
}

int capturing_spies(int spynetworks = 0, int internal_security_bonus = 0, int computer_tech_level = 0, int computer_tech_level_2 = 0, bool hiding = false)
{
    int computer_tech_bonus = 0;
    int hiding_bonus = 0;
    internal_security_bonus = 10;
    if(computer_tech_level > computer_tech_level_2)
        computer_tech_bonus = computer_tech_level + computer_tech_level_2;
    if (hiding)
        hiding_bonus = 30;

    return rand()%100+(computer_tech_bonus+hiding_bonus+internal_security_bonus);
}

int infiltrate(int spynetworks = 0, int internal_security_bonus = 0, int computer_tech_level = 0, int computer_tech_level_2 = 0, bool hiding = false)
{
    int computer_tech_bonus = 0;
    int hiding_bonus = 0;
    internal_security_bonus = 10;
    if (computer_tech_level > computer_tech_level_2)
        computer_tech_bonus = computer_tech_level + computer_tech_level_2;
    if (hiding)
        hiding_bonus = 30;

    return rand() % 100 + (computer_tech_bonus + hiding_bonus + internal_security_bonus);
}

void drawLine(SDL_Surface* dest, int x0, int y0, int x1, int y1)
{
    bool step = abs(x1 - x0)<abs(y1-y0);
    if (step)
    {
        SwapValue(x0,y0);
        SwapValue(x1,y1);
    }
    if (x1 < x0)
    {
        SwapValue(x0,x1);
        SwapValue(y0,y1);
    }
    float error=0.0;
    float rounderror = (float)abs(y1 - y0) / abs(x1-x0);
    int y=y0;
    int ystep = (y1>y0?1:-1);
    for (int i = x0; i < x1; i++)
    {
        if (step )
        {
            PutPixel(dest, y, i, 255, 255, 255);
        }
        else
        {
            PutPixel(dest,i,y,255,255,255);
        }
            error+=rounderror;
            if (error >= 0.5)
            {
                y+=ystep;
                error-= 1.0;
            }
    }
}

void LoadWeapons()
{
    string weapon_name;
    int level;
    int damage;
    int cost;
    int size;
    int power;
    string notes;

    cout << "Loading weapons" << "..." << endl;
    std::ifstream weaponfile("./src/res/weapons.txt", std::ios::in);
    if (weaponfile.is_open())
    {
        while (!weaponfile.eof())
        {
            getline(weaponfile, weapon_name);
            //weaponfile >> name;
            cout << "´Weapon name: " << weapon_name << "..." << endl;
        }
        
        //weaponfile >> level;
        //cout << "Level" << level << "..." << endl;
        //weaponfile >> damage;
        //cout << "Damage" << damage << "..." << endl;
        //weaponfile >> cost;
        //cout << "Cost" << cost << "..." << endl;
        //weaponfile >> size;
        //cout << "Size" << size << "..." << endl;
        //weaponfile >> power;
        //cout << "Power" << power << "..." << endl;
    }
    else
    {
        exit(1);
    }
    weaponfile.clear();
    weaponfile.close();

    string planet_name;

    cout << "Loading planets" << "..." << endl;
    std::ifstream planetfile("./src/res/planets.txt", std::ios::in);
    if (planetfile.is_open())
    {
        while (!planetfile.eof())
        {
            getline(planetfile, planet_name);
            //techfile >> name;
            cout << "Planet name: " << planet_name << "..." << endl;
        }

        //planetfile >> level;
        //cout << "Level" << level << "..." << endl;
        //planetfile >> damage;
        //cout << "Damage" << damage << "..." << endl;
        //planetfile >> cost;
        //cout << "Cost" << cost << "..." << endl;
        //planetfile >> size;
        //cout << "Size" << size << "..." << endl;
        //planetfile >> power;
        //cout << "Power" << power << "..." << endl;
    }
    else
    {
        exit(1);
    }
    planetfile.clear();
    planetfile.close();


    string tech_name;

    cout << "Loading techs" << "..." << endl;
    std::ifstream techfile("./src/res/techs.txt", std::ios::in);
    if (techfile.is_open())
    {
        while (!techfile.eof())
        {
            getline(techfile, tech_name);
            //techfile >> name;
            cout << "Tech name: " << tech_name << "..." << endl;
        }

        //techfile >> level;
        //cout << "Level" << level << "..." << endl;
        //techfile >> damage;
        //cout << "Damage" << damage << "..." << endl;
        //techfile >> cost;
        //cout << "Cost" << cost << "..." << endl;
        //techfile >> size;
        //cout << "Size" << size << "..." << endl;
        //techfile >> power;
        //cout << "Power" << power << "..." << endl;
    }
    else
    {
        exit(1);
    }
    techfile.clear();
    techfile.close();

    cout << "Loading computer techs" << "..." << endl;
    std::ifstream computer_techfile("./src/res/computer_techs.txt", std::ios::in);
    if (computer_techfile.is_open())
    {
        while (!computer_techfile.eof())
        {
            getline(computer_techfile, tech_name);
            //techfile >> name;
            cout << "Computer Tech name: " << tech_name << "..." << endl;
        }

        //computer_techfile >> level;
        //cout << "Level" << level << "..." << endl;
        //computer_techfile >> damage;
        //cout << "Damage" << damage << "..." << endl;
        //computer_techfile >> cost;
        //cout << "Cost" << cost << "..." << endl;
        //computer_techfile >> size;
        //cout << "Size" << size << "..." << endl;
        //computer_techfile >> power;
        //cout << "Power" << power << "..." << endl;
    }
    else
    {
        exit(1);
    }
    techfile.clear();
    techfile.close();


    string shipsize_name;

    cout << "Loading shipsizefile" << "..." << endl;
    std::ifstream shipsizefile("./src/res/shipsize.txt", std::ios::in);
    if (shipsizefile.is_open())
    {
        while (!shipsizefile.eof())
        {
            getline(shipsizefile, tech_name);
            //shipsizefile >> name;
            cout << "Tech name: " << tech_name << "..." << endl;
        }

        //shipsizefile >> level;
        //cout << "Level" << level << "..." << endl;
        //shipsizefile >> damage;
        //cout << "Damage" << damage << "..." << endl;
        //shipsizefile >> cost;
        //cout << "Cost" << cost << "..." << endl;
        //shipsizefile >> size;
        //cout << "Size" << size << "..." << endl;
        //shipsizefile >> power;
        //cout << "Power" << power << "..." << endl;
    }
    else
    {
        exit(1);
    }
    shipsizefile.clear();
    shipsizefile.close();

    int planet_pos_x,planet_pos_y;

    cout << "Loading planet positions" << "..." << endl;
    std::ifstream planet_posfile("./src/res/planet_pos.txt", std::ios::in);
    if (planet_posfile.is_open())
    {
        while (!planet_posfile.eof())
        {
            planet_posfile >> planet_pos_x >> planet_pos_y;
            cout << "Planet position ( " << planet_pos_x << "," << planet_pos_y << ")..." << endl;
        }

        //planet_posfile >> level;
        //cout << "Level" << level << "..." << endl;
        //planet_posfile >> damage;
        //cout << "Damage" << damage << "..." << endl;
        //planet_posfile >> cost;
        //cout << "Cost" << cost << "..." << endl;
        //planet_posfile >> size;
        //cout << "Size" << size << "..." << endl;
        //planet_posfile >> power;
        //cout << "Power" << power << "..." << endl;
    }
    else
    {
        exit(1);
    }
    planet_posfile.clear();
    planet_posfile.close();
}

void Game::HandleEvents( SDL_Event _event )
{
	switch ( _event.type )
	{
		// Handle mouse button events
        case SDL_MOUSEBUTTONDOWN:
        {} break;
        case SDL_MOUSEMOTION:
        {
                                int MouseXCoordinates, MouseYCoordinates;
                                SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
                                drawLine(Gfx.BackBuffer, MouseXCoordinates, MouseYCoordinates, Gfx.BackBuffer->clip_rect.w / 2, Gfx.BackBuffer->clip_rect.h / 2);
                                PutPixel(Gfx.BackBuffer, MouseXCoordinates, MouseYCoordinates, 255, 0, 0);
                                cout << capturing_spies() << endl;
                                if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w-200 &&
                                    MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                    MouseYCoordinates > Gfx.BackBuffer->clip_rect.h-200 &&
                                    MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                {
                                    cout << "Read star: " << endl;
                                }
        } break;
		case SDL_MOUSEBUTTONUP:
		{
			switch( gamestate.GameState.top()  )
			{
				case MENU_MAIN_STATE:
				{
                                        
                                        std::ofstream of("./saves/save.txt", std::ios::out);
                                        if (of.is_open())
                                        {
                                            of << "save" << endl;
                                            of << "# Mouse Coordinates" << endl;
                                            of << MouseXCoordinates << endl;
                                            of << MouseYCoordinates << endl;
                                            of << "# Stardate" << endl;
                                            of << stardate << endl;
                                            of << "#DIFFICULTY" << endl;
                                            of << DIFFICULTY << endl;
                                            of << "#SOUND" << endl;
                                            of << SOUND << endl;
                                            of << "#MUSIC" << endl;
                                            of << MUSIC << endl;
                                            of << "#RESOLUTION wxh" << endl;
                                            of << Gfx.GetSurface(0)->w << endl;
                                            of << Gfx.GetSurface(0)->h << endl;
                                        }
                                        else
                                        {
                                            exit(1);
                                        }

				} break;
				case GAME_RUNNING_STATE:
				{
                    SDL_Rect minus_sign_one; SDL_Rect plus_sign_one;

                    plus_sign_one.x = Gfx.BackBuffer->w - 50; plus_sign_one.y = 340; plus_sign_one.h = 32; plus_sign_one.w = 32;

                    if (MouseXCoordinates > plus_sign_one.x &&
                        MouseXCoordinates < plus_sign_one.x + 32 &&
                        MouseYCoordinates > plus_sign_one.y &&
                        MouseYCoordinates < plus_sign_one.y + plus_sign_one.h)
                    {
                        ship++;
                    }

                    plus_sign_one.x = Gfx.BackBuffer->w - 50; plus_sign_one.y = 378; plus_sign_one.h = 32; plus_sign_one.w = 32;

                    if (MouseXCoordinates > plus_sign_one.x &&
                        MouseXCoordinates < plus_sign_one.x + 32 &&
                        MouseYCoordinates > plus_sign_one.y &&
                        MouseYCoordinates < plus_sign_one.y + plus_sign_one.h)
                    {
                        ind++;
                    }

                    plus_sign_one.x = Gfx.BackBuffer->w - 50; plus_sign_one.y = 416; plus_sign_one.h = 32; plus_sign_one.w = 32;

                    if (MouseXCoordinates > plus_sign_one.x &&
                        MouseXCoordinates < plus_sign_one.x + 32 &&
                        MouseYCoordinates > plus_sign_one.y &&
                        MouseYCoordinates < plus_sign_one.y + plus_sign_one.h)
                    {
                        def++;
                    }
                    
                    plus_sign_one.x = Gfx.BackBuffer->w - 50; plus_sign_one.y = 456; plus_sign_one.h = 32; plus_sign_one.w = 32;
                    if (MouseXCoordinates > plus_sign_one.x &&
                        MouseXCoordinates < plus_sign_one.x + 32 &&
                        MouseYCoordinates > plus_sign_one.y &&
                        MouseYCoordinates < plus_sign_one.y + plus_sign_one.h)
                    {
                        eco++;
                    }

                    plus_sign_one.x = Gfx.BackBuffer->w - 50; plus_sign_one.y = 500; plus_sign_one.h = 32; plus_sign_one.w = 32;

                    if (MouseXCoordinates > plus_sign_one.x &&
                        MouseXCoordinates < plus_sign_one.x + 32 &&
                        MouseYCoordinates > plus_sign_one.y &&
                        MouseYCoordinates < plus_sign_one.y + plus_sign_one.h)
                    {
                        tech++;
                    }

                    minus_sign_one.x = Gfx.BackBuffer->w - 250; minus_sign_one.y = 340; minus_sign_one.h = 32; minus_sign_one.w = 32;
                    if (MouseXCoordinates > minus_sign_one.x &&
                        MouseXCoordinates < minus_sign_one.x + 32 &&
                        MouseYCoordinates > minus_sign_one.y &&
                        MouseYCoordinates < minus_sign_one.y + minus_sign_one.h)
                    {
                        ship--;
                    }

                    minus_sign_one.x = Gfx.BackBuffer->w - 250; minus_sign_one.y = 378; minus_sign_one.h = 32; minus_sign_one.w = 32;
                    if (MouseXCoordinates > minus_sign_one.x &&
                        MouseXCoordinates < minus_sign_one.x + 32 &&
                        MouseYCoordinates > minus_sign_one.y &&
                        MouseYCoordinates < minus_sign_one.y + minus_sign_one.h)
                    {
                        ind--;
                    }
                    minus_sign_one.x = Gfx.BackBuffer->w - 250; minus_sign_one.y = 416; minus_sign_one.h = 32; minus_sign_one.w = 32;
                    if (MouseXCoordinates > minus_sign_one.x &&
                        MouseXCoordinates < minus_sign_one.x + 32 &&
                        MouseYCoordinates > minus_sign_one.y &&
                        MouseYCoordinates < minus_sign_one.y + minus_sign_one.h)
                    {
                        def--;
                    }
                    minus_sign_one.x = Gfx.BackBuffer->w - 250; minus_sign_one.y = 456; minus_sign_one.h = 32; minus_sign_one.w = 32;
                    if (MouseXCoordinates > minus_sign_one.x &&
                        MouseXCoordinates < minus_sign_one.x + 32 &&
                        MouseYCoordinates > minus_sign_one.y &&
                        MouseYCoordinates < minus_sign_one.y + minus_sign_one.h)
                    {
                        eco--;
                    }
                    minus_sign_one.x = Gfx.BackBuffer->w - 250; minus_sign_one.y = 500; minus_sign_one.h = 32; minus_sign_one.w = 32;
                    if (MouseXCoordinates > minus_sign_one.x &&
                        MouseXCoordinates < minus_sign_one.x + 32 &&
                        MouseYCoordinates > minus_sign_one.y &&
                        MouseYCoordinates < minus_sign_one.y + minus_sign_one.h)
                    {
                        tech--;
                    }

                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               cout << "Read star: " << endl;
                                           }

                                           int MouseXCoordinates, MouseYCoordinates;
                                           SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
                                           drawLine(Gfx.BackBuffer, MouseXCoordinates, MouseYCoordinates, Gfx.BackBuffer->clip_rect.w / 2, Gfx.BackBuffer->clip_rect.h / 2);
                                           PutPixel(Gfx.BackBuffer, MouseXCoordinates, MouseYCoordinates, 255, 0, 0);
                                           cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
                                           cout << "Release mouse button" << endl;
                                           // ship 
                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               ship++;
                                           }
                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               stardate++;
                                           }
                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               stardate++;
                                           }
                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               stardate++;
                                           }
                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               stardate++;
                                           }
                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               stardate++;
                                           }
                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               stardate++;
                                           }
                                           if (MouseXCoordinates > Gfx.BackBuffer->clip_rect.w - 200 &&
                                               MouseXCoordinates < Gfx.BackBuffer->clip_rect.w &&
                                               MouseYCoordinates > Gfx.BackBuffer->clip_rect.h - 200 &&
                                               MouseYCoordinates < Gfx.BackBuffer->clip_rect.h)
                                           {
                                               stardate++;
                                           }
				} break;

                case GAME_LOADING_STATE:
                {
                                           SetGameOptionButtons();
                                           int MouseXCoordinates, MouseYCoordinates;
                                           SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
                                           cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
                                           for (int i = 0; i < 3; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Difficuty set to -> " << i << "..." << endl;
                                                   DIFFICULTY = i;
                                               }
                                           }
                                           for (int i = 3; i < 5; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Sound set to -> " << i << "..." << endl;
                                                   SOUND = i;
                                               }
                                           }
                                           for (int i = 5; i < 7; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Music set to -> " << i << "..." << endl;
                                                   MUSIC = i;
                                               }
                                           }
                                           for (int i = 7; i < 8; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Returning to main menu -> " << i << "..." << endl;
                                                   gamestate.GameState.pop();
                                                   gamestate.GameState.push(MENU_MAIN_STATE);
                                                   _event.type = 0;
                                               }
                                           }
                                           for (int i = 0; i < 8; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Entering button " << i << "..." << endl;
                                               }
                                           }
                } break;

                case GAME_SAVING_STATE:
                {
                                           SetGameOptionButtons();
                                           int MouseXCoordinates, MouseYCoordinates;
                                           SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
                                           cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
                                           for (int i = 0; i < 3; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Saving -> " << i << "..." << endl;
                                                   std::ofstream of("./saves/save.txt", std::ios::out);
                                                   if (of.is_open())
                                                   {
                                                        of << "save" << endl;
                                                        of << "# Mouse Coordinates" << endl;
                                                        of << MouseXCoordinates << endl;
                                                        of << MouseYCoordinates << endl;
                                                   }
                                                   else
                                                   {
                                                       exit(1);
                                                   }
                                               }
                                           }
                                           for (int i = 3; i < 5; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Sound set to -> " << i << "..." << endl;
                                                   SOUND = i;
                                               }
                                           }
                                           for (int i = 5; i < 7; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Music set to -> " << i << "..." << endl;
                                                   MUSIC = i;
                                               }
                                           }
                                           for (int i = 7; i < 8; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Returning to main menu -> " << i << "..." << endl;
                                                   gamestate.GameState.pop();
                                                   gamestate.GameState.push(MENU_MAIN_STATE);
                                                   _event.type = 0;
                                               }
                                           }
                                           for (int i = 0; i < 8; i++)
                                           {
                                               if (MouseXCoordinates > ButtonClips[i].x &&
                                                   MouseXCoordinates < ButtonClips[i].x + ButtonClips[i].w &&
                                                   MouseYCoordinates > ButtonClips[i].y &&
                                                   MouseYCoordinates < ButtonClips[i].y + ButtonClips[i].h)
                                               {
                                                   cout << "Entering button " << i << "..." << endl;
                                               }
                                           }
                } break;


				case GAME_OPTIONS_STATE:
				{
					SetGameOptionButtons();
					int MouseXCoordinates, MouseYCoordinates;
					SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
					cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
					for( int i = 0; i < 3; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Difficuty set to -> " << i << "..." << endl;
							DIFFICULTY = i;
						}
					}
					for( int i = 3; i < 5; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Sound set to -> " << i << "..." << endl;
							SOUND = i;
						}
					}
					for( int i = 5; i < 7; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Music set to -> " << i << "..." << endl;
							MUSIC = i;
						}
					}
					for( int i = 7; i < 8; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Returning to main menu -> " << i << "..." << endl;
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
							_event.type = 0;
						}
					}
					for( int i = 0; i < 8; i++ )
					{
						if(MouseXCoordinates > ButtonClips[ i ].x && 
						MouseXCoordinates < ButtonClips[ i ].x + ButtonClips[ i ].w &&
						MouseYCoordinates > ButtonClips[ i ].y &&
						MouseYCoordinates < ButtonClips[ i ].y + ButtonClips[ i ].h )
						{
							cout << "Entering button " << i << "..." << endl;
						}
					}
				} break;
			}
		} break; // END OF MOUSEUP

		case SDL_KEYDOWN:
		{
			switch( gamestate.GameState.top()  )
			{
				case MENU_MAIN_STATE:
				{
					switch( _event.key.keysym.sym )		
					{
						case SDLK_ESCAPE:
						{
							std::cout << "Trying to quit the game" << endl;
						} break;
					}
				} break;
				case GAME_CREDITS_STATE:
				{
					switch( _event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
					}
				} break;
				case GAME_SAVING_STATE:
				{
					switch( _event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
					}
				} break;
				case GAME_LOADING_STATE:
				{
					switch( _event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
					}
				} break;
				case GAME_RUNNING_STATE:
				{
						switch( _event.key.keysym.sym )
						{
							case SDLK_RIGHT:
							{
								Spaceship.xVelocity = 1.0f;
							} break;
							case SDLK_LEFT:
							{
								Spaceship.xVelocity = -1.0f;
							} break;
							case SDLK_UP:
							{
								Spaceship.yVelocity = 1.0f;
							} break;
							case SDLK_DOWN:
							{
								Spaceship.yVelocity = -1.0f;
							} break;
							case SDLK_SPACE:
							{
								if( FIRED == 0 )
								{
									BulletController.Create_Bullets();
									FIRED = 1;
									Gfx.FLIP();
									Audio.PlaySoundEffect( 4 );
								}
							} break;
							case SDLK_LALT:
							{
								Spaceship.AddAction("FIRE_SPECIAL");
							} break;
							case SDLK_RETURN:
							{
								Spaceship.AddAction("RETURN");
							} break;
							case SDLK_ESCAPE:
							{
								std::cout << "Trying to get to the menu eeeyyy!!" << endl;
								gamestate.GameState.push(MENU_MAIN_STATE);
							} break;
							default:
							{
								Spaceship.AddAction("DEFAULT");
							}
					}
				} break;
				case GAME_OPTIONS_STATE:
				{
					switch( _event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
					}
				} break;
			}
		} break;
		case SDL_KEYUP:
		{
			switch( gamestate.GameState.top()  )
			{
				case MENU_MAIN_STATE:
				{
				} break;
				case GAME_RUNNING_STATE:
				{
					switch( _event.key.keysym.sym )		
					{
						case SDLK_ESCAPE:
						{
							gamestate.GameState.push(MENU_MAIN_STATE);
						} break;
						case SDLK_RIGHT:
						{
							Spaceship.xVelocity = 0.0f;
						} break;
						case SDLK_LEFT:
						{
							Spaceship.xVelocity = 0.0f;
						} break;
						case SDLK_UP:
						{
							Spaceship.yVelocity = 0.0f;
						} break;
						case SDLK_DOWN:
						{
							Spaceship.yVelocity = 0.0f;
						} break;
						case SDLK_SPACE:
						{
							FIRED = 0;
						} break;
					}
				} break;
			}
		} break;
		case SDL_ACTIVEEVENT:
		{
			std::cout << "Hey stop focusing on other windows, get back here!" << endl;
		} break;
		case SDL_QUIT:
		{
			Quit = true;
		} break;
        default:
            cout << "Unknown event please try again.." << endl;
	}

	if(gamestate.GameState.top() == MENU_MAIN_STATE)
	{
		if( MUSIC == 5 )
			Audio.PlayMusic(rand()%3);
		else
			Audio.PauseMusic();

		SDL_GetMouseState(&MouseXCoordinates, &MouseYCoordinates);
		cout << "(" << MouseXCoordinates << "," << MouseYCoordinates << ")" << endl;
		for( int i = 0; i < 8; i++ )
		{
			if(MouseXCoordinates > gamestate.MainMenuScreen->ButtonClips[ i ].x && 
			MouseXCoordinates < gamestate.MainMenuScreen->ButtonClips[ i ].x + gamestate.MainMenuScreen->ButtonClips[ i ].w &&
			MouseYCoordinates > gamestate.MainMenuScreen->ButtonClips[ i ].y &&
			MouseYCoordinates < gamestate.MainMenuScreen->ButtonClips[ i ].y + gamestate.MainMenuScreen->ButtonClips[ i ].h )
			{
				cout << "Entering button " << i << "..." << endl;
			}
		}
		if (_event.type == SDL_MOUSEBUTTONUP )
		{
            SDL_Rect bytton;
            bytton.h = 100;
            bytton.w = 500;
            bytton.x = 700;
            bytton.y = 505;
            if (MouseXCoordinates > bytton.x &&
                MouseXCoordinates < bytton.x + bytton.w &&
                MouseYCoordinates > bytton.y &&
                MouseYCoordinates < bytton.y + bytton.h)
            {
                Audio.PauseMusic();
                gamestate.RestartGame();
                gamestate.GameState.pop();
                gamestate.GameState.push(GAME_RUNNING_STATE);
            }
            bytton.h = 100;
            bytton.w = 500;
            bytton.x = 700;
            bytton.y = 615;
            if (MouseXCoordinates > bytton.x &&
                MouseXCoordinates < bytton.x + bytton.w &&
                MouseYCoordinates > bytton.y &&
                MouseYCoordinates < bytton.y + bytton.h)
            {
                gamestate.GameState.pop();
                gamestate.GameState.push(GAME_LOADING_STATE);
            }
            bytton.h = 100;
            bytton.w = 500;
            bytton.x = 700;
            bytton.y = 750;
            if (MouseXCoordinates > bytton.x &&
                MouseXCoordinates < bytton.x + bytton.w &&
                MouseYCoordinates > bytton.y &&
                MouseYCoordinates < bytton.y + bytton.h)
            {
                InitNewGame();
                Audio.PauseMusic();
                gamestate.RestartGame();
                gamestate.GameState.pop();
                gamestate.GameState.push(GAME_RUNNING_STATE);
            }
            bytton.h = 100;
            bytton.w = 500;
            bytton.x = 700;
            bytton.y = 860;

            if (MouseXCoordinates > bytton.x &&
                MouseXCoordinates < bytton.x + bytton.w &&
                MouseYCoordinates > bytton.y &&
                MouseYCoordinates < bytton.y + bytton.h)
            {
                Game::Quit = true;
            }
			// if mouse click within boundries of one of the buttons
			for( int i = 0; i < 8; i++ )
			{
					if( _event.button.x > gamestate.MainMenuScreen->ButtonClips[ i ].x && 
					_event.button.x < gamestate.MainMenuScreen->ButtonClips[ i ].x + gamestate.MainMenuScreen->ButtonClips[ i ].w &&
					_event.button.y > gamestate.MainMenuScreen->ButtonClips[ i ].y &&
					_event.button.y < gamestate.MainMenuScreen->ButtonClips[ i ].y + gamestate.MainMenuScreen->ButtonClips[ i ].h )
					{
						if( i == 7 )
						{
							Game::Quit = true;
						}
						if( i == 6 )
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_CREDITS_STATE);
						}
						if( i == 4 )
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_OPTIONS_STATE);
						}
						if( i == 3 )
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_SAVING_STATE);
						}
						if( i == 2 )
						{
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_LOADING_STATE);
						}
						if( i == 1 )
						{
							Audio.PauseMusic();
							gamestate.RestartGame();
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_RUNNING_STATE);
						}
						if( i == 0 )
						{
							Audio.PauseMusic();
							gamestate.GameState.pop();
							gamestate.GameState.push(GAME_RUNNING_STATE);
						}
						cout << "Hit button..." << i << endl;
					}
			}
		}
	}
	else
	{
		return;
	}
}


Game::Game()
{
    Engine._Opponents.Generate();
    LoadWeapons();
	cout << "Creating the Game::Game object..." << endl;

    CubeController.LoadSpawnPoints();

	SPAWN_POSITION_X = 0;
	SPAWN_POSITION_Y = 0;
	_SCORE = 0;

	Quit = false;

	// Setup of the application icons
	//SDL_WM_SetCaption("", "res/big.ico");
	
	//SDL_WM_SetIcon(SDL_LoadBMP("res/small.bmp"), NULL);

	Init( Gfx.screen );
	
	gamestate.load_files();

	//new setclips function
    Spaceship.SetClips();
	
	// New button stuff
	
	objRectangle(_Button["BName::RESUME_GAME"], 401, 130, 350, 45 );
	objRectangle(_Button["BName::LOAD_GAME" ], 401, 242, 350, 45 );
	objRectangle(_Button["BName::SAVE_GAME" ], 401, 298, 350, 45 );
	objRectangle(_Button["BName::OPTIONS" ], 401, 355, 350, 45 );
	objRectangle(_Button["BName::UNKNOWN" ], 401, 410, 350, 45 );
	objRectangle(_Button["BName::CREDITS "], 401, 465, 350, 45 );
	objRectangle(_Button["BName::QUIT_GAME" ], 401, 519, 350, 45 );
	objRectangle(_Button["BName::UNKNOWN" ], 0, 0, 0, 0 );
	objRectangle(_Button["BName::UNKNOWN" ], 0, 0, 0, 0 );
}

int randomBool() {
    return rand() % 2 == 1;
}

void increment_stardate()
{
    stardate++;
}
// loads all graphic files and all new files and the font
void Gamestate::load_files()
{
    Engine.Map = new StarMap(1920 / 64 - 5, 1080 / 64 - 5);
    TechMap *techy = new TechMap(6,99 );

    weapon_data.init();
    current_ship_design[0].init();
    current_ship_design[1].init();
    current_ship_design[2].init();
    current_ship_design[3].init();
    current_ship_design[4].init();
    current_ship_design[5].init();



    // 30 x 16
    //StarMap *Map = new StarMap(1920/64, 1080/64);
    //Map->Dump();
    //delete Map;

    /*
    int galaxy_size = SMALL_GALAXY;
    cout << "Galaxy size" << endl;
    cout << "-----------" << endl;
    cout << "Small(24)" << endl;
    cout << "Medium(48)" << endl;
    cout << "Large(70)" << endl;
    cout << "Huge(108)" << endl;
    cin >> galaxy_size;

    int difficulty = 1;
    cout << "Galaxy size" << endl;
    cout << "-----------" << endl;
    cout << "Simple" << endl;
    cout << "Easy" << endl;
    cout << "Average" << endl;
    cout << "Hard" << endl;
    cout << "Impossible" << endl;
    cin >> difficulty;

    int opponents = 1;
    cout << "Opponents" << endl;
    cout << "-----------" << endl;
    cout << "1-8" << endl;
    cin >> opponents;

    int race = 1;
    cout << "Choose race" << endl;
    cout << "-----------" << endl;
    cout << "Human" << endl;
    cout << "Mrrshan" << endl;
    cout << "Silicoid" << endl;
    cout << "Sakkra" << endl;
    cout << "Psilon" << endl;
    cout << "Alkari" << endl;
    cout << "Klackon" << endl;
    cout << "Bulrathi" << endl;
    cout << "Meklar" << endl;
    cout << "Darlok" << endl;
    cin >> race;

    int banner = 1;
    cout << "Choose banner" << endl;
    cout << "-----------" << endl;
    cout << "Blue" << endl;
    cout << "Green" << endl;
    cout << "Purple" << endl;
    cout << "Red" << endl;
    cout << "White" << endl;
    cout << "Yellow" << endl;
    cin >> banner;

    string name = "Alexander";
    cout << "Your name" << endl;
    cout << "-----------" << endl;
    cin >> name;

    string homeworld = "Sol";
    cout << "Home World..." << endl;
    cout << "-----------" << endl;
    cin >> homeworld;

    for (int i = 0; i < SMALL_GALAXY; i++)
    {
        PLANET[i] = randomBool();
        cout << PLANET[i] << endl;
    }
    */

	std::ifstream file;
	file.open("graphics.txt");
	if (!file)
	{
		MessageBox(NULL,"CFG: File couldn't be found!\n","Failed Loading",MB_OK);
		exit(1);
	}

	std::string line;
	size_t lineNo = 0;
	while (std::getline(file, line))
	{
		lineNo++;
		std::string temp = line;

		if (temp.empty())
			continue;
	}

	file.close();

    m_srfgui = Gfx.Load_imageAlpha("src/res/gui.png", 0, 0, 0);

    // gamesetup
    m_srfnew_game_options = Gfx.Load_imageAlpha("src/res/new_game_options.png", 0, 0, 0);

    // gamesetup
    m_srfchoose_race = Gfx.Load_imageAlpha("src/res/choose_race.png", 0, 0, 0);

    // gamesetup
    m_srfmain_menu = Gfx.Load_imageAlpha("src/res/main_menu.png", 0, 0, 0);
    // gamesetup
    m_srfgamesetup = Gfx.Load_imageAlpha("src/res/game_setup.png", 0, 0, 0);
    
    m_srfspaceship = Gfx.Load_imageAlpha("src/res/spaceship.png", 0, 0, 0);

        // 288x337px
    m_srfhuman = Gfx.Load_imageAlpha("src/res/human.png", 0, 0, 0);
    m_srfmrrshan = Gfx.Load_imageAlpha("src/res/mrrshan.png", 0, 0, 0);
    m_srfsilicoid = Gfx.Load_imageAlpha("src/res/silicoid.png", 0, 0, 0);
    m_srfsakkra = Gfx.Load_imageAlpha("src/res/sakkra.png", 0, 0, 0);
    m_srfpsilon = Gfx.Load_imageAlpha("src/res/psilon.png", 0, 0, 0);
    m_srfalkari = Gfx.Load_imageAlpha("src/res/alkari.png", 0, 0, 0);
    m_srfklackon = Gfx.Load_imageAlpha("src/res/klackon.png", 0, 0, 0);
    m_srfbulrathi = Gfx.Load_imageAlpha("src/res/bulrathi.png", 0, 0, 0);
    m_srfmeklar = Gfx.Load_imageAlpha("src/res/meklar.png", 0, 0, 0);
    m_srfdarlok = Gfx.Load_imageAlpha("src/res/darlok.png", 0, 0, 0);

    //banner
    m_srfblue_banner = Gfx.Load_imageAlpha("src/res/blue_banner.png", 0, 0, 0);
    m_srfgreen_banner = Gfx.Load_imageAlpha("src/res/green_banner.png", 0, 0, 0);
    m_srfpurple_banner = Gfx.Load_imageAlpha("src/res/purple_banner.png", 0, 0, 0);
    m_srfred_banner = Gfx.Load_imageAlpha("src/res/red_banner.png", 0, 0, 0);
    m_srfwhite_banner = Gfx.Load_imageAlpha("src/res/white_banner.png", 0, 0, 0);
    m_srfyellow_banner = Gfx.Load_imageAlpha("src/res/yellow_banner.png", 0, 0, 0);


    m_srfsmallmap = Gfx.Load_imageAlpha("src/res/smallmap.png", 0, 0, 0);
    m_srfmediummap = Gfx.Load_imageAlpha("src/res/mediummap.png", 0, 0, 0);
    m_srflargemap = Gfx.Load_imageAlpha("src/res/largemap.png", 0, 0, 0);
    m_srfhugemap = Gfx.Load_imageAlpha("src/res/hugemap.png", 0, 0, 0);

	m_srfBackdrop = Gfx.Load_imageAlpha( "Graphics/Backdrops/srfBackdrop.png", 0, 0, 0 );
	m_srfBlack = Gfx.Load_imageAlpha( "Graphics/srfBlack.png", 0, 0, 0 );
	Spaceship._SurfaceID = Gfx.Load_imageAlpha( "Graphics/demonSurface.png", 255, 255, 255 );
	m_srfAsteroid = Gfx.Load_imageAlpha( "Graphics/srfAsteroid.png", 255, 255, 255 );
	m_srfStart = Gfx.Load_imageAlpha( "Graphics/Backdrops/srfStart.png", 237, 234, 214 );
	m_srfButtons = Gfx.Load_imageAlpha( "Graphics/srfButtons.png", 255, 255, 255 );
	m_srfIntro = Gfx.Load_imageAlpha( "Graphics/srfIntro.png", 255, 255, 255 );
	m_srfOutro = Gfx.Load_imageAlpha( "Graphics/srfOutro.png", 0, 0, 0 );
	m_srfHealth = Gfx.Load_imageAlpha( "Graphics/srfHealth.png", 0, 0, 0 );
	m_srfLaser = Gfx.Load_imageAlpha( "Graphics/srfLaser.png", 255, 255, 255 );
	m_srfCredits = Gfx.Load_imageAlpha( "Graphics/Backdrops/srfCredits.png", 255, 255, 255 );
	m_srfOptions = Gfx.Load_imageAlpha( "Graphics/Backdrops/srfOptions.png", 255, 255, 255 );
	m_srfLoad = Gfx.Load_imageAlpha( "Graphics/Backdrops/srfLoad.png", 255, 255, 255 );
	m_srfSave = Gfx.Load_imageAlpha( "Graphics/Backdrops/srfSave.png", 255, 255, 255 );
	m_srfCube = Gfx.Load_imageAlpha( "Graphics/srfCube.png", 255, 255, 255 );
	m_srfTriangle = Gfx.Load_imageAlpha( "Graphics/srfTriangle.png", 255, 255, 255 );
	m_srfButtonActive = Gfx.Load_imageAlpha( "Graphics/Backdrops/srfButtonActive.png", 255, 255, 255 );
	
	/*
	std::map<string,int> m_SurfaceCollection;
	
	m_SurfaceCollection["Graphics/srfCity.png"] = Gfx.Load_imageAlpha( "Graphics/srfCity.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfClouds.png"] = Gfx.Load_imageAlpha( "Graphics/srfClouds.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfBlack.png"] = Gfx.Load_imageAlpha( "Graphics/srfBlack.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfSky.png"] = Gfx.Load_imageAlpha( "Graphics/srfSky.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/demonSurface.png"] = Gfx.Load_imageAlpha( "Graphics/demonSurface.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfEnemyZombie.png"] = Gfx.Load_imageAlpha( "Graphics/srfEnemyZombie.png", 255, 0, 255 );
	m_SurfaceCollection["Graphics/srfCrow.png"] = Gfx.Load_imageAlpha( "Graphics/srfCrow.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfdemonLife.png"] = Gfx.Load_imageAlpha( "Graphics/srfdemonLife.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfdemonHealthAndFire.png"] = Gfx.Load_imageAlpha( "Graphics/srfdemonHealthAndFire.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfDragon.png"] = Gfx.Load_imageAlpha( "Graphics/srfDragon.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfStart.png"] = Gfx.Load_imageAlpha( "Graphics/srfStart.png", 237, 234, 214 );
	m_SurfaceCollection["Graphics/srfButtons.png"] = Gfx.Load_imageAlpha( "Graphics/srfButtons.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfIntro.png"] = Gfx.Load_imageAlpha( "Graphics/srfIntro.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfMorphing.png"] = Gfx.Load_imageAlpha( "Graphics/srfMorphing.png", 255, 255, 241 );
	m_SurfaceCollection["Graphics/srfOutro.png"] = Gfx.Load_imageAlpha( "Graphics/srfOutro.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfButton.png"] = Gfx.Load_imageAlpha( "Graphics/srfButton.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfHealth.png"] = Gfx.Load_imageAlpha( "Graphics/srfHealth.png", 0, 0, 0 );
	m_SurfaceCollection["Graphics/srfLaser.png"] = Gfx.Load_imageAlpha( "Graphics/srfLaser.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfCredits.png"] = Gfx.Load_imageAlpha( "Graphics/srfCredits.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfOptions.png"] = Gfx.Load_imageAlpha( "Graphics/srfOptions.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfLoad.png"] = Gfx.Load_imageAlpha( "Graphics/srfLoad.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfSave.png"] = Gfx.Load_imageAlpha( "Graphics/srfSave.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfCube.png"] = Gfx.Load_imageAlpha( "Graphics/srfCube.png", 255, 255, 255 );
	m_SurfaceCollection["Graphics/srfTriangle.png"] = Gfx.Load_imageAlpha( "Graphics/srfTriangle.png", 255, 255, 255 );
	
	for (const auto &p : m_SurfaceCollection)
		std::cout << p.first << " => " << p.second << '\n';
*/

	MainMenuScreen = new MainMenu( 290,  m_srfStart, m_srfButtons );
	CreditsScreen = new Credits( 290,  m_srfCredits, m_srfButtons );
	OptionsScreen = new Options( 290, m_srfOptions, m_srfButtons );
	LoadsScreen = new Load( 290, m_srfLoad, m_srfButtons );
	SavesScreen = new Save( 290, m_srfSave, m_srfButtons );
	GameOverScreen = new GameOver( 290,  m_srfStart, m_srfButtons );
    TechScreen = new Technology(290, m_srfCredits, m_srfButtons);
}

void Gamestate::ResetEnemies()
{
	//if(EnemyController.Enemies.size() != NULL )
	//{
	//	EnemyController.Enemies.clear();
	//}
}



// ----------------------------------------------------------------------------
// Update() - Updates the whole game depending on which state it is in
// ----------------------------------------------------------------------------
void Game::Update( SDL_Event input, int iElapsedTime )
{
	// Check game state
	switch( gamestate.GameState.top() )
	{
        case GAME_GAME_STATE:
		case MENU_MAIN_STATE:
			{
				gamestate.MainScreen(iElapsedTime);
			} break;
		case GAME_CREDITS_STATE:
			{
				gamestate.CreditScreen(iElapsedTime);
			} break;
		case GAME_OPTIONS_STATE:
			{
				gamestate.OptionScreen(iElapsedTime);
			} break;
		case GAME_LOADING_STATE:
			{
				gamestate.LoadScreen(iElapsedTime);
			} break;
		case GAME_SAVING_STATE:
			{
				gamestate.SaveScreen(iElapsedTime);
			} break;
        case GAME_DESIGN_STATE:
        {
            gamestate.CreditScreen(iElapsedTime);
        } break;
		case GAME_RUNNING_STATE:
			{
                static bool galaxy_set = false;
                if (!galaxy_set)
                {
                    SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfnew_game_options), &Gfx.GetSurface(gamestate.m_srfnew_game_options)->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
                    Gfx.FLIP();
                    cout << "Galaxy size" << endl;
                    cout << "-----------" << endl;
                    cout << "Small(24)" << endl;
                    cout << "Medium(48)" << endl;
                    cout << "Large(70)" << endl;
                    cout << "Huge(108)" << endl;
                    //cin >> galaxy_size;
                    galaxy_set = true;

                    cout << "Galaxy size" << endl;
                    cout << "-----------" << endl;
                    cout << "Simple" << endl;
                    cout << "Easy" << endl;
                    cout << "Average" << endl;
                    cout << "Hard" << endl;
                    cout << "Impossible" << endl;
                    //cin >> difficulty;

                    cout << "Opponents" << endl;
                    cout << "-----------" << endl;
                    cout << "1-8" << endl;
                    //cin >> opponents;
                    SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfchoose_race), &Gfx.GetSurface(gamestate.m_srfchoose_race)->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
                    Gfx.FLIP();
                    cout << "Choose race" << endl;
                    cout << "-----------" << endl;
                    cout << "Human" << endl;
                    cout << "Mrrshan" << endl;
                    cout << "Silicoid" << endl;
                    cout << "Sakkra" << endl;
                    cout << "Psilon" << endl;
                    cout << "Alkari" << endl;
                    cout << "Klackon" << endl;
                    cout << "Bulrathi" << endl;
                    cout << "Meklar" << endl;
                    cout << "Darlok" << endl;
                    //cin >> race;
                    if (race == 0)
                        SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfchoose_race), &Gfx.GetSurface(gamestate.m_srfchoose_race)->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
                    if (galaxy_size == 0)
                        SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfnew_game_options), &Gfx.GetSurface(gamestate.m_srfnew_game_options)->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
                    Gfx.FLIP();
                    cout << "Choose banner" << endl;
                    cout << "-----------" << endl;
                    cout << "Blue" << endl;
                    cout << "Green" << endl;
                    cout << "Purple" << endl;
                    cout << "Red" << endl;
                    cout << "White" << endl;
                    cout << "Yellow" << endl;
                    //cin >> banner;

                    string name = "Alexander";
                    cout << "Your name" << endl;
                    cout << "-----------" << endl;
                    //cin >> name;

                    string homeworld = "Sol";
                    cout << "Home World..." << endl;
                    cout << "-----------" << endl;
                    //cin >> homeworld;
                    // 30 x 16

                    //Map->Dump();
                    //delete Map;
                    }

                    SDL_GetMouseState(&Engine.MouseXCoordinates, &Engine.MouseYCoordinates);

                    static int fleet_pos_x = Engine.MouseXCoordinates;
                    static int fleet_pos_y = Engine.MouseYCoordinates;

                    static int tile_fleet_x = Align(fleet_pos_x, 64);
                    static int tile_fleet_y = Align(fleet_pos_y, 64);

                    static int old_tile_clicked_x;
                    static int old_tile_clicked_y;

                    static int tile_clicked_x;
                    static int tile_clicked_y;

                    static SDL_Rect fleet_pos_coords;


                    SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfsmallmap), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
                    SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfgui), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
                    SDL_Rect tmp = SDL_GetVideoSurface()->clip_rect;
                    SDL_Rect oldtmp = SDL_GetVideoSurface()->clip_rect;

                    old_tile_clicked_x = tile_clicked_x;
                    old_tile_clicked_y = tile_clicked_y;

                    tile_clicked_x = Align(Engine.MouseXCoordinates, 64);
                    tile_clicked_y = Align(Engine.MouseYCoordinates, 64);

                    oldtmp.x = tile_clicked_x;
                    oldtmp.y = tile_clicked_y;
                    oldtmp.w = 64;
                    oldtmp.h = 80;

                    tmp.x = old_tile_clicked_x;
                    tmp.y = old_tile_clicked_y;
                    tmp.w = 64;
                    tmp.h = 64;

                    //Map->Dump();
                    SDL_Rect grid_coords;
                                   


                                   if (SDL_GetMouseState(&fleet_pos_x, &fleet_pos_y) & SDL_BUTTON_LMASK)
                                   {
                                       tile_fleet_x = Align(fleet_pos_x, 64);
                                       tile_fleet_y = Align(fleet_pos_y, 64);
                                       fleet_pos_coords.x = tile_fleet_x;
                                       fleet_pos_coords.y = tile_fleet_y;
                                       fleet_pos_coords.w = 64;
                                       fleet_pos_coords.h = 64;
                                       SDL_FillRect(Gfx.BackBuffer, &oldtmp, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
                                   }

                                   //int tile_clicked_x = (200 + MouseXCoordinates) / (Gfx.BackBuffer->clip_rect.w / 14);
                                   //int tile_clicked_y = (500 + MouseYCoordinates) / (Gfx.BackBuffer->clip_rect.h / 10);

                                   //SDL_FillRect(Gfx.BackBuffer, &tmp, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 0, 0));
                                   //drawLine(Gfx.BackBuffer, MouseXCoordinates, MouseYCoordinates, tile_clicked_x, tile_clicked_y);
                                   //putPixel(Gfx.BackBuffer, tile_clicked_x, tile_clicked_y, 255, 0, 0);
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfhuman), &Gfx.GetSurface(m_srfhuman)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 288;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfmrrshan), &Gfx.GetSurface(m_srfmrrshan)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 288;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfsilicoid), &Gfx.GetSurface(m_srfsilicoid)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 288;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfsakkra), &Gfx.GetSurface(m_srfsakkra)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 288;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfpsilon), &Gfx.GetSurface(m_srfpsilon)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x = 0;
                                   //tmp.y += 337;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfalkari), &Gfx.GetSurface(m_srfalkari)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 288;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfklackon), &Gfx.GetSurface(m_srfklackon)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 288;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfbulrathi), &Gfx.GetSurface(m_srfbulrathi)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 288;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfmeklar), &Gfx.GetSurface(m_srfmeklar)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 288;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfdarlok), &Gfx.GetSurface(m_srfdarlok)->clip_rect, Gfx.BackBuffer, &tmp);


                                   //tmp = SDL_GetVideoSurface()->clip_rect;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfblue_banner), &Gfx.GetSurface(m_srfblue_banner)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 384;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfgreen_banner), &Gfx.GetSurface(m_srfgreen_banner)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 384;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfpurple_banner), &Gfx.GetSurface(m_srfpurple_banner)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x = 0;
                                   //tmp.y += 216;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfred_banner), &Gfx.GetSurface(m_srfred_banner)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 384;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfwhite_banner), &Gfx.GetSurface(m_srfwhite_banner)->clip_rect, Gfx.BackBuffer, &tmp);
                                   //tmp.x += 384;
                                   //SDL_BlitSurface(Gfx.GetSurface(m_srfyellow_banner), &Gfx.GetSurface(m_srfyellow_banner)->clip_rect, Gfx.BackBuffer, &tmp);

                                   

                                   //SDL_BlitSurface(&Gfx.m_SurfaceCollection["Graphics/Backdrops/srfStart.png"], &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
				//LevelProgress += iElapsedTime / 150;
				//Gfx.DrawParallaxLayers();
				//Gfx.DrawObjects();
				//
				//
				//CollisionController.ObjectCollider( BulletController.BulletArrayRef, AnimalController.AnimalArrayRef );
				//CollisionController.ObjectCollider( BulletController.BulletArrayRef, CubeController.CubeArrayRef );
				//CollisionController.ObjectCollider( BulletController.BulletArrayRef, TriangleController.TriangleArrayRef );
				//
				//CollisionController.SpaceshipCollider(Spaceship,AnimalController.AnimalArrayRef );
				//CollisionController.SpaceshipCollider(Spaceship,CubeController.CubeArrayRef );
				//CollisionController.SpaceshipCollider(Spaceship,TriangleController.TriangleArrayRef );
				//
				//SDL_Surface * SrfProgress;
				//SrfProgress = TTF_RenderText_Solid( Gfx.DefaultFont, std::to_string(LevelProgress).c_str(), Gfx.WhiteRGB );
				//Gfx.apply_surface( 300, 50, SrfProgress, Gfx.BackBuffer );

				//Gfx.DrawScore(300,25,UpdateScore());

				//if(LevelProgress < 50000)
				//{
				//					Gfx.srfText = TTF_RenderText_Blended(Gfx.DefaultFont,"You have just escaped from the clutches of the evil empire of 'Are you square or round'. Good luck!",Gfx.WhiteRGB);//TTF_RenderText_Shaded( Gfx.DefaultFont, " YOU DIED STOP PLAYING GOD DAMN YOU!!!!! ", Gfx.WhiteRGB, Gfx.BlackRGB );
				//					Gfx.apply_surface( Gfx.BackBuffer->w /4, Gfx.BackBuffer->h/2, Gfx.srfText, Gfx.BackBuffer );
				//}

				//// rising text for score
				//static int raise = -1;

				//if(!PopupScore.empty())
				//{
				//	if( raise < 0 )
				//	{
				//		raise = PopupScore.back();
				//		PopupScore.pop_back();
				//	}
				//}
				//
				//if(raise < 0)
				//{
				//	Gfx.srfText = TTF_RenderText_Blended(Gfx.DefaultFont,std::to_string(raise).c_str(),Gfx.WhiteRGB);
				//	Gfx.apply_surface( Gfx.BackBuffer->w / 2, Gfx.BackBuffer->h / 2 -50, Gfx.srfText, Gfx.BackBuffer );
				//}
				//else
				//{
				//	Gfx.srfText = TTF_RenderText_Blended(Gfx.DefaultFont,std::to_string(raise).c_str(),Gfx.WhiteRGB);
				//	Gfx.apply_surface( Gfx.BackBuffer->w / 2, Gfx.BackBuffer->h / 2 + raise, Gfx.srfText, Gfx.BackBuffer );
				//	raise--;
				//}
    //            Gfx.DrawSprite();
    // 1920 / 64 - 5, 1080 / 64 - 5
                                   
                for (int y = 0; y < 1080 / 64 - 5; y++)
                for (int x = 0; x < 1920 / 64 - 5; x++)
                {
                    static int old_x,old_y;
                    if (Engine.Map->stars->here(x , y ))
                    {
                            grid_coords.h = 63;
                            grid_coords.w = 63;
                            grid_coords.x = x * 64;
                            grid_coords.y = y * 64;
                            if (Engine.Map->stars->GetStar(x, y)->population < 10)
                            {
                                SDL_FillRect(Gfx.BackBuffer, &grid_coords, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                                PutPixel(Gfx.BackBuffer, x, y, 0, 0, 255);
                            }
                            else
                            if (Engine.Map->stars->GetStar(x, y)->population < 50)
                            {
                                SDL_FillRect(Gfx.BackBuffer, &grid_coords, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 0, 0));
                                PutPixel(Gfx.BackBuffer, x, y, 255, 0, 0);

                            }
                            else
                            if (Engine.Map->stars->GetStar(x, y)->population < 100)
                            {
                                SDL_FillRect(Gfx.BackBuffer, &grid_coords, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 255, 0, 0));
                                PutPixel(Gfx.BackBuffer,x,y,0,255,0);

                            }
                    }
                }



                SDL_Surface * SrfProgress;
                SrfProgress = TTF_RenderText_Solid( Gfx.DefaultFont, std::to_string(stardate).c_str(), Gfx.WhiteRGB );
                Gfx.apply_surface(Gfx.BackBuffer->w-75, 10, SrfProgress, Gfx.BackBuffer);

                if (Engine.Map->stars->here(tile_clicked_x/64, tile_clicked_y/64))
                {
                    //RenderPixelMap(Gfx);
                    stringstream get_enviroment_text;
                    get_enviroment_text << Engine.Map->stars->GetStar(tile_clicked_x / 64, tile_clicked_y / 64)->GetEnviromentText();
                    string str_enviroment_text = "";
                    str_enviroment_text.append(get_enviroment_text.str());
                    SDL_Surface * srfenviromenttext;
                    srfenviromenttext = TTF_RenderText_Solid(Gfx.DefaultFont, str_enviroment_text.c_str(), Gfx.WhiteRGB);
                    //Gfx.apply_surface(tile_clicked_x, tile_clicked_y, srfenviromenttext, Gfx.BackBuffer);
                    Gfx.apply_surface(Gfx.BackBuffer->w - 150, 146, srfenviromenttext, Gfx.BackBuffer);
                    SDL_FreeSurface(srfenviromenttext);

                    stringstream get_special_text;
                    get_special_text << Engine.Map->stars->GetStar(tile_clicked_x / 64, tile_clicked_y / 64)->GetSpecialText();
                    string str_special_text = "";
                    str_special_text.append(get_special_text.str());
                    SDL_Surface * srfspecialtext;
                    srfspecialtext = TTF_RenderText_Solid(Gfx.DefaultFont, str_special_text.c_str(), Gfx.WhiteRGB);
                    //Gfx.apply_surface(tile_clicked_x, tile_clicked_y, srfspecialtext, Gfx.BackBuffer);
                    Gfx.apply_surface(Gfx.BackBuffer->w - 150, 166, srfspecialtext, Gfx.BackBuffer);
                    SDL_FreeSurface(srfspecialtext);
                    
                    stringstream ssss;
                    //ssss << Engine.Map->stars->GetStar(tile_clicked_x/64, tile_clicked_y/64)->population;
                    ssss << Engine.Map->stars->GetStar(tile_clicked_x / 64, tile_clicked_y / 64)->population;
                    string str_pop = "";
                    str_pop.append(ssss.str());
                    SDL_Surface * srfpop;
                    srfpop = TTF_RenderText_Solid(Gfx.DefaultFont, str_pop.c_str(), Gfx.WhiteRGB);
                    Gfx.apply_surface(tile_clicked_x, tile_clicked_y, srfpop, Gfx.BackBuffer);
                    Gfx.apply_surface(Gfx.BackBuffer->w - 110, 215, srfpop, Gfx.BackBuffer);
                    SDL_FreeSurface(srfpop);
                }
                SDL_Rect minus_sign_one;
                SDL_Rect plus_sign_one;
                minus_sign_one.x = Gfx.BackBuffer->w - 250;
                minus_sign_one.y = 340;
                minus_sign_one.h = 32;
                minus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &minus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                minus_sign_one.x = Gfx.BackBuffer->w - 250;
                minus_sign_one.y = 378;
                minus_sign_one.h = 32;
                minus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &minus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                minus_sign_one.x = Gfx.BackBuffer->w - 250;
                minus_sign_one.y = 416;
                minus_sign_one.h = 32;
                minus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &minus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                minus_sign_one.x = Gfx.BackBuffer->w - 250;
                minus_sign_one.y = 456;
                minus_sign_one.h = 32;
                minus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &minus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                minus_sign_one.x = Gfx.BackBuffer->w - 250;
                minus_sign_one.y = 500;
                minus_sign_one.h = 32;
                minus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &minus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                minus_sign_one.x = Gfx.BackBuffer->w - 250;
                minus_sign_one.y = 538;
                minus_sign_one.h = 32;
                minus_sign_one.w = 32;


                plus_sign_one.x = Gfx.BackBuffer->w - 50;
                plus_sign_one.y = 340;
                plus_sign_one.h = 32;
                plus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &plus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                plus_sign_one.x = Gfx.BackBuffer->w - 50;
                plus_sign_one.y = 378;
                plus_sign_one.h = 32;
                plus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &plus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                plus_sign_one.x = Gfx.BackBuffer->w - 50;
                plus_sign_one.y = 416;
                plus_sign_one.h = 32;
                plus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &plus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                plus_sign_one.x = Gfx.BackBuffer->w - 50;
                plus_sign_one.y = 456;
                plus_sign_one.h = 32;
                plus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &plus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                plus_sign_one.x = Gfx.BackBuffer->w - 50;
                plus_sign_one.y = 500;
                plus_sign_one.h = 32;
                plus_sign_one.w = 32;

                SDL_FillRect(Gfx.BackBuffer, &plus_sign_one, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 255, 0));
                plus_sign_one.x = Gfx.BackBuffer->w - 200;
                plus_sign_one.y = 538;
                plus_sign_one.h = 32;
                plus_sign_one.w = 32;

                SDL_Rect button_one,button_two,button_three,button_four,button_five,button_six;
                button_one.h = 50;
                button_one.w = 200;
                button_one.x = 930;
                button_one.y = Gfx.BackBuffer->h-50;
               
                button_two.h = 50;
                button_two.w = 200;
                button_two.x = 1070;
                button_two.y = Gfx.BackBuffer->h-50;
               
                button_three.h = 50;
                button_three.w = 200;
                button_three.x = 1210;
                button_three.y = Gfx.BackBuffer->h-50;
               
                button_four.h = 50;
                button_four.w = 200;
                button_four.x = 1350;
                button_four.y = Gfx.BackBuffer->h-50;
               
                button_five.h = 50;
                button_five.w = 200;
                button_five.x = 1490;
                button_five.y = Gfx.BackBuffer->h -50;
               
                button_six.h = 50;
                button_six.w = 200;
                button_six.x = 1630;
                button_six.y = Gfx.BackBuffer->h -50;

                SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &button_one);
                SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &button_two);
                SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &button_three);
                SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &button_four);
                SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &button_five);
                SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &button_six);
                int trigger_x;
                int trigger_y;
                
                //SDL_FillRect(Gfx.BackBuffer, &button_one, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 255, 255, 255));
                //SDL_FillRect(Gfx.BackBuffer, &button_two, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 255, 255, 255));
                //SDL_FillRect(Gfx.BackBuffer, &button_three, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 255, 255, 255));
                //SDL_FillRect(Gfx.BackBuffer, &button_four, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 255, 255, 255));
                //SDL_FillRect(Gfx.BackBuffer, &button_five, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 255, 255, 255));
                //SDL_FillRect(Gfx.BackBuffer, &button_six, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 255, 255, 255));

                if (SDL_GetMouseState(&trigger_x, &trigger_y) & SDL_BUTTON_LMASK)
                {
                    if (trigger_x > button_one.x && trigger_x < button_one.x + button_one.w)
                    {
                        SDL_FillRect(Gfx.BackBuffer, &button_one, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 255));
                        gamestate.GameState.pop();
                        gamestate.GameState.push(MENU_MAIN_STATE);
                    }
                    if (trigger_x > button_two.x && trigger_x < button_two.x + button_two.w)
                    {
                        SDL_FillRect(Gfx.BackBuffer, &button_two, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 255));
                        //gamestate.GameState.pop();
                        //gamestate.GameState.push(GAME_RUNNING_STATE);
                    }
                    if (trigger_x > button_three.x && trigger_x < button_three.x + button_three.w)
                    {
                        SDL_FillRect(Gfx.BackBuffer, &button_three, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 255));
                        //gamestate.GameState.pop();
                        //gamestate.GameState.push(GAME_RUNNING_STATE);
                    }
                    if (trigger_x > button_four.x && trigger_x < button_four.x + button_four.w)
                    {
                        SDL_FillRect(Gfx.BackBuffer, &button_four, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 255));
                        //gamestate.GameState.pop();
                        //gamestate.GameState.push(GAME_RUNNING_STATE);
                    }
                    if (trigger_x > button_five.x && trigger_x < button_five.x + button_five.w)
                    {
                        SDL_FillRect(Gfx.BackBuffer, &button_five, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 255));
                        //gamestate.GameState.pop();
                        //gamestate.GameState.push(GAME_RUNNING_STATE);
                    }
                    if (trigger_x > button_six.x && trigger_x < button_six.x + button_six.w)
                    {
                        SDL_FillRect(Gfx.BackBuffer, &button_six, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 255));
                        //gamestate.GameState.pop();
                        //gamestate.GameState.push(GAME_RUNNING_STATE);
                    }

                }

                SDL_Surface * srfshiptext;
                srfshiptext = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(ship).c_str(), Gfx.WhiteRGB);
                //Gfx.apply_surface(tile_clicked_x, tile_clicked_y, srfspecialtext, Gfx.BackBuffer);
                Gfx.apply_surface(Gfx.BackBuffer->w - 150, 350, srfshiptext, Gfx.BackBuffer);
                srfshiptext = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(ind).c_str(), Gfx.WhiteRGB);
                //Gfx.apply_surface(tile_clicked_x, tile_clicked_y, srfspecialtext, Gfx.BackBuffer);
                Gfx.apply_surface(Gfx.BackBuffer->w - 150, 385, srfshiptext, Gfx.BackBuffer);
                srfshiptext = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(def).c_str(), Gfx.WhiteRGB);
                //Gfx.apply_surface(tile_clicked_x, tile_clicked_y, srfspecialtext, Gfx.BackBuffer);
                Gfx.apply_surface(Gfx.BackBuffer->w - 150, 425, srfshiptext, Gfx.BackBuffer);
                srfshiptext = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(eco).c_str(), Gfx.WhiteRGB);
                //Gfx.apply_surface(tile_clicked_x, tile_clicked_y, srfspecialtext, Gfx.BackBuffer);
                Gfx.apply_surface(Gfx.BackBuffer->w - 150, 465, srfshiptext, Gfx.BackBuffer);
                srfshiptext = TTF_RenderText_Solid(Gfx.DefaultFont, std::to_string(tech).c_str(), Gfx.WhiteRGB);
                //Gfx.apply_surface(tile_clicked_x, tile_clicked_y, srfspecialtext, Gfx.BackBuffer);
                Gfx.apply_surface(Gfx.BackBuffer->w - 150, 505, srfshiptext, Gfx.BackBuffer);

                SDL_BlitSurface(Gfx.GetSurface(gamestate.m_srfspaceship), &Gfx.GetSurface(gamestate.m_srfspaceship)->clip_rect, Gfx.BackBuffer, &fleet_pos_coords);
				Gfx.FLIP();
			} break;
		case GAME_BOSS_STATE:
			{
				//Gfx.DrawScore(300,0,UpdateScore());
			} break;
		case GAME_OUTRO_STATE:
			{
				gamestate.PlayOutro();
			} break;
		case GAME_PLAYER_DIED_STATE:
			{
				Spaceship._Lives--;
				if(Spaceship._Lives>0)
				{
					gamestate.Reset();
					gamestate.GameState.pop();
					gamestate.GameState.push(GAME_RUNNING_STATE);
				}
				else
				{
					gamestate.RestartGame();
					gamestate.GameState.pop();
					gamestate.GameState.push(MENU_MAIN_STATE);
				}
			} break;
	}
	if( _SCORE > 10000 ) 
		_SCORE = 0;
}

// ----------------------------------------------------------------------------
// PlayOutro() - Plays the whole outro sequence
// ----------------------------------------------------------------------------
void Gamestate::PlayOutro()
{
	SDL_BlitSurface( Gfx.GetSurface( gamestate.m_srfOutro ),
					&ScreenSize, Gfx.BackBuffer, &ScreenSize );
	Gfx.FLIP();

	SDL_Event input;

	while( gamestate.GameState.top() == GAME_OUTRO_STATE )
	{
		SDL_PollEvent( &input );
		if( input.type == SDL_KEYDOWN )
		{
  			switch( input.key.keysym.sym )
			{
			case SDLK_SPACE:
				gamestate.GameState.push(MENU_MAIN_STATE);
				break;
			}
		}
	}
	return;
}

// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::MainScreen(int iElapsedTime)
{
    SDL_GetMouseState(&Engine.MouseXCoordinates, &Engine.MouseYCoordinates);

    static int fleet_pos_x = Engine.MouseXCoordinates;
    static int fleet_pos_y = Engine.MouseYCoordinates;

    static int tile_fleet_x = Align(fleet_pos_x, 64);
    static int tile_fleet_y = Align(fleet_pos_y, 64);

    static int old_tile_clicked_x;
    static int old_tile_clicked_y;

    static int tile_clicked_x;
    static int tile_clicked_y;
    
    static SDL_Rect fleet_pos_coords;


    SDL_Rect tmp = SDL_GetVideoSurface()->clip_rect;
    SDL_Rect oldtmp = SDL_GetVideoSurface()->clip_rect;

    old_tile_clicked_x = tile_clicked_x;
    old_tile_clicked_y = tile_clicked_y;

    tile_clicked_x = Align(Engine.MouseXCoordinates, 64);
    tile_clicked_y = Align(Engine.MouseYCoordinates, 64);

    oldtmp.x = tile_clicked_x;
    oldtmp.y = tile_clicked_y;
    oldtmp.w = 64;
    oldtmp.h = 80;

    tmp.x = old_tile_clicked_x;
    tmp.y = old_tile_clicked_y;
    tmp.w = 64;
    tmp.h = 64;

    if (SDL_GetMouseState(&fleet_pos_x, &fleet_pos_y) & SDL_BUTTON_LMASK)
    {
        tile_fleet_x = Align(fleet_pos_x, 64);
        tile_fleet_y = Align(fleet_pos_y, 64);
        fleet_pos_coords.x = tile_fleet_x;
        fleet_pos_coords.y = tile_fleet_y;
        fleet_pos_coords.w = 64;
        fleet_pos_coords.h = 64;
        SDL_FillRect(Gfx.BackBuffer, &oldtmp, SDL_MapRGBA(Gfx.BackBuffer->format, 0, 0, 0, 0));
    }

    //int tile_clicked_x = (200 + MouseXCoordinates) / (Gfx.BackBuffer->clip_rect.w / 14);
    //int tile_clicked_y = (500 + MouseYCoordinates) / (Gfx.BackBuffer->clip_rect.h / 10);

    //SDL_FillRect(Gfx.BackBuffer, &tmp, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 0, 0));
    //drawLine(Gfx.BackBuffer, MouseXCoordinates, MouseYCoordinates, tile_clicked_x, tile_clicked_y);
    //putPixel(Gfx.BackBuffer, tile_clicked_x, tile_clicked_y, 255, 0, 0);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfhuman), &Gfx.GetSurface(m_srfhuman)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 288;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfmrrshan), &Gfx.GetSurface(m_srfmrrshan)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 288;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfsilicoid), &Gfx.GetSurface(m_srfsilicoid)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 288;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfsakkra), &Gfx.GetSurface(m_srfsakkra)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 288;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfpsilon), &Gfx.GetSurface(m_srfpsilon)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x = 0;
    //tmp.y += 337;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfalkari), &Gfx.GetSurface(m_srfalkari)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 288;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfklackon), &Gfx.GetSurface(m_srfklackon)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 288;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfbulrathi), &Gfx.GetSurface(m_srfbulrathi)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 288;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfmeklar), &Gfx.GetSurface(m_srfmeklar)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 288;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfdarlok), &Gfx.GetSurface(m_srfdarlok)->clip_rect, Gfx.BackBuffer, &tmp);


    //tmp = SDL_GetVideoSurface()->clip_rect;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfblue_banner), &Gfx.GetSurface(m_srfblue_banner)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 384;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfgreen_banner), &Gfx.GetSurface(m_srfgreen_banner)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 384;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfpurple_banner), &Gfx.GetSurface(m_srfpurple_banner)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x = 0;
    //tmp.y += 216;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfred_banner), &Gfx.GetSurface(m_srfred_banner)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 384;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfwhite_banner), &Gfx.GetSurface(m_srfwhite_banner)->clip_rect, Gfx.BackBuffer, &tmp);
    //tmp.x += 384;
    //SDL_BlitSurface(Gfx.GetSurface(m_srfyellow_banner), &Gfx.GetSurface(m_srfyellow_banner)->clip_rect, Gfx.BackBuffer, &tmp);

    SDL_BlitSurface(Gfx.GetSurface(m_srfspaceship), &Gfx.GetSurface(m_srfspaceship)->clip_rect, Gfx.BackBuffer, &fleet_pos_coords);

    SDL_BlitSurface(Gfx.GetSurface(m_srfmain_menu), &Gfx.GetSurface(m_srfmain_menu)->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
	//SDL_BlitSurface( &Gfx.m_SurfaceCollection["Graphics/Backdrops/main_menu.png"], &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );
    //SDL_BlitSurface(&Gfx.m_SurfaceCollection["Graphics/Backdrops/srfStart.png"], &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);
    //SDL_BlitSurface(Gfx.GetSurface(m_srfsmallmap), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);

    stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "MainScreen @ ";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	SDL_FreeSurface(srfElapsedTime);

    // 30 x 16
    //StarMap *Map = new StarMap(1920 / 64, 1080 / 64);
    //Map->Dump();

    SDL_Rect bytton;
    bytton.h = 100;
    bytton.w = 500;
    bytton.x = 700;
    bytton.y = 505;
    //SDL_FillRect(Gfx.BackBuffer, &bytton, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 128));

    bytton.h = 100;
    bytton.w = 500;
    bytton.x = 700;
    bytton.y = 615;
    //SDL_FillRect(Gfx.BackBuffer, &bytton, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 0));

    bytton.h = 100;
    bytton.w = 500;
    bytton.x = 700;
    bytton.y = 750;
    //SDL_FillRect(Gfx.BackBuffer, &bytton, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 0));

    bytton.h = 100;
    bytton.w = 500;
    bytton.x = 700;
    bytton.y = 860;
    //SDL_FillRect(Gfx.BackBuffer, &bytton, SDL_MapRGBA(Gfx.BackBuffer->format, 255, 0, 255, 0));
}

// ----------------------------------------------------------------------------
// LoadScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::LoadScreen(int iElapsedTime)
{
    SDL_BlitSurface(Gfx.GetSurface(LoadsScreen->surface), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect);

    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[0]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[1]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[2]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[3]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[4]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[5]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[6]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &LoadsScreen->ButtonClips[7]);

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "LoadScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	if( LoadsScreen->ButtonNewgame == true )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_RUNNING_STATE);
		LoadsScreen->ButtonNewgame = false;
	}
	SDL_FreeSurface(srfElapsedTime);
}

// ----------------------------------------------------------------------------
// SaveScreen() - Draws the save screen
// ----------------------------------------------------------------------------
void Gamestate::SaveScreen(int iElapsedTime)
{
	SDL_BlitSurface( Gfx.GetSurface( SavesScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );

    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[0]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[1]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[2]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[3]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[4]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[5]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[6]);
    SDL_BlitSurface(Gfx.GetSurface(m_srfButtonActive), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SavesScreen->ButtonClips[7]);

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "SaveScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	if( SavesScreen->ButtonNewgame == true )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_RUNNING_STATE);
		SavesScreen->ButtonNewgame = false;
	}
    SDL_FreeSurface(srfElapsedTime);
}

// ----------------------------------------------------------------------------
// CreditScreen() - Draws the credit screen
// ----------------------------------------------------------------------------
void Gamestate::CreditScreen(int iElapsedTime)
{
	SDL_BlitSurface( Gfx.GetSurface( CreditsScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );
	
	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "CreditsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	SDL_FreeSurface(srfElapsedTime);
}
// ----------------------------------------------------------------------------
// OptionScreen() - Draws the option screen
// ----------------------------------------------------------------------------
void Gamestate::OptionScreen(int iElapsedTime)
{
	SDL_FillRect(Gfx.BackBuffer, NULL, SDL_MapRGBA(Gfx.BackBuffer->format, 0,0,0,0));


	SDL_BlitSurface( Gfx.GetSurface( OptionsScreen->surface ),&SDL_GetVideoSurface()->clip_rect,Gfx.BackBuffer,&SDL_GetVideoSurface()->clip_rect);
	
	if( DIFFICULTY == 0 )
	{
			SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 0 ]);
	}
	else
	if( DIFFICULTY == 1 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 1 ]);
	}
	else
	if( DIFFICULTY == 2 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 2 ]);
	}
	if( SOUND == 3 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 3 ]);
	}
	else
	if( SOUND == 4 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 4 ]);
	}
	if( MUSIC == 5 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 5 ]);
		//Audio.PlayMusic(rand()%3);
	}
	else
	if( MUSIC == 6 )
	{
		SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 6 ]);
		//Audio.PauseMusic();
	}

	SDL_BlitSurface( Gfx.GetSurface( m_srfButtonActive ),  &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &ButtonClips[ 7 ]);

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "OptionsScreen @";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	SDL_FreeSurface(srfElapsedTime);
}

// ----------------------------------------------------------------------------
// MainScreen() - Draws the mainscreen, checks conditions. MenuScreen
// ----------------------------------------------------------------------------
void Gamestate::GameoverScreen(int iElapsedTime)
{
	SDL_BlitSurface( Gfx.GetSurface( MainMenuScreen->surface ), &SDL_GetVideoSurface()->clip_rect, Gfx.BackBuffer, &SDL_GetVideoSurface()->clip_rect );

	stringstream ss;
	ss << (float)iElapsedTime / 1000000;
	string str = "Gameover @ ";
	str.append(ss.str());
	SDL_Surface * srfElapsedTime;
	srfElapsedTime = TTF_RenderText_Solid( Gfx.DefaultFont, str.c_str(), Gfx.WhiteRGB );
	Gfx.apply_surface( 0, 0, srfElapsedTime, Gfx.BackBuffer );
	SDL_FreeSurface(srfElapsedTime);
	return;
}


// ----------------------------------------------------------------------------
// EnterName() - checks for input demon name
// ----------------------------------------------------------------------------
void Gamestate::EnterName()
{
	SDL_BlitSurface( Gfx.GetSurface( MainMenuScreen->surface ), &ScreenSize, Gfx.BackBuffer, &ScreenSize );
	SDL_Surface * srfEnter = 0;
	//srfEnter = TTF_RenderText_Solid( Gfx.DefaultFont, gamestate.demonName.c_str(), Gfx.BlackRGB );
	Gfx.apply_surface( 200, 400, srfEnter, Gfx.BackBuffer );

	if( gamestate.name->handle_input(  ) == false )
	{
		gamestate.GameState.pop();
		gamestate.GameState.push(GAME_STORY_STATE);
	}
}

void Gamestate::RestartGame()
{
	Spaceship.Reset();
	AnimalController.Destroy();
	CubeController.CubeArrayRef.clear();
	TriangleController.TriangleArrayRef.clear();
	_SCORE = 0;
	Spaceship._Lives = 3;
}
void Gamestate::Reset()
{
	Spaceship.Reset();
	AnimalController.Destroy();
	CubeController.CubeArrayRef.clear();
	TriangleController.TriangleArrayRef.clear();
	_SCORE = 0;
}
void Gamestate::Cleanup()
{
	if( MainMenuScreen != NULL )
	{
		delete MainMenuScreen;
	}
	if( CreditsScreen != NULL )
	{
		delete CreditsScreen;
	}
	//for( int i = 0; i < ParallaxBG->getLayerCount(); i++ )
	//{
	//	SDL_FreeSurface( m_surfaceList[ i ] );
	//}
	if( gamestate.name != NULL )
	{
		delete name;
	}
	//if( gamestate.ParallaxBG != NULL )
	//{
	//	delete ParallaxBG;
	//}
	if( gamestate.GameOverScreen != NULL )
	{
		delete GameOverScreen;
	}
	if( gamestate.OptionsScreen != NULL )
	{
		delete OptionsScreen;
	}
	if( gamestate.LoadsScreen != NULL )
	{
		delete LoadsScreen;
	}
	if( gamestate.SavesScreen != NULL )
	{
		delete SavesScreen;
	}
}

void Gamestate::ResetRest()
{
	if( MainMenuScreen != NULL )
	{
		delete MainMenuScreen;
	}
	if( CreditsScreen != NULL )
	{
		delete CreditsScreen;
	}
}

void Game::Cleanup()
{
	TTF_Quit();
	SDL_Quit();
}

// inits sdl, font and videomode
bool Game::Init(SDL_Surface * &screen)
{
	screen = 0;
    Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	//set up the screen
    screen = SDL_SetVideoMode(0, 0, 0, flags ^ SDL_FULLSCREEN);
    //screen = SDL_SetVideoMode(ScreenSize.w, ScreenSize.h, 32, flags);
    Gfx.m_SurfaceCollection["Screen"] = *SDL_SetVideoMode(ScreenSize.w, ScreenSize.h, 32, flags ^ SDL_FULLSCREEN);
    
    //Uint32 flags = SDL_SWSURFACE; /* Start with whatever flags you prefer */
    //flags = screen->flags; /* Save the current flags in case toggling fails */
    //screen = SDL_SetVideoMode(0, 0, 0, screen->flags ^ SDL_FULLSCREEN); /*Toggles FullScreen Mode */
    //if (screen == NULL) screen = SDL_SetVideoMode(0, 0, 0, flags); /* If toggle FullScreen failed, then switch back */
    //if (screen == NULL) exit(1); /* If you can't switch back for some reason, then epic fail */

	SDL_Rect** modes;
	int i;
   
    /* Get available fullscreen/hardware modes */
    modes = SDL_ListModes(NULL, SDL_FULLSCREEN | SDL_HWSURFACE);
    
    /* Check if there are any modes available */
    if (modes == (SDL_Rect**)0) 
	{
        printf("No modes available!\n");
       exit(-1);
	}
   
   /* Check if our resolution is restricted */
   if (modes == (SDL_Rect**)-1) 
   {
       printf("All resolutions available.\n");
   }
   else
   {
       /* Print valid modes */
       printf("Available Modes\n");
       for (i=0; modes[i]; ++i)
         printf("  %d x %d\n", modes[i]->w, modes[i]->h);
   }

	if( screen == NULL )
	{
		return false;
	}

	//set window caption
	SDL_WM_SetCaption( " S-TYPE ", NULL);

	/* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    Uint32 rmask, gmask, bmask, amask;

	/* SDL interprets each pixel as a 32-bit number, so our masks must depend
	   on the endianness (byte order) of the machine */

	rmask = 0x00000000;
	gmask = 0x00000000;
	bmask = 0x00000000;
	amask = 0x00000000;

	Gfx.BackBuffer = SDL_CreateRGBSurface( SDL_HWSURFACE, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h, SDL_GetVideoSurface()->format->BitsPerPixel,
								   rmask, gmask, bmask, amask);
	
	if( Gfx.BackBuffer == NULL )
	{
		return false;																							
	}

	return true;
}

void Gamestate::CreateAll()
{
	AnimalController.CreateAnimals(_SCORE );
	PowerupController.CreatePowerup(_SCORE );
	CubeController.CreateCubes( _SCORE );
	TriangleController.CreateTriangles( _SCORE );
	EnemyController.Create_Enemies();
	ObjectController.CreateObjects();
}