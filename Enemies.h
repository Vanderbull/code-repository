#pragma once
#include<algorithm>
#include<list>
#include<ctime>
#include<SDL.h>
#include<SDL_image.h>

#include "Global\Global.h"
#include "Objects.h"
#include "Enemies\MovingThings.h"

// holds info for all the enemies

class CEnemy : public MovingThings
{
public:
	
	CEnemy();
    ~CEnemy();
	void Set_Clips( int WhichTypeOfEnemy ); // Should be replaced by objects SetClips
	void SetFrame();
	
	// New update functionality
	SDL_Rect GetPosition()
	{
		return CEnemy::_Position;
	}
	void Update()
	{
		CEnemy::_Position.w = CEnemy::Width;
		CEnemy::_Position.h = CEnemy::Height;
	}

	int PrevFrame, Frame, Radius, 
		WalkFrameLeft, WalkFrameRight, 
		AttackFrameRight, AttackFrameLeft, 
		DieFrameLeft, DieFrameRight, 
		AnimCounter;

	bool Walk, Attack, Die, LeftOfPlayer, RightOfPlayer;

	std::list<SDL_Rect> Clips;

private:
};

// controls the enemies and creates the enemies
class Control_Enemies
{
public:
	Control_Enemies();
	void Update();
	void Draw_Enemies();
	void Create_Enemies();
	std::list< CEnemy* > Enemies;
	CEnemy * CreateEnemy( Sint16 xPos, Sint16 yPos, int surface );	
private:

	int SpawnTimer;
	bool Collide;
	bool CollideFire;
	bool Attack;
};

extern Control_Enemies EnemyController;

const int MAX_NUMS = 20;

class Opponents
{
    public:
        string races[MAX_NUMS];
        int index[5];
                
        Opponents()
        {
            srand(time(NULL));
            std::string romanNumsInitialiser[MAX_NUMS] = { "Akaris", "Bulrathis", "Darloks", "Humans", "Klackons", "Mecklars", "Mrrshans", "Psilons", "Sakkras", "Silicoids" };
            std::copy(romanNumsInitialiser, romanNumsInitialiser + MAX_NUMS, races);
        };
        void Generate()
        {   
            for (int i = 1; i<10; ++i) opponent_id.push_back(i); // 1 2 3 4 5 6 7 8 9

            // using built-in random generator:
            std::random_shuffle(opponent_id.begin(), opponent_id.end());

            // remove possibility for duplicate
            cout << "Generating opponents..." << endl;
            cout << races[opponent_id.at(0)].c_str() << "– an <something> race of <something>." << endl;
            cout << races[opponent_id.at(1)].c_str() << "– an <something> race of <something>." << endl;
            cout << races[opponent_id.at(2)].c_str() << "– an <something> race of <something>." << endl;
            cout << races[opponent_id.at(3)].c_str() << "– an <something> race of <something>." << endl;
            cout << races[opponent_id.at(4)].c_str() << "– an <something> race of <something>." << endl;
        };
        ~Opponents(){};
    private:

        std::vector<int> opponent_id;
};


