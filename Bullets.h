#pragma once
#include <list>
#include <vector>
#include <stack>
#include <SDL.h>
#include "Objects.h"
#include "Animals.h"

#define BULLET_MAX_FRAMES 15

/// <summary>Used to create a Bullet entity</summary>
class Bullet : public Object
{

public:
	Bullet();
	
	SDL_Rect UpdateCollisionBox(SDL_Rect Box);
	void Update();
	void Draw();
	int GetSurfaceID();
	void onCollision(){ DeActivate(); };
	bool isActive(){ return Active; };
	void DeActivate(){ Active = false; };
	void Activate(){ Active = true; };
	void onDestruction(){ DeActivate(); };
	
	SDL_Rect GetLocAndSize();
	void SetCollisionBox(Sint16 x, Sint16 y, Sint16 h, Sint16 w)
	{
		CollisionBox.x = x;
		CollisionBox.y = y;
		CollisionBox.h = h;
		CollisionBox.w = w;
	}
	SDL_Rect GetCollisionBox(){ return CollisionBox; };
	void Spawn() {};

private:
	SDL_Rect Clips[ 16 ];
	int PrevFrame;
};

/// <summary>A class the controls the animals</summary> 
class ControlBullets
{
public:
	ControlBullets();
	~ControlBullets();
	void Draw_Bullets();
	void Create_Bullets();

	void LoadBullet( int xPos, int yPos, int iSurfaceID );
	std::vector< Bullet > GetVBulletsByReference(){ return BulletArrayRef; };

	Bullet CreateBulletByReference( int xPos, int yPos, int surface );

	std::vector< Bullet > BulletArrayRef;	
private:

};

extern ControlBullets BulletController;