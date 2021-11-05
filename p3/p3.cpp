#include "simulation.h"
#include "world_type.h"

int main(int argc, char *argv[])
{
    world_t world;
    initWorld(world,"species","world-tests/world1");//TODO catch if return false
    printWorld(world);
    destructWorld(world);
    return 0;
}