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

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose)
{
    bool flag = true;
    cout<<"Creature ("<<creature.species->name<<" "<<directName[(int)creature.direction]<<" "
        <<creature.location.r<<" "<<creature.location.c<<") takes action:";
    if(verbose) cout<<endl;
    while(flag)
    {
        //cout << "Simulating "<<creature.species->name << " ID "<<creature.programID<<endl;//
        instruction_t currentIns = creature.species->program[creature.programID];
        int programforward = (creature.programID+1)%(creature.species->programSize);
        point_t adj = adjacentPoint(creature.location,creature.direction);
        switch(currentIns.op)
        {
            case HOP:
                //point_t adj = adjacentPoint(creature.location,creature.direction);
                //cout<<adj.r<<"\t"<<adj.c<<endl;//
                if(adj.r >= 0 && (unsigned)adj.r < grid.height &&
                    adj.c >= 0 && (unsigned)adj.c < grid.width &&
                    grid.squares[adj.r][adj.c] == NULL)
                    {
                        grid.squares[adj.r][adj.c] = grid.squares[creature.location.r][creature.location.c];
                        grid.squares[creature.location.r][creature.location.c] = NULL;
                        creature.location = adj;
                        //printGrid(grid);
                    }
                flag = false;
                break;
            case LEFT:
                creature.direction = leftFrom(creature.direction);
                flag = false;
                break;
            case RIGHT:
                creature.direction = rightFrom(creature.direction);
                flag = false;
                break;
            case INFECT:
                if(adj.r >= 0 && (unsigned)adj.r < grid.height &&
                   adj.c >= 0 && (unsigned)adj.c < grid.width &&
                   grid.squares[adj.r][adj.c] != NULL &&
                   grid.squares[adj.r][adj.c]->species != creature.species)
                    {
                        grid.squares[adj.r][adj.c]->species = creature.species;
                        grid.squares[adj.r][adj.c]->programID = 0;
                    }
                flag = false;
                break;
            case IFEMPTY:
                if(adj.r >= 0 && (unsigned)adj.r < grid.height &&
                   adj.c >= 0 && (unsigned)adj.c < grid.width &&
                   grid.squares[adj.r][adj.c] == NULL)
                    {
                        programforward = currentIns.address-1;
                    }
                break;
            case IFWALL:
                if(adj.r < 0 || (unsigned)adj.r >= grid.height ||
                   adj.c < 0 || (unsigned)adj.c >= grid.width)
                   {
                       programforward = currentIns.address-1;
                   }
                break;
            case IFSAME: 
                if(adj.r >= 0 && (unsigned)adj.r < grid.height &&
                   adj.c >= 0 && (unsigned)adj.c < grid.width &&
                   grid.squares[adj.r][adj.c] != NULL)
                   {
                       if(grid.squares[adj.r][adj.c]->species == creature.species)
                       {
                           programforward = currentIns.address-1;
                       }
                   }
                break;
            case IFENEMY:
                if(adj.r >= 0 && (unsigned)adj.r < grid.height &&
                   adj.c >= 0 && (unsigned)adj.c < grid.width &&
                   grid.squares[adj.r][adj.c] != NULL)
                   {
                       if(grid.squares[adj.r][adj.c]->species != creature.species)
                       {
                           programforward = currentIns.address-1;
                       }
                   }
                break;
            case GO:
                programforward = currentIns.address-1;
                break;
        }
        if(verbose)
        {
            cout<<"Instruction "<<creature.programID+1<<": "<<opName[(int)currentIns.op];
            if(currentIns.address > 0) cout<<" "<<currentIns.address<<endl;
            else cout<<endl;
            if(currentIns.op == HOP || currentIns.op == LEFT || currentIns.op == RIGHT || currentIns.op == INFECT)
            {
                printGrid(grid);
            }
        }
        else
        {
            if(currentIns.op == HOP || currentIns.op == LEFT || currentIns.op == RIGHT || currentIns.op == INFECT)
            {
                cout<<" "<<opName[(int)currentIns.op]<<endl;
            }
        }
        creature.programID = programforward;
    }
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
    if(!iFile)//Error 3
    {
        cout<<"Error: Cannot open file "<<filename<<"!"<<endl;
        exit(0);
    }
    string newline;
    while(getline(iFile,newline) && (!newline.empty()))
    {
        if(newSpecies.programSize + 1 > MAXPROGRAM)//Error 5
        {
            cout<<"Error: Too many instructions for species "<<newSpecies.name<<"!"<<endl;
            cout<<"Maximal number of instructions is "<<MAXPROGRAM<<"."<<endl;
            iFile.close();
            exit(0);
        }
        try//Error 6
        {
            newSpecies.program[newSpecies.programSize] = analyzeInstruction(newline);
        }
        catch(string op)
        {
            cout<<"Error: Instruction "<<op<<" is not recognized!"<<endl;
            iFile.close();
            exit(0);
        }
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
    throw op;
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
    throw dir;
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
    /*
    for(int i = 0; (unsigned)i < world.numSpecies ; i++)
    {
        printSpecies(world.species[i]);
        cout<<endl;
    }
    */
    printGrid(world.grid);
}

bool readSpeciesSummary(world_t & world,const string speciesFile)
{
    ifstream iFilesummary;

    iFilesummary.open(speciesFile); //Error to be thrown if bad file open
    if(!iFilesummary)//Error 3
    {
        cout<<"Error: Cannot open file "<<speciesFile<<"!"<<endl;
        exit(0);
    }
    string dir;
    getline(iFilesummary,dir);
    string fname;
    while(getline(iFilesummary,fname) && (!fname.empty()))
    {
        if(world.numSpecies+1 > MAXSPECIES)//Error 4
        {
            cout<<"Error: Too many species!"<<endl;
            cout<<"Maximal number of species is "<<MAXSPECIES<<"."<<endl;
            iFilesummary.close();
            exit(0);
        }
        string fulldir = dir+"/"+fname;
        world.species[world.numSpecies] = readSpecies(fulldir);
        world.numSpecies++;
    }

    iFilesummary.close();
    return true; //TODO return true if successful
}

bool readCreatures(world_t & world, const string worldFile)
{
    world.numCreatures = 0;
    for(int i = 0;(unsigned)i < MAXHEIGHT;i++)
    {
        for(int j = 0;(unsigned)j < MAXWIDTH;j++)
        {
            (world.grid.squares)[i][j] = NULL;
        }
    }

    ifstream iFileWorld;
    iFileWorld.open(worldFile);
    if(!iFileWorld)//Error 3
    {
        cout<<"Error: Cannot open file "<<worldFile<<"!"<<endl;
        exit(0);
    }
    string line;
    getline(iFileWorld,line); // read row
    world.grid.height = atoi(line.c_str());
    if(world.grid.height < 1 || world.grid.height >MAXHEIGHT)//Error 10
    {
        cout<<"Error: The grid height is illegal!"<<endl;
        iFileWorld.close();
        exit(0);
    }
    getline(iFileWorld,line); // read column
    world.grid.width = atoi(line.c_str());
    if(world.grid.width < 1 || world.grid.width > MAXWIDTH)//Error 11
    {
        cout<<"Error: The grid width is illegal!"<<endl;
        iFileWorld.close();
        exit(0);
    }
    while(getline(iFileWorld,line)&&(!line.empty()))
    {
        if(world.numCreatures + 1 > MAXCREATURES)//Error 7
        {
            cout<<"Error: Too many creatures!"<<endl;
            cout<<"Maximal number of creatures is "<<MAXCREATURES<<"."<<endl;
            iFileWorld.close();
            exit(0);
        }
        istringstream istream;
        istream.str(line);
        string species;//species name
        string dir;//direction
        int initRow;//initial-row
        int initCol;//initial-column

        istream >> species >> dir >> initRow >> initCol;
        if(initRow < 0 || (unsigned)initRow >= world.grid.height
         ||initCol < 0 || (unsigned)initCol >= world.grid.width)//Error 12
        {
            cout<<"Error: Creature ("<<species<<" "<<dir<<" "<<initRow<<" "<<initCol<<") is out of bound!"<<endl;
            cout<<"The grid size is "<<world.grid.height<<"-by-"<<world.grid.width<<"."<<endl;
            iFileWorld.close();
            exit(0);
        }

        world.creatures[world.numCreatures].location = point_t{initRow,initCol};
        try//Error 9
        {
            world.creatures[world.numCreatures].direction = matchDirection(dir); 
        }
        catch(string dir)
        {
            cout<<"Error: Direction "<<dir<<" is not recognized!"<<endl;
            iFileWorld.close();
            exit(0);
        }
        
        world.creatures[world.numCreatures].species = matchSpecies(world.species,world.numSpecies,species);
        if(world.creatures[world.numCreatures].species == NULL)//Error 8
        {
            cout<<"Error: Species "<<species<<" not found!"<<endl;
            iFileWorld.close();
            exit(0);
        }
        world.creatures[world.numCreatures].programID = 0;
        if(world.grid.squares[initRow][initCol] != NULL)//Error 13
        {
            cout<<"Error: Creature ("<<species<<" "<<dir<<" "<<initRow<<" "<<initCol<<") overlaps with creature ("
               <<world.grid.squares[initRow][initCol]->species->name<<" "
               <<directName[(int)world.grid.squares[initRow][initCol]->direction]<<" "
               <<world.grid.squares[initRow][initCol]->location.r<<" "
               <<world.grid.squares[initRow][initCol]->location.c<<")!"<<endl;
            iFileWorld.close();
            exit(0);
        }

        world.grid.squares[initRow][initCol] = &world.creatures[world.numCreatures];
        world.numCreatures++;
    }
    iFileWorld.close();
    return true;//TODO return false if error
}

bool simulateRound(world_t & world,bool verbose)
{
    //TODO
    for(int i = 0; (unsigned)i < world.numCreatures; i++)
    {
        simulateCreature(world.creatures[i],world.grid,verbose);
    }
    return true;
}