#ifndef MGATE_H
#define MGATE_H

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

class mGate 
{
private:
    int registers[2] = {};
public:
    mGate(int registers[2], std::string name, std::string original);

    mGate(int registers[2], std::string name);

    mGate(std::string instr);

    mGate();

    int source() { return registers[0]; } // usually used to determin what registers are used

    int target()
    {
        return registers[1];
    }

    int count()
    { 
        if(registers[1] >= 0)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }

    std::string name; // this is the name of the gate (x,y,cx, etc)

    std::string original;

    std::string GetStatement();

    void revert();
    
};
#endif