#ifndef TECHMAP_H_INCLUDED
#define TECHMAP_H_INCLUDED

#include <string>
// DEFINES

class Tech
{
    private:

        int x,y;   // The stars location on the starmap grid
        int classification; // The stellar classification
        int size; //The size of the star ranges from 1 to 3, and then 5 for super giants


        // char *name;      This will be taken care of in another tutorial
        // Planet *planets;   Again, in another tutorial
        Tech *next;  // The next star
        Tech *prev;  // The next star

    public:
        Tech(int, int); //constructor
        ~Tech(void); //destructor
        void Add(Tech *); // Add a star to the list
        int here(int, int); // Is there a star at the given coordinates?
        Tech * GetTech(int, int); //return the star at the given location, otherwise return null
        int GetClassification(void); //Get this star's classification
        int GetSize(void); //Get this star's size
        Tech *GetNext(void); // return the next star
        int GetX(void);  // Get this star's X coordinate
        int GetY(void);  // Get this star's Y coordinate

        std::string name;
        int research_cost;
        int level;
        int researched;
};

class TechMap
{
    private:
        int tech_science_computers_procentage;
        int tech_science_construction_procentage;
        int tech_science_forcefields_procentage;
        int tech_science_planetology_procentage;
        int tech_science_propulsion_procentage;
        int tech_science_weapons_procentage;

        int tech_science_computers;
        int tech_science_construction;
        int tech_science_forcefields;
        int tech_science_planetology;
        int tech_science_propulsion;
        int tech_science_weapons;

        int tech_science_computers_accumulated;
        int tech_science_construction_accumulated;
        int tech_science_forcefields_accumulated;
        int tech_science_planetology_accumulated;
        int tech_science_propulsion_accumulated;
        int tech_science_weapons_accumulated;


        int tech_points_every_turn;

        int width, height; // The size of the starmap in grids

    public:
        Tech * techs;  // Pointer the stars in the map
        TechMap(int, int);  // Constructor - passed width and height
        ~TechMap(void); // Destructor
        void Update();
        void Dump(void); // Dump the Starmap to an HTML file

};


#endif // TechMAP_H_INCLUDED
