#include "mArchitecture.h"
#include "mCircuit.h"

#include <list>
#include <map>
#include <string>
#include <iostream>

#include <boost/range.hpp>

int main()
{
    
    std::map<int,std::list<int>> back;

    back[1].push_back(0);

    back[2].push_back(0);
    back[2].push_back(1);

    back[3].push_back(2);

    back[4].push_back(2);
    back[4].push_back(3);

    //back[4].push_back(4);

    
    mArchitecture b(back);
    

    std::list<std::string> lines;
    //lines.push_back("H q[2];");
    lines.push_back("CX q[4],q[0];");
    lines.push_back("H q[2];");
    //lines.push_back("CX q[2],q[1];");
    lines.push_back("H q[2];");
    //lines.push_back("CX q[2],q[3];");
    //lines.push_back("H q[2];");
    //lines.push_back("CX q[2],q[4];");
    //lines.push_back("H q[2];");

    //lines.push_back("CX q[1],q[0];");

    //lines.push_back("");
    //lines.push_back("");
    //lines.push_back("");
    //lines.push_back("");

    mCircuit circ(b,lines);

    std::cout << "backend: "<< std::endl;
    for(std::map<int,std::list<int>>::value_type lists : b.connection){
        for(int i : lists.second){
            std::cout << lists.first << " --> " << i << std::endl;
            std::cout << circ.GetBackEnd().indexVertexTable[lists.first] << std::endl;
            std::cout << circ.GetBackEnd().indexVertexTable[i] << std::endl;
        }
    }

    std::cout << "edges: " << std::endl;

    std::cout << circ.GetBackEnd().generalGraph.num_edges() << std::endl;

    


    std::cout << "predicessor" << std::endl;
    std::map<int,int> predecessors = circ.GetBackEnd().getIndexedPredecessorMap(circ.GetBackEnd().getPredecessorMapFrom(0));

    mArchitecture arc = circ.GetBackEnd();
    for(std::map<int,int>::value_type v : predecessors)
    {
        
        std::cout << v.first << " pred " << v.second << std::endl;
    }
    



    std::cout << circ.GetGates() << std::endl;

    std::cout << "my dictioary: " << back.size() << std::endl;

    std::cout << "Count of Vertecies: " << circ.GetBackEnd().indexVertexTable.size() << std::endl;

    std::cout << "Count of connections: " << circ.GetBackEnd().connection.size() << std::endl;

    //std::cout << "distances: " << boost::size(circ.GetBackEnd().distances) << std::endl;
    
    std::cout << "Architecture Fitting: " << circ.Fit() << std::endl;

    std::cout << circ.GetGates() << std::endl;

    std::cout << "Auto Collapse!" << std::endl;

    circ.AutoCollapse();

    std::cout << circ.GetGates() << std::endl;

    std::cout << "It works a bit" << std::endl;

    return 0;
}
