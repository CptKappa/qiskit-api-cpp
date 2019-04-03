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
        vertexIndexTable[indexVertexTable[i]] = i;
        dVs[i] = dG.add_vertex();
    }

    for(std::map<int, std::list<int>>::value_type var : connection)
    {
        for(int tar : var.second)
        {
            uG.add_edge(indexVertexTable[var.first], indexVertexTable[tar]);
            //uG.add_edge(indexVertexTable[tar],indexVertexTable[var.first]);
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

std::map<vertex_des,vertex_des> mArchitecture::getPredecessorMapFrom(int source){

    std::map<vertex_des,vertex_des> pred;
       

    std::queue<int> dis;
    dis.push(source);
    //std::cout << "start search" << std::endl;
    while(!dis.empty()){
        int u = dis.front();
        dis.pop();
        //std::cout << u << std::endl;
        for(int i : getConnectedVertecies(u)){
            // if not in map add it and queue it
            // std::cout <<  i << std::endl;
            
            if( !(pred.find(indexVertexTable[i]) != pred.end())){
                pred[indexVertexTable[i]] = indexVertexTable[u];
                dis.push(i);
                //std::cout << "is not in pred" << std::endl;
            }
        }
    }
    pred[indexVertexTable[source]] = indexVertexTable[source];

    // std::cout << "end search" << std::endl;
    return pred;
}



std::list<int> mArchitecture::getConnectedVertecies(int source){
    
    std::list<int> vecs;
    // std::cout << "get connected " << source << std::endl;
    for(std::list<std::tuple<int,int>>::value_type tupl : directional){
        if(std::get<1>(tupl)==source){
            // std::cout << "To" << std::endl;
            if(!(std::find(vecs.begin(),vecs.end(),std::get<0>(tupl))!=vecs.end())){
                vecs.push_back(std::get<0>(tupl));
                // std::cout << std::get<0>(tupl) << std::endl;
            }
        }

        if(std::get<0>(tupl)==source){
            //std::cout << "From" << std::endl;
            if(!(std::find(vecs.begin(),vecs.end(),std::get<1>(tupl))!=vecs.end())){
                vecs.push_back(std::get<1>(tupl));
                //std::cout << std::get<1>(tupl) << std::endl;
            }
        }   
    }

    return vecs;

    
    
    typename boost::graph_traits<udGraph>::adjacency_iterator ai;
    typename boost::graph_traits<udGraph>::adjacency_iterator ai_end;

    // std::cout << "from " << source << std::endl;

    for(tie(ai,ai_end) = boost::adjacent_vertices(indexVertexTable[source],generalGraph); ai != ai_end; ++ai){
        vecs.push_back(vertexIndexTable[*ai]);
        // std::cout << "Connected: " << *ai << std::endl;
    }

    return vecs;

}

std::map<int,int> mArchitecture::getIndexedPredecessorMap(std::map<vertex_des,vertex_des> map){
    
    std::map<int,int> changed;
    
    for(std::map<vertex_des,vertex_des>::value_type v : map){
        changed[vertexIndexTable[v.first]] = vertexIndexTable[v.second];
    }
    return changed;
}