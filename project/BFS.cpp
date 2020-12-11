/**
 * @file BFS.cpp
 */

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <stack>
#include "graph.h"
#include "edge.h"
#include "BFS.h"

using namespace std;

/** 
 * BFS Constructor
 *  Initiates and constructs the BFS traversal for given graph
*/
BFS::BFS(Graph graph) {
    for (Vertex vertex : graph.getVertices()) { // initializes vertex vector
        pair<Vertex, bool> pair(vertex, false);
        visited_vertices.insert(pair);
    }

    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < edges.size(); i++) { // initializes edge vector
        cross.push_back(edges.at(i));
    }

    for (auto it = visited_vertices.begin(); it != visited_vertices.end(); it++) {
        if ((*it).second == false) { // if not visited, traverse vertex           
            construct(graph, (*it).first);
        }
    }
}

/**
 * Constructs the BFS Traversal
*/
void BFS::construct(Graph graph, Vertex vertex) {
    queue<Vertex> queue; // queue of vertices to visit
    visited_vertices[vertex] = true;
    queue.push(vertex);

    output_queue_.push(vertex); // adds start vertex to output queue

    while (!queue.empty()) {
        vertex = queue.front();
        queue.pop();
        
        for (Vertex temp_vertex : graph.getAdjacent(vertex)) {

            Edge edge(temp_vertex, vertex);
            Edge edge2(vertex, temp_vertex);
            
            if (visited_vertices[temp_vertex] == false) {

                discovered.push_back(edge);
                
                // removes edge from cross as they are labeled as discovered
                for (size_t i = 0; i < cross.size(); i++) {
                    if (cross.at(i) == edge || cross.at(i) == edge2) {
                        cross.erase(cross.begin() + i);
                        break;
                    }
                }

                visited_vertices[temp_vertex] = true; // temp_vertex is now visited, add to queue to visit
                queue.push(temp_vertex);
                
                output_queue_.push(temp_vertex); // adds new vertex to output queue
            
            }
        }
    }

}


/** 
 * outputs output_queue_ into BFS.txt
*/
void BFS::writeOut() {

    ofstream myFile;
    myFile.open("BFS.txt");

    string output = "";
    queue<string> queue = output_queue_;
    
    output += "Vertices visited in order: \n";
    while (!queue.empty()) {
        output += queue.front();
        // cout << queue.front() << endl;
        output += "\n";
        queue.pop();
    }
    output += "\n";

    output += "Visit state of each edge: \n";
    for (size_t i = 0; i < discovered.size(); i++) {
        output += discovered.at(i).source + " " + discovered.at(i).dest + " DISCOVERED\n";
    }
    // All unvisited should be cross edges/discovered theoretically, hence this should ouptut cross edges
    for (size_t i = 0; i < cross.size(); i++) {
        output += cross.at(i).source + " " + cross.at(i).dest + " CROSS EDGE\n";
    }

    myFile << output;
    myFile.close();

    return;
}

// Getters for test cases
queue<string> BFS::getTraverseOrder() {
    return output_queue_;
}

vector<Edge> BFS::getEdgesDiscovered() {
    vector<Edge> final;
    for (auto it = discovered.begin(); it != discovered.end(); it++) {
        final.push_back(*it);
    }
    return final;
}

vector<Edge> BFS::getEdgesCross() {
    vector<Edge> final;
    for (auto it = cross.begin(); it != cross.end(); it++) {
        final.push_back(*it);
    }
    return final;
}


