#ifndef MARCHITECTURE_H
#define MARCHITECTURE_H

#include <map>
#include <list>
#include <tuple>
#include <iostream>
#include <queue>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/directed_graph.hpp>
#include <boost/graph/exterior_property.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/array.hpp>

typedef boost::undirected_graph<boost::no_property> udGraph;
typedef boost::directed_graph<> dGraph;
typedef boost::graph_traits<udGraph>::vertex_descriptor vertex_des;


typedef boost::graph_traits<udGraph>::edge_descriptor edge_des;

// The name map provides an abstract accessor for the names of
// each vertex. This is used during graph creation.
//typedef boost::property_map<udGraph, std::string Actor::*>::type NameMap;

// Declare a matrix type and its corresponding property map that
// will contain the distances between each pair of vertices.
typedef boost::exterior_vertex_property<udGraph, int> DistanceProperty;
typedef DistanceProperty::matrix_type DistanceMatrix;
typedef DistanceProperty::matrix_map_type DistanceMatrixMap;

// Declare the weight map so that each edge returns the same value.
typedef boost::constant_property_map<edge_des, int> WeightMap;


class mArchitecture
{
public:
    std::list<std::tuple<int,int>> directional; // From register, to register
    std::map<int, std::list<int>> connection; // a register and all registered beeing the target of connection
    udGraph generalGraph;
    DistanceMatrixMap distances;
    std::map<vertex_des, std::map<vertex_des, int>> disMap;
    std::map<int,boost::graph_traits<udGraph>::vertex_descriptor> indexVertexTable;
    std::map<boost::graph_traits<udGraph>::vertex_descriptor,int> vertexIndexTable;
    dGraph directionalGraph;

    mArchitecture(std::list<std::tuple<int, int>> d)
    {
        directional = d;
        
        updateConnection();
        updateDirectional();
        updateGraphs();
    }

    mArchitecture(std::map<int, std::list<int>> c)
    {
        connection = c;
        
        updateDirectional();
        updateConnection();
        updateGraphs();
    }

    mArchitecture();

    void updateDirectional();
    void updateConnection();

    void updateGraphs(); // this method should only be called with updated connection

    std::map<vertex_des,vertex_des> getPredecessorMapFrom(int source);
    std::list<int> getConnectedVertecies(int source);
    std::map<int,int> getIndexedPredecessorMap(std::map<vertex_des,vertex_des> map);
};

#endif