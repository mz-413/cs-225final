/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <map>
#include "graph.h"
#include "edge.h"

using namespace std;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS {
public:
    // Constructors create the private variable output_queue_
    BFS(Graph graph);
    BFS(Graph graph, Vertex vertex);

    void writeOut();

private:
    // Graph graph_;
    map<Vertex, bool> visited_vertices; // map of visited vertices - to keep track of visited state; true = visited
    map<Edge, string> visited_edges; // vector of visited edges - to keep track of visited state of edges
    queue<string> output_queue_; // final queue that keeps track of traversed nodes
};


/** Outline:
 * BFS Traversing method
 * 
 * Output traverse results in a txt file
 * 
*/

//? setEdgeLabel? - For our purpose label = discovery, edge etc.