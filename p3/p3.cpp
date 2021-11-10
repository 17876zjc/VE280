#include "simulation.h"
#include "world_type.h"

int main(int argc, char *argv[])
{
    int rounds;
    bool verbose = false;
    string speciesFile;
    string worldFile;
    
    if(argc <= 3||argc >= 6)//Error 1
    {
        cout<<"Error: Missing arguments!"<<endl;
        cout<<"Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"<<endl;
        exit(0);
    }
    else
    {
        speciesFile = string(argv[1]);
        worldFile = string(argv[2]);
        rounds = atoi(argv[3]);
        if(rounds < 0)//Error 2
        {
            cout<<"Error: Number of simulation rounds is negative!"<<endl;
            exit(0);
        }
        if(argc == 5)
        {
            if(string(argv[4]) == "v" || string(argv[4]) == "verbose")
            {
                verbose = true;
            }
        }
    }

    //TODO: check wrong arguments.
    world_t world;
    initWorld(world,speciesFile,worldFile);//TODO catch if return false
    cout<<"Initial state"<<endl;
    printWorld(world);

    for(int i = 0;i < rounds;i++)
    {
        cout<<"Round "<<i+1<<endl;
        simulateRound(world,verbose);
        if(!verbose) printWorld(world);
    }
    return 0;
}