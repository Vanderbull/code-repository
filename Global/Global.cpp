#include "Global.h"

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

// declaration of g_nValue 
int g_nValue = 5;
int DIFFICULTY = 0;
int SOUND = 3;
int MUSIC = 5;
int CURRENT_HIGHSCORE = 0;
string HIGHSCORE = "";
SDL_Rect ScreenSize = {0,0,1920,1080};
SDL_Rect ButtonClips[ 10 ];
int _SCORE = 0;
int FIRED = 0;
float SpaceScrollingSpeed = 0.0001f;
int LevelSize = 300000;
int LevelProgress = 0;
Sint16 SpriteWidth = 64;
Uint16 SpriteHeight = 64;
std::vector< int > PopupScore;
int SMALL_GALAXY = 24;
int MEDIUM_GALAXY = 48;
int LARGE_GALAXY = 70;
int HUGE_GALAXY = 108;
int PLANET[24];
int stardate = 2300;
unsigned int ship = 0;
unsigned int def = 0;
unsigned int ind = 0;
unsigned int eco = 0;
unsigned int tech = 0;
int BC = 0;
ship_design current_ship_design[6];
weapon_manager weapon_data;
travel_routes current_travel_routes[100];

int NORMAL_RESOURCE_LEVEL = 0;
int ULTRA_POOR_RESOURCE_LEVEL = 1;
int POOR_RESOURCE_LEVEL = 2;
int RICH_RESOURCE_LEVEL = 3;
int ULTRA_RICH_RESOURCE_LEVEL = 4;
int ARTIFACTS_RESOURCE_LEVEL = 5;
int ORION_RESOURCE_LEVEL = 6;

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

int galaxy_size = SMALL_GALAXY;
int difficulty = 0;
int opponents = 0;
int race = 0;
int banner = 0;

unsigned int permuteQPR(unsigned int x)
{
    static const unsigned int prime = 4294967291;
    if (x >= prime)
        return x;  // The 5 integers out of range are mapped to themselves.
    unsigned int residue = ((unsigned long long) x * x) % prime;
    return (x <= prime / 2) ? residue : prime - residue;
};

void SetGameOptionButtons()
{
    // easy option
    ButtonClips[ 0 ].h = 33;
    ButtonClips[ 0 ].w = 101;
    ButtonClips[ 0 ].x = 284;
    ButtonClips[ 0 ].y = 128;

    //medium option
    ButtonClips[ 1 ].h = 33;
    ButtonClips[ 1 ].w = 101;
    ButtonClips[ 1 ].x = 414;
    ButtonClips[ 1 ].y = 128;

    //hard option
    ButtonClips[ 2 ].h = 33;
    ButtonClips[ 2 ].w = 101;
    ButtonClips[ 2 ].x = 554;
    ButtonClips[ 2 ].y = 128;

    // sound on
    ButtonClips[ 3 ].h = 33;
    ButtonClips[ 3 ].w = 101;
    ButtonClips[ 3 ].x = 284;
    ButtonClips[ 3 ].y = 168;

    // sound off
    ButtonClips[ 4 ].h = 33;
    ButtonClips[ 4 ].w = 101;
    ButtonClips[ 4 ].x = 414;
    ButtonClips[ 4 ].y = 168;

    // music on
    ButtonClips[ 5 ].h = 33;
    ButtonClips[ 5 ].w = 101;
    ButtonClips[ 5 ].x = 284;
    ButtonClips[ 5 ].y = 218;

    // music off
    ButtonClips[ 6 ].h = 33;
    ButtonClips[ 6 ].w = 101;
    ButtonClips[ 6 ].x = 414;
    ButtonClips[ 6 ].y = 218;

    // back to main menu
    ButtonClips[ 7 ].h = 33;
    ButtonClips[ 7 ].w = 101;
    ButtonClips[ 7 ].x = 632;
    ButtonClips[ 7 ].y = 534;
}

//return by reference
void objRectangle(SDL_Rect &Rect, int XPos, int YPos, int Width, int Height)
{
	Rect.h = Height;
	Rect.w = Width;
	Rect.x = XPos;
	Rect.y = YPos;
};

int MouseInBox(SDL_Rect &Rect)
{
	std::cout << "Hey there is a mouse in this box!" << endl;
	return 0;
}

// Helper functions

int tickindex=0;
int ticksum=0;
int ticklist[MAXSAMPLES];

/* need to zero out the ticklist array before starting */
/* average will ramp up until the buffer is full */
/* returns average ticks per frame over the MAXSAMPPLES last frames */

double CalcAverageTick(int newtick)
{
    ticksum-=ticklist[tickindex];  /* subtract value falling off */
    ticksum+=newtick;              /* add new value */
    ticklist[tickindex]=newtick;   /* save new value so it can be subtracted later */
    if(++tickindex==MAXSAMPLES)    /* inc buffer index */
        tickindex=0;

    /* return average */
    return((double)ticksum/MAXSAMPLES);
}

inline float Align(float value, float size)
{
    return std::floor(value / size) * size;
}

void SwapValue(int& value_a, int& value_b)
{
    int tmp = value_a;
    value_a = value_b;
    value_b = tmp;
}

void PutPixel(SDL_Surface* destination_surface, int value_x, int value_y, int red, int green, int blue)
{
    ((Uint32*)destination_surface->pixels)[value_y*destination_surface->pitch / 4 + value_x] = SDL_MapRGB(destination_surface->format, red, green, blue);
}
world_tile world_array[1166400];
world_tile world_array_two_dimensional[1080][1080];

int RenderPixelMap(ControlGfx Gfx )
{
    for (int x = 0; x < 1080; ++x)
    {
        for (int k = 0; k < 1080; ++k)
        {
            //q value for quality
            //t value for type

            world_array[1080 * x + k].q_value = rand() % 100 + 155;
            world_array[1080 * x + k].t_value = rand() % 255;
            world_array_two_dimensional[x][k] = world_array[1080 * x + k];
            //PutPixel(Gfx.BackBuffer, x, k, 0, 0, world_array[1080 * x + k].q_value);
            double frequency = 0.015625;//pow(2, 2);//This increases the frequency with every loop of the octave.

            double amplitude = 64;//pow(0.1, 2);//This decreases the amplitude with every loop of the octave.

            double getnoise = 0;
            getnoise += noise(x, k)*(((double)x)*frequency / 1, ((double)k) / 1*frequency)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude


            int color = (int)((getnoise*128.0) + 128.0);//Convert to 0-256 values.
            
            if (color>255)
                color = 255;
            
            if (color<0)
                color = 0;
            

            PutPixel(Gfx.BackBuffer, x, k, color, color, color);
            PutPixel(Gfx.BackBuffer, x, k, rand() % 255, rand() % 255, rand() % 255);
            
        }

    }
    //for (int x = 0; x < 1080; ++x)
    //{
    //    for (int k = 0; k < 1080; ++k)
    //    {
    //        //q value for quality
    //        //t value for type

    //        world_array[1080 * x + k].q_value = rand() % 100 + 155;
    //        world_array[1080 * x + k].t_value = rand() % 255;
    //        world_array_two_dimensional[x][k] = world_array[1080 * x + k];
    //        if (x >= 200 - rand() % 100 && x <= 800 + rand() % 100)
    //            //PutPixel(Gfx.BackBuffer, x, k, 0, world_array[1080 * x + k].q_value, 0);
    //        if (k >= 200 - rand() % 100 && k <= 800 + rand() % 100)
    //            PutPixel(Gfx.BackBuffer, x, k, 0, world_array[1080 * x + k].q_value, 0);
    //    }
    //}
    for (int islands = 0; islands < 10; ++islands)
    {
        int offset_x = rand() % 380 + 200;
        int offset_k = rand() % 380 + 178;
        for (int x = rand() % 100; x < rand() % 100 + 101; ++x)
        {
            for (int k = rand() % 100; k < rand() % 100 + 101; ++k)
            {
                //q value for quality
                //t value for type

                world_array[1080 * x + k].q_value = rand() % 100 + 155;
                world_array[1080 * x + k].t_value = rand() % 255;
                world_array_two_dimensional[x][k] = world_array[1080 * x + k];
                //if (x >= 200 - rand() % 100 && x <= 800 + rand() % 100)
                //PutPixel(Gfx.BackBuffer, x, k, 0, world_array[1080 * x + k].q_value, 0);
                //if (k >= 200 - rand() % 100 && k <= 800 + rand() % 100)
                PutPixel(Gfx.BackBuffer, x + offset_x, k + offset_k, world_array[1080 * x + k].q_value, world_array[1080 * x + k].q_value, 0);
            }
        }
    }
    
    return 1;
}

// Math noise functions

inline double findnoise2(double x, double y)
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - double(t) * 0.931322574615478515625e-9;/// 1073741824.0);

}

inline double interpolate(double x, double y, double a)

{
    double negA = 1.0 - a;
    double negASqr = negA * negA;
    double fac1 = 3.0 * (negASqr)-2.0 * (negASqr * negA);
    double aSqr = a * a;
    double fac2 = 3.0 * aSqr - 2.0 * (aSqr * a);

    return x * fac1 + y * fac2; //add the weighted factors

}

double noise(double x, double y)

{

        double floorx = (double)((int)x);//This is kinda a cheap way to floor a double integer.

        double floory = (double)((int)y);

        double s, t, u, v;//Integer declaration

        s = findnoise2(floorx, floory);

        t = findnoise2(floorx + 1, floory);

        u = findnoise2(floorx, floory + 1);//Get the surrounding pixels to calculate the transition.

        v = findnoise2(floorx + 1, floory + 1);

        double int1 = interpolate(s, t, x - floorx);//Interpolate between the values.

        double int2 = interpolate(u, v, x - floorx+rand());//Here we use x-floorx, to get 1st dimension. Don't mind the x-floorx thingie, it's part of the cosine formula.

        return interpolate(int1, int2, y - floory);//Here we use y-floory, to get the 2nd dimension.
}

SDL_Surface *Render_Clouds(int w, int h, double zoom, double p, int r, int g, int b)//w and h speak for themselves, zoom wel zoom in and out on it, I usually

{//                                        use 75. P stands for persistence, this controls the roughness of the picture, i use 1/2

        int octaves = 2;

        SDL_Surface *ret = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 24, 0, 0, 0, 0);//Create an empty image.

    for (int y = 0; y<h; y++)

    {//Loops to loop trough all the pixels

        for (int x = 0; x<w; x++)

        {

                double getnoise = 0;

            for (int a = 0; a<octaves - 1; a++)//This loops trough the octaves.

            {

                    double frequency = pow(2, a);//This increases the frequency with every loop of the octave.

                    double amplitude = pow(p, a);//This decreases the amplitude with every loop of the octave.

                    getnoise += noise(x,y)*(((double)x)*frequency / zoom, ((double)y) / zoom*frequency)*amplitude;//This uses our perlin noise functions. It calculates all our zoom and frequency and amplitude

            }//                                          It gives a decimal value, you know, between the pixels. Like 4.2 or 5.1

                int color = (int)((getnoise*128.0) + 128.0);//Convert to 0-256 values.

            if (color>255)

                color = 255;

            if (color<0)

                color = 0;

                //SetPixel(ret, x, y, (int)((r / 255.0)*(double)color), (int)((g / 255.0)*(double)color), (int)((b / 255.0)*(double)color));//This colours the image with the RGB values

        }//                                                          given at the beginning in the function.

    }

        return ret;

}
