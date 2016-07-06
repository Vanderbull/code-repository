#pragma once
#include "Enemies.h"
#include "Game.h"
#include <list>
#include "Timers.h"
#include "Objects.h"
#include "Collision.h"
#include "ControlGfx.h"

// 1. this should go into every .cpp , after all header inclusions
#ifdef _WIN32
#ifdef _DEBUG
   #include <crtdbg.h>
   #undef THIS_FILE
   static char THIS_FILE[] = __FILE__;
   #define new       new( _NORMAL_BLOCK, __FILE__, __LINE__)
   #define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

Control_Enemies EnemyController;

CEnemy::CEnemy()
{
	CEnemy::Speed = 300;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Set_Clips( int WhichTypeOfEnemy )
{
}

// sets frame for skeleton
void CEnemy::SetFrame()
{
	PrevFrame = Frame;

	if( Attack )
	{
		Walk = false;
		if( LeftOfPlayer )
		{
			if( AttackFrameRight == 45 )
			{
				AttackFrameRight = 37;
				Walk = true;
				Attack = false;
			}
			else
			{
				AttackFrameRight++;
			}
			Frame = AttackFrameRight;
		}
		else if( RightOfPlayer )
		{
			if( AttackFrameLeft == 18 )
			{
				AttackFrameLeft = 9;
				Walk = true;
				Attack = false;
			}
			else
			{
				AttackFrameLeft++;
			}
			Frame = AttackFrameLeft;
		}
	}
	else if( Die )
	{
		Walk = false;
		Attack = false;

		if( LeftOfPlayer )
		{
			if( DieFrameRight == 54 )
			{
				DieFrameRight = 54;

			}
			else
			{
				DieFrameRight++;
			}

			Frame = DieFrameRight;
		}
		else if( RightOfPlayer )
		{
			if( DieFrameLeft == 27 ) 
			{
				DieFrameLeft = 27;

			}
			else
			{
				DieFrameLeft++;
			}

			Frame = DieFrameLeft;
		}
	}
	else if( Walk )
	{
		if( LeftOfPlayer )
		{
			if( WalkFrameRight == 39 )
			{
				WalkFrameRight = 30;
			}
			else
			{
				WalkFrameRight++;
			}

			Frame = WalkFrameRight;
		}
		else if( RightOfPlayer )
		{
			if( WalkFrameLeft == 8 )
			{
				WalkFrameLeft = 0;
			}
			else
			{
				WalkFrameLeft++;
			}
			
			Frame = WalkFrameLeft;
		}		
	}
}

void Control_Enemies::Update()
{
	Collide = false;
	list< CEnemy* >::iterator i = Enemies.begin();

	i = Enemies.begin();
	while(i != Enemies.end() )
	{
		(*i)->Update();
		if( (*i)->_Position.x <= 200 )
		{
			i = Enemies.erase(i);
		}
		else
		{
			++i;
		}
	}
}
// draws all enemies , checks collision and updates frame
void Control_Enemies::Draw_Enemies()
{
	if( Enemies.size() != 0 )
	{
		list< CEnemy* >::iterator i = Enemies.begin();
		for( ; i != Enemies.end(); ++i )
		{

				// Check to see if collision occurs and if demon is in any kind of attack state
				//CEnemy * enemy = (*i);

				// checks collision with demon using circlecollision
				//Collide = CollisionController.CheckCollisionWithdemon( enemy, 1 );
            Collide = CollisionController.CheckCollision((*i), 1, &Spaceship);

				//Attack = demon.IsInStateAttack();
				
            if (Collide == true && Spaceship.IsAttacking()) // && Attack == true
				{
				}
				else if( Collide == true )
				{
					if( (*i)->Surface == 8 )
					{
						(*i)->Attack = true;
					}
					else
					{
					}		
				}
				if( (*i)->Frame == 18 || (*i)->Frame == 46 )
				{
					(*i)->Attack = false;
					(*i)->Walk = true;
				}
				
				static int FrameCounter = 0;
				if( FrameCounter > 13)
					FrameCounter = 0;
		}

	}
}

// Memory leak here because of missing delete, code not used though so its not critical
CEnemy * Control_Enemies::CreateEnemy( Sint16 xPos, Sint16 yPos, int surface )
{
	CEnemy * temp = new CEnemy;
	temp->Surface = surface;
	temp->AnimCounter = 1;
	temp->PrevFrame = 0;
	
	temp->_Position.x = xPos;
	temp->_Position.y = yPos;

	temp->Height = 96;
	temp->Width = 96;
	temp->Walk = true;
	temp->Attack = false;
	temp->Die = false;
	temp->LeftOfPlayer = false; 
	temp->RightOfPlayer = false;

	temp->AttackFrameLeft = 9;
	temp->AttackFrameRight = 37;
	temp->DieFrameLeft = 18;
	temp->DieFrameRight = 46;
	temp->WalkFrameLeft = 0;
	temp->WalkFrameRight = 28;

	int Height, Width;
	Height = temp->Height / 2;
	Width = temp->Width / 2;

	return temp;
}

void Control_Enemies::Create_Enemies()
{
}

Control_Enemies::Control_Enemies()
{
	Attack = false;
	Collide = false;
	CollideFire = false;
	SpawnTimer = 0;
}

