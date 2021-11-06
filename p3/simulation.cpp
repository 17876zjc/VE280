#include "simulation.h"
#include "world_type.h"

bool initWorld(world_t &world, const string &speciesFile,const string &creaturesFile)
{
    world.numSpecies = 0;
    world.numCreatures = 0;
    readSpeciesSummary(world,speciesFile);
    readCreatures(world,creaturesFile);
    return true; // TODO return true if open successful
}

bool destructWorld(world_t & world)
{
    for(int i = 0;(unsigned)i < MAXHEIGHT; i++)
    {
        for(int j = 0; (unsigned)j < MAXWIDTH; j++)
        {
            if(world.grid.squares[i][j] != NULL)
            {
                delete(world.grid.squares[i][j]);
            }
        }
    }
    return true;//TODO return false is delete unsuccessful;
}

point_t adjacentPoint(point_t pt, direction_t dir)
{
    switch(dir)
    {
        case EAST:
            pt.c++;
            break;
        case SOUTH:
            pt.r++;
            break;
        case WEST:
            pt.c--;
            break;
        case NORTH:
            pt.r--;
            break;
    }
    return pt;
}

direction_t leftFrom(direction_t dir)
{
    return (direction_t)(((int)(dir)+3)%4);
}

direction_t rightFrom(direction_t dir)
{
    return (direction_t)(((int)(dir)+1)%4);
}

instruction_t getInstruction(const creature_t &creature)
{
    return creature.species->program[creature.programID];
}

creature_t *getCreature(const grid_t &grid, point_t location)
{
    return (grid.squares)[location.r][location.c];
}

species_t readSpecies(const string filename) //Read a species from a file with name specified
{
    species_t newSpecies;
    string speciesName = filename;
    while(true)
    {
        long unsigned index = speciesName.find("/",0);
        if(index == string::npos) break;
        speciesName = speciesName.substr(index+1,string::npos);
    }

    newSpecies.name = speciesName;
    newSpecies.programSize = 0;
    ifstream iFile;
    iFile.open(filename);
    string newline;
    while(getline(iFile,newline) && (!newline.empty()))
    {
        newSpecies.program[newSpecies.programSize] = analyzeInstruction(newline);
        newSpecies.programSize++;
    }
    iFile.close();
    return newSpecies;
}

instruction_t analyzeInstruction(const string line) // analyze the instructions line by line
{
    instruction_t newInstruction;
    newInstruction.address = -1;
    istringstream iStream;
    iStream.str(line);
    string ins;
    iStream >> ins;
    newInstruction.op = matchOpCode(ins);
    if(line.length() == ins.length() || line[ins.length()+1] == ' ')
    {
        newInstruction.address = 0;
    }
    else
    {
        iStream >> newInstruction.address;
    }
    return newInstruction;
}

opcode_t matchOpCode(const string op) // match the Opcode number with op name.
{
    for(int i = 0; i < 9;i++)
    {
        if(op == opName[i])
        {
            return opcode_t(i);
        }
    }
    return opcode_t(-1); // Error to be catched
}

direction_t matchDirection(const string dir)
{
    for(int i = 0; i < 4;i++)
    {
        if(dir == directName[i])
        {
            return direction_t(i);
        }
    }
    return direction_t(-1);// Error to be catched
}

species_t * matchSpecies(species_t* species,const unsigned int num,const string str)
{
    for(int i = 0;(unsigned)i < num; i++)
    {
        if(species[i].name == str)
        {
            return species+i;
        }
    }
    return NULL;//if not found
}

void printSpecies (const species_t & species) // Print out a species(for debug use)
{
    cout << "The name is: "<< species.name<<endl;
    cout << "It has: "<<species.programSize << " programs"<<endl;
    for (int i = 0; (unsigned)i < species.programSize; i++)
    {
        cout << i+1<<": "<<opName[int(species.program[i].op)]<<" ";
        if (species.program[i].address)
        {
            cout<<species.program[i].address<<endl;
        }
        else
        {
            cout <<endl;
        }
        
    } 
}

void printGrid(const grid_t &grid)
{
    //cout<<"Height: "<<grid.height<<" Width: "<<grid.width<<endl;
    for(int i = 0;(unsigned)i < grid.height; i++)
    {
        for(int j = 0;(unsigned)j < grid.width; j++)
        {
            //cout<<i<<"\t"<<j<<endl;
            if(grid.squares[i][j] == NULL)
            {
                cout<<"____ ";
            }
            else
            {
                string nameShort = (grid.squares[i][j]->species->name).substr(0,2);
                cout<<nameShort<<"_"<<directShortName[(int)(grid.squares[i][j]->direction)]<<" ";
            }
            //cout<<grid.squares[i][j]<<" ";
        }
        cout<<endl;
    }
}

void printWorld (const world_t & world)
{
    for(int i = 0; (unsigned)i < world.numSpecies ; i++)
    {
        printSpecies(world.species[i]);
        cout<<endl;
    }
    printGrid(world.grid);
}

string strFix(const string str) //Fix a string read from a File into a normal one.
{
    return str;
}


bool readSpeciesSummary(world_t & world,const string speciesFile)
{
    ifstream iFilesummary;

    iFilesummary.open(speciesFile); //Error to be thrown if bad file open
    string dir;
    getline(iFilesummary,dir);
    string fname;
    while(getline(iFilesummary,fname) && (!fname.empty()))
    {
        string fulldir = dir+"/"+fname;
        world.species[world.numSpecies] = readSpecies(fulldir);
        world.numSpecies++;
    }

    iFilesummary.close();
    return true; //TODO return true if successful
}

bool readCreatures(world_t & world, const string worldFile)
{
    for(int i = 0;(unsigned)i < MAXHEIGHT;i++)
    {
        for(int j = 0;(unsigned)j < MAXWIDTH;j++)
        {
            (world.grid.squares)[i][j] = NULL;
        }
    }

    ifstream iFileWorld;
    iFileWorld.open(worldFile);
    string line;
    getline(iFileWorld,line); // read row
    world.grid.height = atoi(line.c_str());
    getline(iFileWorld,line); // read column
    world.grid.width = atoi(line.c_str());

    while(getline(iFileWorld,line)&&(!line.empty()))
    {
        istringstream istream;
        istream.str(line);
        string species;//species name
        string dir;//direction
        int initRow;//initial-row
        int initCol;//initial-column

        istream >> species >> dir >> initRow >> initCol;

        //cout<<species<<" "<<dir<<" "<<initRow_s<<" "<<initCol_s<<endl;
        creature_t *creature = new creature_t;
        creature->location = point_t{initRow,initCol};
        creature->direction = matchDirection(dir);
        creature->species = matchSpecies(world.species,world.numSpecies,species);
        creature->programID = 0;


        world.grid.squares[initRow][initCol] = creature;
    }
    iFileWorld.close();
    return true;//TODO return false if error
}