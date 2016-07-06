#include <SDL.h>
#include "techmap.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Tech::Tech(int x_a, int y_a)
{
    next=NULL;    // There is no next star yet
    prev=NULL;
    research_cost = rand()%5000;
    level = (rand() % 50) + 1;
    name = "default";
    researched = 0;


}

Tech::~Tech(void)
{
    if(next)			// If there is a star after this one
        delete next;    // Delete it first
}

void Tech::Add(Tech *n)
{
    if(!next)               // If this star doesn't point to another star
        next=n;             // Then add the passed star to this one
    else                    // Otherwise
        next->Add(n);       // Let the next star handle it
    prev = n;
}

int Tech::here(int x_a, int y_a)
{
    if((x==x_a) & (y==y_a))                 // Am I at the given location
        return 1;                           // Okay, then return true
    else                                    // Otherwise
        if (next)                           // Is there another star?
            return next->here(x_a, y_a);    // If so, let it handle the request
        else                                // No more stars and no match found
            return 0;                       // return false
}

Tech * Tech::GetTech(int x_a, int y_a)
{
    if((x==x_a) & (y==y_a))                 // Am I at the given location
        return(this);                       // Hey, it's me.  So return me
    else                                    // Otherwise
        if(next)                            // Is there another star?
            return next->GetTech(x_a, y_a);  // If so, let it handle the request
        else                                // No more stars and no match found
            return NULL;                    // Return NULL
}

int Tech::GetClassification(void)
{
    return classification;  // Duh
}

int Tech::GetSize(void)
{
    return size;  // Duh
}

Tech * Tech::GetNext(void)
{
    return next; // Duh
}

int Tech::GetX(void)
{
    return x;   // Duh
}

int Tech::GetY(void)
{
    return y;   // Duh
}

TechMap::TechMap(int w, int h)
{
    tech_points_every_turn = 100;
    tech_science_computers_procentage = 100 / 6;
    tech_science_construction_procentage = 100 / 6;
    tech_science_forcefields_procentage = 100 / 6;
    tech_science_planetology_procentage = 100 / 6;
    tech_science_propulsion_procentage = 100 / 6;
    tech_science_weapons_procentage = 100 / 6;
    Update();


    width=w;
    height=h;
    techs=NULL;  // There are no stars yet

    int numtechs=int(width*height);  // The number of stars we're going to create

	int x,y;		// x,y coordinates of a created star, generated randomly

    int found;       // a boolean to determine if we found a good place for a new star

    for(int i=0; i<numtechs; ++i)
    {
        found=0;            // set found to false
        while(!found)       // while we haven't found a good place
        {
            x=rand() % width;   // Determine x
            y=rand() % height;  // and y randomly
            Tech *TempTech = new Tech(x, y);  // create a temporary star
            if(!techs)  // If we have no stars yet, then we don't have to check to see if the location is okay.
            {
                techs=TempTech;   // So we simply point stars to it's first star
                found=1;          // And we set found to true so we can get out of the loop
            }
            else if(!techs->here(x,y)) // If there are stars in the list, we have to make sure the current random location is okay
            {
                techs->Add(TempTech);  // If it is, add the newly created star
                found=1;               // And set found to true
            }
			else						// This location is not okay because a star already exists there
			{
                delete TempTech;        // Get rid of this so we don't have memory leaks.
			}

        }
    }
}

TechMap::~TechMap(void)
{
    delete techs;
}

void TechMap::Update()
{
    tech_science_computers_accumulated = tech_points_every_turn / tech_science_computers_procentage;
    tech_science_construction_accumulated = tech_points_every_turn / tech_science_construction_procentage;
    tech_science_forcefields_accumulated = tech_points_every_turn / tech_science_forcefields_procentage;
    tech_science_planetology_accumulated = tech_points_every_turn / tech_science_planetology_procentage;
    tech_science_propulsion_accumulated = tech_points_every_turn / tech_science_propulsion_procentage;
    tech_science_weapons_accumulated = tech_points_every_turn / tech_science_weapons_procentage;

    tech_science_computers;
    tech_science_construction;
    tech_science_forcefields;
    tech_science_planetology;
    tech_science_propulsion;
    tech_science_weapons;

    tech_science_computers_accumulated;
    tech_science_construction_accumulated;
    tech_science_forcefields_accumulated;
    tech_science_planetology_accumulated;
    tech_science_propulsion_accumulated;
    tech_science_weapons_accumulated;


    tech_points_every_turn;

}

void TechMap::Dump(void)
{
    Tech *DumpMe;  // Just to get the color and size
    char * TechColors[7]; // The colors for all 7 classifications
    int classification, size;

    //TechColors[STAR_O] = "#9bb0ff";
    //TechColors[STAR_B] = "#aabfff";
    //TechColors[STAR_A] = "#cad7ff";
    //TechColors[STAR_F] = "#f8f7ff";
    //TechColors[STAR_G] = "#fff4ea";
    //TechColors[STAR_K] = "#ffd2a1";
    //TechColors[STAR_M] = "#ffcc6f";



    ofstream outfile("stars.html"); //create ofstream object

    // First, let's write out the HTML header
    outfile<<"<html><head><title>Starmap</title></head>"<<endl<<"<body bgcolor=#000000>";


    for(int j=0; j<height; ++j)
    {
        for(int i=0; i<width; ++i)
        {

            DumpMe = techs->GetTech(i, j);   // Is there a star at i,j.  If so, get it
            if(DumpMe)                    // So is this a valid star or a NULL
            {                             // If it's valid
                classification=DumpMe->GetClassification(); //Get its classification
                size=DumpMe->GetSize();  // And its size                
                if(size==1)
                    outfile << "<font color=" << TechColors[classification] << ">.</font>";
                else if(size==2)
                    outfile << "<font color=" << TechColors[classification] << ">,</font>";
                else if(size==3)
                    outfile << "<font color=" << TechColors[classification] << ">+</font>";
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
