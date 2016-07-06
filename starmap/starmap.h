#ifndef STARMAP_H_INCLUDED
#define STARMAP_H_INCLUDED

#include <string>
using namespace std;
// DEFINES

#define PERCENT_STARS .10    // The fraction of the map that has stars
#define PERCENT_GIANTS  3    // The chance that any given star is a super giant

#define STAR_O      0
#define STAR_B      1
#define STAR_A      2
#define STAR_F      3
#define STAR_G      4
#define STAR_K      5
#define STAR_M      6

#define PLANET_TERRAN     0
#define PLANET_JUNGLE     1
#define PLANET_OCEAN      2
#define PLANET_ARID       3
#define PLANET_STEPPE     4
#define PLANET_DESERT     5
#define PLANET_MINIMAL    6
#define PLANET_BARREN     7
#define PLANET_TUNDRA     8
#define PLANET_DEAD       9
#define PLANET_INFERNO   10
#define PLANET_TOXIC     11
#define PLANET_RADIATED  12

#define MINERAL_POOR  0
#define ULTRA_POOR    1
#define ARTIFACT      2
#define MINERAL_RICH  3
#define ULTRA_RICH    4
#define HOSTILE       5
#define FERTILE       6
#define GAIA          7

class Star
{
    private:
        int x,y;   // The stars location on the starmap grid
        int classification; // The stellar classification
        int enviroment; // The planetary enviroment
        int size; //The size of the star ranges from 1 to 3, and then 5 for super giants


        // char *name;      This will be taken care of in another tutorial
        // Planet *planets;   Again, in another tutorial
        Star *next;  // The next star

    public:
        Star(int, int); //constructor
        ~Star(void); //destructor
        void Add(Star *); // Add a star to the list
        int here(int, int); // Is there a star at the given coordinates?
        Star * GetStar(int, int); //return the star at the given location, otherwise return null
        int GetClassification(void); //Get this star's classification
        int GetEnviroment(void); // Get this star's planet enviroment
        string GetEnviromentText(void); // Get this star's planet enviroment
        string GetSpecialText(void); // Get this star's planet enviroment
        int GetSize(void); //Get this star's size
        Star *GetNext(void); // return the next star
        int GetX(void);  // Get this star's X coordinate
        int GetY(void);  // Get this star's Y coordinate

        int special; // planetary special
        int defense_shield;
        int factories;
        int industrial_waste;
        int missile_bases;
        int population;
        int growth;
        int owner;
};

class StarMap
{
    private:
        int width, height; // The size of the starmap in grids

    public:
        Star * stars;  // Pointer the stars in the map
        StarMap(int, int);  // Constructor - passed width and height
        ~StarMap(void); // Destructor
        void Dump(void); // Dump the Starmap to an HTML file
};


#endif // STARMAP_H_INCLUDED
