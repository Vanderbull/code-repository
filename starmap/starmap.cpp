#include "starmap.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

Star::Star(int x_a, int y_a)
{
    x=x_a;
    y=y_a;
    int temp;  // This variable will be used to determine if the star is a giant

    classification=rand() % 7;  // This will generate a random number from 0 to 6, for the OBAFGKM classification
    enviroment = rand() % 13;  // This will generate a random number from 0 to 12, for the planet enviroment
    special = rand() % 9;  // This will generate a random number from 0 to 8, for the planet special

    temp=(rand() %100);         // Generate a random number between 0 and 99

    if(temp<PERCENT_GIANTS)          // is this a supergiant
        size=5;                      // then it's size is 5
    else                             // otherwise
        size=(rand() % 3) + 1;       // This will generate a random size from 1 to 3
    next=NULL;    // There is no next star yet

    population = (rand() % 100) + 1;
}

Star::~Star(void)
{
    if(next)			// If there is a star after this one
        delete next;    // Delete it first
}

void Star::Add(Star *n)
{
    if(!next)               // If this star doesn't point to another star
        next=n;             // Then add the passed star to this one
    else                    // Otherwise
        next->Add(n);       // Let the next star handle it
}

int Star::here(int x_a, int y_a)
{
    if((x==x_a) & (y==y_a))                 // Am I at the given location
        return 1;                           // Okay, then return true
    else                                    // Otherwise
        if (next)                           // Is there another star?
            return next->here(x_a, y_a);    // If so, let it handle the request
        else                                // No more stars and no match found
            return 0;                       // return false
}

Star * Star::GetStar(int x_a, int y_a)
{
    if((x==x_a) & (y==y_a))                 // Am I at the given location
        return(this);                       // Hey, it's me.  So return me
    else                                    // Otherwise
        if(next)                            // Is there another star?
            return next->GetStar(x_a, y_a);  // If so, let it handle the request
        else                                // No more stars and no match found
            return NULL;                    // Return NULL
}

int Star::GetClassification(void)
{
    return classification;
}

int Star::GetEnviroment(void)
{
    return enviroment;
}

string Star::GetEnviromentText(void)
{
    if (enviroment == PLANET_TOXIC)
        return "TOXIC";
    else
    if (enviroment == PLANET_TERRAN)
        return "TERRAN";
    else
    if (enviroment == PLANET_STEPPE)
        return "STEPPE";
    else
    if (enviroment == PLANET_RADIATED)
        return "RADIATED";
    else
    if (enviroment == PLANET_OCEAN)
        return "OCEAN";
    else
    if (enviroment == PLANET_MINIMAL)
        return "MINIMAL";
    else
    if (enviroment == PLANET_JUNGLE)
        return "JUNGLE";
    else
    if (enviroment == PLANET_INFERNO)
        return "INFERNO";
    else
    if (enviroment == PLANET_DESERT)
        return "DESERT";
    else
    if (enviroment == PLANET_DEAD)
        return "DEAD";
    else
    if (enviroment == PLANET_BARREN)
        return "BARREN";
    else
    if (enviroment == PLANET_ARID)
        return "ARID";
    else
        return "TUNDRA";
}
string Star::GetSpecialText(void)
{
    if (special == MINERAL_POOR)
        return "MINERAL POOR";
    else
    if (special == ULTRA_POOR)
        return "ULTRA POOR";
    else
    if (special == ARTIFACT)
        return "ARTIFACT";
    else
    if (special == MINERAL_RICH)
        return "MINERAL RICH";
    else
    if (special == ULTRA_RICH)
        return "ULTRA RICH";
    else
    if (special == HOSTILE)
        return "HOSTILE";
    else
    if (special == FERTILE)
        return "FERTILE";
    else
    //if (special == GAIA)
        return "GAIA";

}

int Star::GetSize(void)
{
    return size;
}

Star * Star::GetNext(void)
{
    return next;
}

int Star::GetX(void)
{
    return x;
}

int Star::GetY(void)
{
    return y;
}

StarMap::StarMap(int w, int h)
{
    srand(time(NULL));
    int test = rand() % width;
    width=w;
    height=h;
    stars=NULL;  // There are no stars yet

    int numstars=int(width*height*PERCENT_STARS);  // The number of stars we're going to create

	int x,y;		// x,y coordinates of a created star, generated randomly

    int found;       // a boolean to determine if we found a good place for a new star

    for(int i=0; i<numstars; ++i)
    {
        found=0;            // set found to false
        while(!found)       // while we haven't found a good place
        {
            x=rand() % width;   // Determine x
            y=rand() % height;  // and y randomly
            Star *TempStar=new Star(x,y);  // create a temporary star
            if(!stars)  // If we have no stars yet, then we don't have to check to see if the location is okay.
            {
                stars=TempStar;   // So we simply point stars to it's first star
                found=1;          // And we set found to true so we can get out of the loop
            }
            else if(!stars->here(x,y)) // If there are stars in the list, we have to make sure the current random location is okay
            {
                stars->Add(TempStar);  // If it is, add the newly created star
                found=1;               // And set found to true
            }
			else						// This location is not okay because a star already exists there
			{
				delete TempStar;        // Get rid of this so we don't have memory leaks.
			}

        }
    }
}

StarMap::~StarMap(void)
{
    delete stars;

}

void StarMap::Dump(void)
{
    Star *DumpMe;  // Just to get the color and size
    char * StarColors[7]; // The colors for all 7 classifications
    int classification, size;

    StarColors[STAR_O]="#9bb0ff";
    StarColors[STAR_B]="#aabfff";
    StarColors[STAR_A]="#cad7ff";
    StarColors[STAR_F]="#f8f7ff";
    StarColors[STAR_G]="#fff4ea";
    StarColors[STAR_K]="#ffd2a1";
    StarColors[STAR_M]="#ffcc6f";



    ofstream outfile("stars.html"); //create ofstream object

    // First, let's write out the HTML header
    outfile<<"<html><head><title>Starmap</title></head>"<<endl<<"<body bgcolor=#000000>";


    for(int j=0; j<height; ++j)
    {
        for(int i=0; i<width; ++i)
        {

            DumpMe=stars->GetStar(i,j);   // Is there a star at i,j.  If so, get it
            if(DumpMe)                    // So is this a valid star or a NULL
            {                             // If it's valid
                classification=DumpMe->GetClassification(); //Get its classification
                size=DumpMe->GetSize();  // And its size                
                if(size==1)
                    outfile<<"<font color="<<StarColors[classification]<<">.</font>";
                else if(size==2)
                    outfile<<"<font color="<<StarColors[classification]<<">,</font>";
                else if(size==3)
                    outfile<<"<font color="<<StarColors[classification]<<">+</font>";
                else if(size==5)    // Red Giant
                    outfile<<"<font color=#FF0000>*</font>";
            }
            else
                outfile<<"&nbsp;"<<endl;
        }
        outfile<<"<BR>"<<endl;
    }
    outfile<<"</body></html>"<<endl;
}
