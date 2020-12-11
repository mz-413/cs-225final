/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <map>
#include <stack>
#include "graph.h"
#include "edge.h"

using namespace std;

/**
 * A breadth-first ImageTraversal.
 *      BFS implementation.
 * Derived from base class ImageTraversal
 */
class BFS {
public:
    // Constructor to create the private variables for keeping track of results 
    BFS(Graph graph);
    
    // Method to construct the BFS traversal given graph and vertex
    void construct(Graph graph, Vertex vertex);

    // Prints the BFS traversal results to BFS.txt
    void writeOut();

    /** FOR TEST CASES */
    queue<string> getTraverseOrder();
    vector<Edge> getEdgesDiscovered();
    vector<Edge> getEdgesCross();

private:
    map<Vertex, bool> visited_vertices; // map of visited vertices - to keep track of visited state; true = visited
    map<Edge, string> visited_edges; // vector of visited edges - to keep track of visited state of edges
    queue<string> output_queue_; // final queue that keeps track of traversed nodes

    vector<Edge> discovered; // edges in this vector will be labeled as discovered
    vector<Edge> cross; // edges in this vector will be labeled as cross
    // Note: All edges are either discovered or crossing edges
    
};
