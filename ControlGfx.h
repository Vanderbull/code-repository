#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include "Paralaxlayers.h"

const int MAX_SURFACES = 128;

class ControlGfx
{
public:
	ControlGfx();
	~ControlGfx(){};
	int Load_imageAlpha( std::string filename, int r, int g, int b );
	//void stretchPicToBackBuffer( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect );
	int findAvailableIndex();
	SDL_Surface* GetSurface(int index);
	void PasteScreenToAnother( SDL_Rect srcRect, SDL_Rect destRect );
	bool FLIP();
	//void stretchBlit( ParallaxLayer * layer, SDL_Rect srcRect, SDL_Rect destRect );
	void apply_surface( Sint16 x, Sint16 y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
	//void DrawParallaxLayers();
	void DrawSprite();
	void DrawObjects();
	void DrawBackgroundBlack();
	void DrawScore(unsigned int xCoord,unsigned int yCoord, int iScore);
	void SetAlpha( int _SurfaceIndex, int _Opacity );

	SDL_Color WhiteRGB,BlackRGB;

	SDL_Surface * screen;
	SDL_Surface * BackBuffer;
	SDL_Surface * srfText;

	TTF_Font * DefaultFont;

	std::map<std::string,SDL_Surface> m_SurfaceCollection;
private:
	SDL_Surface * m_surfaceList[ MAX_SURFACES ];

};

extern ControlGfx Gfx;