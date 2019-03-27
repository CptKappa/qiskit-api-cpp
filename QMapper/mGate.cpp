#include "mGate.h"

mGate::mGate(int registers[2], std::string name, std::string original)
{
    this->registers[0] = registers[0];
    this->registers[1] = registers[1];

    this->name = name;
    this->original = original;
}

mGate::mGate(int registers[2], std::string name)
{
    this->registers[0] = registers[0];
    this->registers[1] = registers[1];

    this->name = name;
    this->original = "";
}

mGate::mGate()
{
    registers[0] = 0;
    registers[1] = -1;

    name = "---Empty---";
}

mGate::mGate(std::string instr)
{
    std::vector<std::string> results;
    // Remove the semi column at the end
    std::string s = instr.substr(0, instr.length() - 1);

    // get the gate in 0 and the registers in 1 seperated by ','
    boost::split(results, s, [](char c){ return c == ' '; });

    // safe the gate, just in case
    std::string name = results.at(0);
            
    // now start seperating the registers; number does not matter, will always take 2 at max
    std::vector<std::string> registers;

    boost::split(registers, results[1], [](char c){ return c == ','; }); // same as above
            
    // params for mGate
    int params[2];
            
    // having at least 1 register is certain
    // prepare the string to be cast to int
    std::string fromPrep = registers.at(0).substr(2, registers.at(0).length() - 3);
    int origin = std::stoi(fromPrep);
            
    params[0] = origin;

    // check for second register
    if(registers.size() > 1)
    {
        std::string toPrep = registers.at(1).substr(2, registers.at(1).length() - 3);
        int to = std::stoi(toPrep);
        params[1] = to;
    }
    else
    {
        params[1] = -1;
    }

    // Set parameters
    this->registers[0] = params[0];
    this->registers[1] = params[1];

    this->name = name;
    this->original = instr;
}

std::string mGate::GetStatement()
{
    std::string s;
    
    if (this->name == "cx" || this->original.empty())
    {
        s = name + " q[" + std::to_string(registers[0]) + "]";

        if(count() > 1)
        {
            s += ",q[" + std::to_string(registers[1]) + "]";
        }

        s += ";";
    }
    else
    {
        s = this->original;
    }
    
    return s;
}

void mGate::revert()
{
    if(count() > 1)
    {
        int t = registers[0];
        registers[0] = registers[1];
        registers[1] = t;
    }
}
