#include "simulation.h"
#include "world_type.h"

int main(int argc, char *argv[])
{
    world_t world;
    initWorld(world,"species","");//TODO catch if return false
    printWorld(world);
    return 0;
}