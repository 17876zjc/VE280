#include "simulation.h"
#include "world_type.h"

bool initWorld(world_t &world, const string &speciesFile,const string &creaturesFile)
{
    ifstream iFileSpecies;

    iFileSpecies.close();
    return true;
}

species_t readSpecies(const string filename) //Read a species from a file with name specified
{
    species_t newSpecies;
    newSpecies.name = filename;
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

void printSpecies (const species_t species) // Print out a species(for debug use)
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

string strFix(const string str) //Fix a string read from a File into a normal one.
{
    return str;
}