#ifndef GLOBAL_H // header guards 
#define GLOBAL_H   // extern tells the compiler this variable is declared elsewhere 

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
//#include <windows.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "../ControlGfx.h"

#define PORT    "32001" /* Port to listen on */
#define BACKLOG 10      /* Passed to listen() */


using namespace std;
extern int g_nValue;
extern SDL_Rect ScreenSize;
#define MAXSAMPLES 100
const int FRAMES_PER_SECOND = 20;
extern int DIFFICULTY;
extern int SOUND;
extern int MUSIC;
extern string HIGHSCORE;
extern SDL_Rect ButtonClips[ 10 ];
extern int CURRENT_HIGHSCORE;
extern int _SCORE;
extern int FIRED;
extern float SpaceScrollingSpeed;
extern int LevelSize;
extern int LevelProgress;
extern Sint16 SpriteWidth;
extern Uint16 SpriteHeight;
extern int SMALL_GALAXY;
extern int MEDIUM_GALAXY;
extern int LARGE_GALAXY;
extern int HUGE_GALAXY;
extern int PLANET[24];
extern int stardate;
extern unsigned int ship;
extern unsigned int ind;
extern unsigned int def;
extern unsigned int eco;
extern unsigned int tech;
extern int BC;
extern int income_trade;
extern int income_planets;
extern int spending_ships;
extern int spending_spying;
extern int spending_bases;
extern int spending_security;

extern int NORMAL_RESOURCE_LEVEL;
extern int ULTRA_POOR_RESOURCE_LEVEL;
extern int POOR_RESOURCE_LEVEL;
extern int RICH_RESOURCE_LEVEL;
extern int ULTRA_RICH_RESOURCE_LEVEL;
extern int ARTIFACTS_RESOURCE_LEVEL;
extern int ORION_RESOURCE_LEVEL;

extern int alkari_tech_development[6];
extern int bulrathi_tech_development[6];
extern int darlok_tech_development[6];
extern int human_tech_development[6];
extern int klackon_tech_development[6];
extern int meklar_tech_development[6];
extern int mrrshan_tech_development[6];
extern int psilon_tech_development[6];
extern int sakkra_tech_development[6];
extern int silicoid_tech_development[6];

extern int galaxy_size;
extern int difficulty;
extern int opponents;
extern int race;
extern int banner;
enum{ BOSS_IDLE, BOSS_ATTACK, BOSS_DIE };
enum{ HEAD_GO, HEAD_DOWN, HEAD_CRASH };
enum{ BUTTON_NEW_GAME, BUTTON_OPTIONS, BUTTON_QUIT };
enum{ MAIN_MENU, OPTIONS_MENU, CREDITS_MENU };
enum{ POOR, STANDARD, GOOD, EXCELLENT };
enum{ COMPUTERS, CONSTRUCTION, FORCEFIELD, PLANETOLOGY, PROPULSION, WEAPON };

struct tech_development
{
    int alkari_tech_development[6];
    int bulrathi_tech_development[6];
    int darlok_tech_development[6];
    int human_tech_development[6];
    int klackon_tech_development[6];
    int meklar_tech_development[6];
    int mrrshan_tech_development[6];
    int psilon_tech_development[6];
    int sakkra_tech_development[6];
    int silicoid_tech_development[6];

    float poor_multiplier = 1.25f;
    float good_multiplier = 0.80f;
    float excellent_multiplier = 0.60f;

    void init()
    {
        alkari_tech_development[COMPUTERS] = POOR;
        alkari_tech_development[CONSTRUCTION] = POOR;
        alkari_tech_development[FORCEFIELD] = POOR;
        alkari_tech_development[PLANETOLOGY] = POOR;
        alkari_tech_development[PROPULSION] = POOR;
        alkari_tech_development[WEAPON] = POOR;

        bulrathi_tech_development[COMPUTERS] = POOR;
        bulrathi_tech_development[CONSTRUCTION] = POOR;
        bulrathi_tech_development[FORCEFIELD] = POOR;
        bulrathi_tech_development[PLANETOLOGY] = POOR;
        bulrathi_tech_development[PROPULSION] = POOR;
        bulrathi_tech_development[WEAPON] = POOR;

        darlok_tech_development[COMPUTERS] = POOR;
        darlok_tech_development[CONSTRUCTION] = POOR;
        darlok_tech_development[FORCEFIELD] = POOR;
        darlok_tech_development[PLANETOLOGY] = POOR;
        darlok_tech_development[PROPULSION] = POOR;
        darlok_tech_development[WEAPON] = POOR;

        human_tech_development[COMPUTERS] = POOR;
        human_tech_development[CONSTRUCTION] = POOR;
        human_tech_development[FORCEFIELD] = POOR;
        human_tech_development[PLANETOLOGY] = POOR;
        human_tech_development[PROPULSION] = POOR;
        human_tech_development[WEAPON] = POOR;

        klackon_tech_development[COMPUTERS] = POOR;
        klackon_tech_development[CONSTRUCTION] = POOR;
        klackon_tech_development[FORCEFIELD] = POOR;
        klackon_tech_development[PLANETOLOGY] = POOR;
        klackon_tech_development[PROPULSION] = POOR;
        klackon_tech_development[WEAPON] = POOR;

        meklar_tech_development[COMPUTERS] = POOR;
        meklar_tech_development[CONSTRUCTION] = POOR;
        meklar_tech_development[FORCEFIELD] = POOR;
        meklar_tech_development[PLANETOLOGY] = POOR;
        meklar_tech_development[PROPULSION] = POOR;
        meklar_tech_development[WEAPON] = POOR;

        mrrshan_tech_development[COMPUTERS] = POOR;
        mrrshan_tech_development[CONSTRUCTION] = POOR;
        mrrshan_tech_development[FORCEFIELD] = POOR;
        mrrshan_tech_development[PLANETOLOGY] = POOR;
        mrrshan_tech_development[PROPULSION] = POOR;
        mrrshan_tech_development[WEAPON] = POOR;

        psilon_tech_development[COMPUTERS] = POOR;
        psilon_tech_development[CONSTRUCTION] = POOR;
        psilon_tech_development[FORCEFIELD] = POOR;
        psilon_tech_development[PLANETOLOGY] = POOR;
        psilon_tech_development[PROPULSION] = POOR;
        psilon_tech_development[WEAPON] = POOR;

        sakkra_tech_development[COMPUTERS] = POOR;
        sakkra_tech_development[CONSTRUCTION] = POOR;
        sakkra_tech_development[FORCEFIELD] = POOR;
        sakkra_tech_development[PLANETOLOGY] = POOR;
        sakkra_tech_development[PROPULSION] = POOR;
        sakkra_tech_development[WEAPON] = POOR;

        silicoid_tech_development[COMPUTERS] = POOR;
        silicoid_tech_development[CONSTRUCTION] = POOR;
        silicoid_tech_development[FORCEFIELD] = POOR;
        silicoid_tech_development[PLANETOLOGY] = POOR;
        silicoid_tech_development[PROPULSION] = POOR;
        silicoid_tech_development[WEAPON] = POOR;
    };
};

struct weapon_manager
{
    string line;
    string name[50];
    int level[50];
    int min_damage[50];
    int max_damage[50];
    int cost[50];
    int size[50];
    int power[50];
    int bombs[50];
    int bonus[50];
    int speed[50];
    int range[50];

    void init()
    {
        cout << "Loading weapons" << "..." << endl;
        std::ifstream weaponfile("./src/res/weapons.txt", std::ios::in);
        if (weaponfile.is_open())
        {
            while (getline(weaponfile, line))
            {
                static int index = 0;
               static int counter = 0;
                cout << line << endl;
                // Skip comments
                if (line[0] == '#')
                {
                    continue;
                }
                if (counter == 0)
                    name[index] = line;
                if (counter == 1)
                    level[index] = atoi(line.c_str());
                if (counter == 2)
                    min_damage[index] = atoi(line.c_str());
                if (counter == 3)
                    max_damage[index] = atoi(line.c_str());
                if (counter == 4)
                    cost[index] = atoi(line.c_str());
                if (counter == 5)
                    size[index] = atoi(line.c_str());
                if (counter == 6)
                    power[index] = atoi(line.c_str());
                if (counter == 7)
                    bombs[index] = atoi(line.c_str());
                if (counter == 8)
                    bonus[index] = atoi(line.c_str());
                if (counter == 9)
                    speed[index] = atoi(line.c_str());
                if (counter == 10)
                    range[index] = atoi(line.c_str());

                counter++;
                
                if (counter > 10)
                {
                    index++;
                    counter = 0;
                }
            }
        }
        else
        {
            exit(1);
        }
        weaponfile.clear();
        weaponfile.close();
    }; 
};
extern weapon_manager weapon_data;
struct tech_manger
{
    //areas
    int computers[99];
    int construction[99];
    int force_fields[99];
    int planetology[99];
    int propulsion[99];
    int weapons[99];

};

struct fleet_manager
{
    int fleets;
};

struct ship_design
{
    string name;
    int ship_size;
    int battle_computers;
    int shields;
    int ecm_generators;
    int armor;
    int engines;
    int maneuverability;
    int weapon_types[4];
    int special_devices[3];
    int active;

    void init()
    {
        name = "default";
        ship_size = 1;
        battle_computers = 1;
        shields = 1;
        ecm_generators = 0;
        armor = 0;
        engines = 0;
        maneuverability = 0;
        weapon_types[0] = 0;
        weapon_types[1] = 0;
        weapon_types[2] = 0;
        weapon_types[3] = 0;
        special_devices[0] = 0;
        special_devices[1] = 0;
        special_devices[2] = 0;
        active = 0;
    };
};
extern ship_design current_ship_design[6];

void SetGameOptionButtons();
void objRectangle(SDL_Rect &Rect, int XPos, int YPos, int Width, int Height);
int MouseInBox(SDL_Rect &Rect);
int RenderPixelMap(ControlGfx Gfx);

#define arrlen(x) (sizeof(x)/sizeof((x)[0]))
struct world_tile
{
    int q_value;
    int t_value;
};

extern world_tile world_array[1166400];
extern world_tile world_array_two_dimensional[1080][1080];

inline double findnoise2(double x, double y);
inline double interpolate(double a, double b, double x);
//  It returns a value between -1 and 1. To convert this to a 0-256 RGB value, we simple multiply it by 128,then add 128 to it
double noise(double x, double y);
//Use like this:
//SDL_Rect myRect;
//Rectangle(myRect, 5, 5, 50, 20);

// Used in Game.h file
typedef enum
{
	GAME_RESUME_STATE,
	GAME_NEW_STATE,
	GAME_LOAD_STATE,
	GAME_SAVE_STATE,
	GAME_QUIT_STATE,
	GAME_CREDITS_STATE,
	GAME_OPTIONS_STATE,
	MENU_MAIN_STATE,
	MENU_SUB_STATE,
	GAME_RUNNING_STATE,
	GAME_INTRO_STATE,
	GAME_OUTRO_STATE,
	GAME_PAUSED_STATE,
	GAME_STORY_STATE,
	GAME_LOADING_STATE,
	GAME_SAVING_STATE,
	GAME_BOSS_STATE,
	GAME_PLAYER_DIED_STATE,
    GAME_GAME_STATE,
    GAME_DESIGN_STATE,
    GAME_FLEET_STATE,
    GAME_MAP_STATE,
    GAME_RACES_STATE,
    GAME_PLANETS_STATE,
} InGameStates;



const int MAX_SURFACE = 128;
const int ANIMPACE = 150;
const int ANIMPACESLOWER = 300;
const int ANIMPACEENEMY = 50;
const int ANIMPACEBOSSHEAD = 5;

const int SPACESHIP_HEIGHT = 100;
const int SPACESHIP_WIDTH = 130;
const int SPACESHIP_WIDTH_REAL = 25;
const int SPACESHIP_HEIGHT_REAL = 25;

const int GROUND_Y = 500;
const int GROUND_X = 400;
const int STARTSCROLLING = 400;
const int BOSS_ATTACK_START = 150;
extern std::vector< int > PopupScore;



// Helper functions

double CalcAverageTick(int newtick);
extern inline float Align(float value, float size);
void SwapValue(int& value_a, int& value_b);
void PutPixel(SDL_Surface* destination_surface, int value_x, int value_y, int red, int green, int blue);

struct travel_routes
{
    int from_x, from_y, from_z;
    int to_x, to_y, to_z;

    void init()
    {
        from_x = 0;
        from_y = 0;
        from_z = 0;
        to_x = 0;
        to_y = 0;
        to_z = 0;
    };

    void render()
    {

    }
};

unsigned int permuteQPR(unsigned int x);

#endif