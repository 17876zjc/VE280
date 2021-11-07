#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"
#include <String>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

bool initWorld(world_t &world, const string &speciesFile,const string &creaturesFile);
// MODIFIES: world
//
// EFFECTS: Initialize "world" given the species summary file
// "speciesFile" and the world description file
// "creaturesFile". This initializes all the components of
// "world". Returns true if initialization is successful.

// MODIFIES: world
//
// EFFECTS: Initialize "world" given the species summary file
// "speciesFile" and the world description file
// "creaturesFile". This initializes all the components of
// "world". Returns true if initialization is successful.

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS: Simulate one turn of "creature" and update the creature,
// the infected creature, and the grid if necessary.
// The creature programID is always updated. The function
// also prints to the stdout the procedure. If verbose is
// true, it prints more information.

void printGrid(const grid_t &grid);
// MODIFIES: cout.
//
// EFFECTS: print a grid representation of the creature world.
point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns a point that results from moving one square
// in the direction "dir" from the point "pt".
direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
// left from the given direction "dir".
direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
// right from the given direction "dir".
instruction_t getInstruction(const creature_t &creature);
// EFFECTS: Returns the current instruction of "creature".
creature_t *getCreature(const grid_t &grid, point_t location);
// REQUIRES: location is inside the grid.
//
// EFFECTS: Returns a pointer to the creature at "location" in "grid".

bool destructWorld(world_t & world);

species_t readSpecies(const string filename);
instruction_t analyzeInstruction(const string line);
opcode_t matchOpCode(const string op);
direction_t matchDirection(const string dir);
species_t * matchSpecies(species_t* species,const unsigned int num,const string str);
void printSpecies (const species_t & species);
void printWorld (const world_t & world);
string StrFix(const string str);
bool readSpeciesSummary(world_t & world,const string speciesFile);
bool readCreatures(world_t & world,const string worldFile);

bool simulateRound(world_t & world);
#endif