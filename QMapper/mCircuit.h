#ifndef MCIRCUIT_H
#define MCIRCUIT_H

#include <map>
#include <list>
#include <tuple>
#include <string>
#include <iostream>
#include <utility>
#include <vector>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/directed_graph.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/array.hpp>

#include "mArchitecture.h"
#include "mGate.h"


class mCircuit
{
private:
    mArchitecture Backend;
    mArchitecture My;
    std::list<mGate> Gates;

public:
    mCircuit(mArchitecture b, std::list<std::string> l);
    int Fit(); // -1 doesn't fit; 0 needs changes; 1 fits already; 2 or more we moved registers
    mArchitecture GenerateArchitecture();
    void SetBackend(mArchitecture& b){ Backend =  b; }
    std::list<mGate> ReadGates(std::list<std::string> lines);
    std::string GetGates();
    std::list<std::string> GetGatesAsList();
    mArchitecture GetBackEnd(){ return Backend; }
    void AutoCollapse();

};

#endif