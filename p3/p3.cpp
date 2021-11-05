#include "simulation.h"
#include "world_type.h"

int main(int argc, char *argv[])
{
    species_t flytrap = readSpecies("flytrap");
    printSpecies(flytrap);
    return 0;
}