#ifndef SIMULATION_H
#define SIMULATION_H

#include "world_type.h"
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

species_t readSpecies(const string filename);
//EFFECTS: Returns a species read from a given file name.
instruction_t analyzeInstruction(const string line);
//EFFECTS: Returns an instructiton analyzed from a given string.
opcode_t matchOpCode(const string op);
//EFFECTS: Returns a matched opcode enumerate from a given string.
direction_t matchDirection(const string dir);
//EFFECTS: Returns a matched direction enumerate from a given string.
species_t * matchSpecies(species_t* species,const unsigned int num,const string str);
//EFFECTS: Returns a pointer to a matching species in a species array with a given string.
void printSpecies (const species_t & species);
//EFFECTS: Print a species information to console(for bebug use).
void printWorld (const world_t & world);
//EFFECTS: Print a world into console
bool readSpeciesSummary(world_t & world,const string speciesFile);
//EFFECTS: Read a species file and store the data in world
//
//MODIFIES: world
bool readCreatures(world_t & world,const string worldFile);
//EFFECTS: Read a creatures file and store the data in world
//
//MODIFIES: world
bool simulateRound(world_t & world,bool verbose);
//EFFECTS: Simulate the game
//
//MODIFIES: world
#endif