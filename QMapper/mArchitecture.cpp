#include "mArchitecture.h"

void mArchitecture::updateDirectional()
{
    std::list<std::tuple<int, int>> d;

    for(std::map<int, std::list<int>>::value_type var : connection)
    {
        for(std::list<int>::value_type part : var.second)
        {
            std::tuple<int, int> dir(var.first, part);
            d.push_back(dir);
        }
    }
        
    directional = d;
}

void mArchitecture::updateConnection()
{
    std::map<int, std::list<int>> con;
    for(std::tuple<int, int> var : directional)
    {
        std::map<int,std::list<int>>::iterator it = con.find(std::get<0>(var));

        
        if(it == con.end())
        {
            con[std::get<0>(var)] = std::list<int>();
            con[std::get<0>(var)].push_back(std::get<1>(var));
        }
        else
        {
            con[std::get<0>(var)].push_back(std::get<1>(var));
        }
    }
    
    connection = con;
}

void mArchitecture::updateGraphs()
{
    udGraph uG;
    dGraph dG;

    std::map<int,boost::graph_traits<dGraph>::vertex_descriptor> dVs;

    std::list<int> ids;

    for(std::map<int, std::list<int>>::value_type var : connection)
    {
        ids.push_back(var.first);
        for(int ts : var.second){
            ids.push_back(ts);
        }
    }

    ids.sort();
    ids.unique();

    for(int i : ids){
        indexVertexTable[i] = uG.add_vertex();
        dVs[i] = dG.add_vertex();
    }

    for(std::map<int, std::list<int>>::value_type var : connection)
    {
        for(int tar : var.second)
        {
            uG.add_edge(indexVertexTable[var.first], indexVertexTable[tar]);
            dG.add_edge(dVs[var.first], dVs[tar]);
            
        }
    }
    //std::map<vertex_des, std::map<vertex_des, int>> matrix;
    
    DistanceMatrix dists(num_vertices(uG));
    DistanceMatrixMap dm(dists, uG);
    WeightMap wm(1);
    std::map<vertex_des, std::map<vertex_des, int>> ownmap;

    bool b1 = boost::floyd_warshall_initialized_all_pairs_shortest_paths(uG,dm,weight_map(wm));
    bool b2 = boost::floyd_warshall_all_pairs_shortest_paths(uG,ownmap,weight_map(wm));

    disMap = ownmap;

    distances = dm;
    generalGraph = uG;
    directionalGraph = dG;
}

mArchitecture::mArchitecture(){
    int num = 1;
}

