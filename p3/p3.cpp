#include "simulation.h"
#include "world_type.h"

int main(int argc, char *argv[])
{
    int rounds = 10;
    world_t world;
    initWorld(world,"species","world-tests/world1");//TODO catch if return false
    printWorld(world);

    for(int i = 0;i < rounds;i++)
    {
        cout<<"Round "<<i+1<<endl;
        simulateRound(world);
    }

    printWorld(world);
    //destructWorld(world);
    return 0;
}