/**
 * @file graph.h
 * Graph Library Declarations
 *
 * Written for CS 225 Spring 2011
 * @author Sean Massung
 *
 * Updated Spring 2012 by Sean Massung
 *  - Added doxygen comments
 *  - Created better error handling
 *  - More encapsulated and object-oriented
 * 
 *  Updated Spring 2018 by Jordi
 *  - Added doxygen comments
 *  - Created better error handling
 *  - More encapsulated and object-oriented
 *
 * Update Spring 18 by Simeng
 * - Finishing adding all required features
 */
#pragma once

#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>

#include "edge.h"
// #include "random.h"

using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;

/*
Need to be able to read from a file
create a graph (ie insert nodes)
find a node(ie traversals BFS)


1) Read from file


*/
/**
 * Represents a graph; used by the GraphTools class.
 *
 */
class Graph
{
public:

    //for sure using weighted, undirected graph
    Graph();

    Graph(int numVertices);


    void insertVertex(Vertex v);                                 //insert a vertex
    void insertEdge(Vertex source, Vertex destination);         //inset a edge

    vector<Vertex> getAdjacent(Vertex source) const;            //get all adjacent vertices from source
    Vertex getStartingVertex() const;                           //
    


    vector<Vertex> getVertices() const;                         
    vector<Edge> getEdges() const;
 
    int getEdgeWeight(Vertex source, Vertex destination) const;

    Edge setEdgeWeight(Vertex source, Vertex destination, int weight);

    bool vertexExists (Vertex v) const;
    bool edgeExists(Vertex source, Vertex destination) const;


    private:

        unordered_map<Vertex, unordered_map<Vertex, Edge>> adjacency_list;          //mutable to bypass const
/*
<Vertex(intersection1), unordered_map<Vertex(intersection2), Edge>

*/








/*


    void initSnapshot(string title);

   
    void snapshot();


    void print() const;

    void savePNG(string title) const;
   
  bool assertVertexExists(Vertex v, string functionName) const;
    bool assertEdgeExists(Vertex source, Vertex destination, string functionName) const;
*/
};
