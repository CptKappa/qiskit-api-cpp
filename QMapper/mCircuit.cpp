#include "mCircuit.h"

mCircuit::mCircuit(mArchitecture b, std::list<std::string> l)
{
    Backend = b;
    Gates = ReadGates(l);
    //My = GenerateArchitecture();
}

int mCircuit::Fit()
{
    // update Graphs just in case
    My.updateGraphs();
    Backend.updateGraphs();

    // filter Gates for 2 Qubit Gates
    std::list<mGate> relevant;
    for(mGate var : Gates)
    {
        if(var.count() == 2)
        {
            // is a CX gate, hopefully
            relevant.push_back(var);
        }
    }
    /*
    // go through all relevant Gates and 
    // look at the distances between gates
    // if the total distance is equal to the 
    // number of Gates, we know the circuit fits
    // NOTE: CX directional swap may still have to happen
    int totalDist = 0;
    for(mGate g : relevant)
    {
        
        boost::graph_traits<udGraph>::vertex_descriptor from = Backend.indexVertexTable[g.source()];
        boost::graph_traits<udGraph>::vertex_descriptor to = Backend.indexVertexTable[g.target()];
        
        int dis = Backend.disMap[Backend.indexVertexTable[g.source()]][Backend.indexVertexTable[g.target()]];
        //totalDist += Backend.distances[Backend.indexVertexTable[g.source()]][Backend.indexVertexTable[g.target()]];
        totalDist = totalDist + dis;
    }*/
    /*
    // fixing up the graph if it is not perfect yet
    // skipped if everything fits
    if(totalDist != relevant.size())
    {
        // TODO: Check if we can change registers to make it fit
        // May end calculation if we dont figure

        // Doesnt fit right now
        // TODO: make this not return -1
        return -1;
    }
    */
    // The Gates fit into the Architecture
    // Go through all the gates and invert as nessessary

    int inverted = 0; // inverted CX gates
    int moved = 0; // registers moved to apply CX gates

    std::list<mGate> updated;


    std::list<mGate> pathed;
    
    for(mGate g : Gates){
        if(g.count()==1){
            pathed.push_back(g);
        }else{

            // check if it is directly connected
            boost::graph_traits<udGraph>::vertex_descriptor from = Backend.indexVertexTable[g.source()];
            boost::graph_traits<udGraph>::vertex_descriptor to = Backend.indexVertexTable[g.target()];
        
            int dis = Backend.disMap[Backend.indexVertexTable[g.source()]][Backend.indexVertexTable[g.target()]];

            if(dis == 1){
                // nothing to change
                pathed.push_back(g);
            }else{
                // we have  to find the shortest path to the target 
                // std::cout << "distance larger than 1" << std::endl;
                // this stack is used to return the register back to the original location
                std::list<boost::graph_traits<udGraph>::vertex_descriptor> returnStack;
                
                std::map<boost::graph_traits<udGraph>::vertex_descriptor,boost::graph_traits<udGraph>::vertex_descriptor> predecessors = Backend.getPredecessorMapFrom(g.source());
                
                // predecessors will contain information about how to get from any point to the source
                
                // now do swaps until we get to a vertex next to the source
                // we move the target of gate to the source
                boost::graph_traits<udGraph>::vertex_descriptor current = Backend.indexVertexTable[g.target()];

                // insert swaps until we reach the destination
                while(Backend.disMap[Backend.indexVertexTable[g.source()]][current] > 1){
                    // get the next one
                    boost::graph_traits<udGraph>::vertex_descriptor nextRegister = predecessors[current];

                    int first = Backend.vertexIndexTable[current];
                    int second = Backend.vertexIndexTable[nextRegister];

                    // insert the swap code
                    int sw1[2] = {first,second};
                    int sw2[2] = {second,first};
                    int sw3[2] = {first,second};

                    pathed.push_back(mGate(sw1, "cx"));
                    pathed.push_back(mGate(sw2, "cx"));
                    pathed.push_back(mGate(sw3, "cx"));

                    // add the old current to returnStack
                    returnStack.push_back(current);
                    current = nextRegister;

                }
                // apply the gate
                int ap1[2] = {g.source(),Backend.vertexIndexTable[current]};
                pathed.push_back(mGate(ap1,"cx"));

                // return back
                for(boost::graph_traits<udGraph>::vertex_descriptor nextRegister : returnStack){
                    
                    int first = Backend.vertexIndexTable[current];
                    int second = Backend.vertexIndexTable[nextRegister];

                    // insert the swap code
                    int sw1[2] = {first,second};
                    int sw2[2] = {second,first};
                    int sw3[2] = {first,second};

                    pathed.push_back(mGate(sw1, "cx"));
                    pathed.push_back(mGate(sw2, "cx"));
                    pathed.push_back(mGate(sw3, "cx"));

                    current = nextRegister;
                }
                

            }



            
        }
    }
    // TODO do inversion of gates

    for(mGate g : pathed){
            bool found = false;
            if(Backend.connection.count(g.source())){
                // our source exists...
                
                for(int v : Backend.connection[g.source()] ){
                    if(v == g.target()){
                        found = true;
                    }
                }

                //if(std::find(Backend.connection[g.source()].begin(),Backend.connection[g.source()].end(),g.target())!=Backend.connection[g.source()].end()){
                    // we have a winner
                    if(found){
                        updated.push_back(g);
                    }                    
                //}

            }
            if(!found)
            {
                // this means we have to invert!

                int hS1[2] = {g.source(), -1};
                int hS2[2] = {g.source(), -1};

                int hT1[2] = {g.target(), -1};
                int hT2[2] = {g.target(), -1};

                updated.push_back(mGate(hS1, "h"));
                updated.push_back(mGate(hT1, "h"));
                g.revert();
                updated.push_back(g);
                updated.push_back(mGate(hS2, "h"));
                updated.push_back(mGate(hT2, "h"));

                inverted++;
            }

    }



    Gates = updated;

    if(moved > 0)
    {
        // we had to move register content 
        return 2;
    }

    if(inverted > 0)
    {
        // fit without changes
        return 0;
    }


    
    // Fit with invert
    return 1;
}

std::list<mGate> mCircuit::ReadGates(std::list<std::string> lines)
{
    std::list<mGate> gs;

    for(std::string l : lines)
    {
        if (!l.empty())
        {
            mGate newGate(l);
            
            //mGate newGate(params,name);
            gs.push_back(newGate);
        }
        
    }
    return gs;
}

mArchitecture mCircuit::GenerateArchitecture(){
    // here we generate an Architecture from a list of Gates

    std::map<int,std::list<int>> conns; // connections

    // filter the Gatelist for multi registered Gates (CX - Gates)
    std::list<mGate> relevant;

    for(mGate var : Gates)
    {
        if(var.count() == 2)
        {
            // is a CX gate, hopefully
            relevant.push_back(var);
        }
    }

    // generate all the connections
    for(std::list<mGate>::value_type g : relevant)
    {
        conns[g.source()].push_back(g.target());
    }

    mArchitecture arc(conns);

    return arc;
}

std::string mCircuit::GetGates(){
    
    std::stringstream stream;

    for(mGate g : Gates)
    {
        stream << g.GetStatement() << " ";
    }

    return stream.str();
}


std::list<std::string> mCircuit::GetGatesAsList()
{
    std::list<std::string> list;

    for(mGate g : Gates)
    {
        list.push_back(g.GetStatement());
    }

    return list;
}

void mCircuit::AutoCollapse()
{
    // any dublicate {H, X, Y, Z} Gates will be removed

    //mGate lasts[1] = {};

    std::list<mGate> changed;

    int r[2] { 0,0 };
    mGate empty(r, "---Empty---");

    int maxIndex = 0;

    for(std::map<int,std::list<int>>::value_type t : Backend.connection)
    {
        int tmp = t.first;
        //std::cout <<"the temporary value " << tmp << std::endl;
        //lastGates.insert(std::pair<int,mGate>(t.first,empty));
        //lastGates[t.first] = empty;
        if(maxIndex < tmp) { maxIndex = tmp; }
    }

    mGate lastGates[maxIndex+1];

    for(int i = 0 ; i < maxIndex + 1; i++)
    {
        lastGates[i] = empty;
    }

    for(mGate g : Gates)
    {
        
        // check if Gate is single
        if(g.count() > 1)
        {
            // now both registers have to be reset in last Gates
            if(lastGates[g.source()].name != "---Empty---")
            {
                changed.push_back(lastGates[g.source()]);
            }
            if(lastGates[g.target()].name != "---Empty---")
            {
                changed.push_back(lastGates[g.target()]);
            }            
        
            lastGates[g.source()] = empty;
            lastGates[g.target()] = empty;
            changed.push_back(g);
        }
        else
        {
            if(lastGates[g.source()].name == "---Empty---")
            {
                // adding Gate to last Gates
                lastGates[g.source()] = g;
            }
            else
            {
                if(lastGates[g.source()].name == g.name)
                {
                    std::string n = g.name;
                    boost::to_upper(n);
                    if(n == "H" || n == "X" || n == "Y" || n == "Z")
                    {
                        lastGates[g.source()] = empty;
                    }
                    else
                    {
                        changed.push_back(lastGates[g.source()]);
                        lastGates[g.source()] = g;
                    }
                }
                else
                {
                    changed.push_back(lastGates[g.source()]);
                    lastGates[g.source()] = g;
                }
            }
        }
    }

    for(mGate re : lastGates)
    {
        if(re.name != "---Empty---")
        {
            changed.push_back(re);
        }
    }

    Gates = changed;

}