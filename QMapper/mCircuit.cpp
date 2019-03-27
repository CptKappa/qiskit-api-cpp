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
    }
    
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
    
    // The Gates fit into the Architecture
    // Go through all the gates and invert as nessessary

    int inverted = 0;

    std::list<mGate> updated;

    
    for(mGate g : Gates){
        if(g.count()==1){
            updated.push_back(g);
        }else{
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
    }
    

    Gates = updated;

    if(inverted > 0)
    {
        return 0;
    }
    
    // We know it fits but dont know if with CX direction changes
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