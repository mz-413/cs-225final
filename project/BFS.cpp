/**
 * @file BFS.cpp
 */

#include <iterator>
#include <cmath>
#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include "graph.h"
#include "edge.h"
#include "BFS.h"

using namespace std;

/** Outline:
 * BFS Traversing method
 * 
 * Output traverse results in a txt file
 * 
 * PSEUDOCODE:
BFS(G):
 Input: Graph, G
 Output: A labeling of the edges on G as discovery and cross edges

 create a copy of graph
foreach (Vertex v : G.vertices()):
    setLabel(v, UNEXPLORED)
foreach (Edge e : G.edges()):
    setLabel(e, UNEXPLORED)
foreach (Vertex v : G.vertices()):
    if getLabel(v) == UNEXPLORED:
        BFS(G, v)
*/
BFS::BFS(Graph graph) {
    for (Vertex vertex : graph.getVertices()) { // initiates map
        pair<Vertex, bool> pair(vertex, false);
        visited_vertices.insert(pair);
    }

    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < edges.size(); i++) { // initiates map
        unexplored.push_back(edges.at(i));

        // pair<Edge, string> pair(edges.at(i), "UNEXPLORED");
        // visited_edges.insert(pair);
        // Edge e = (edges.at(i));
        // cout << e.dest << " " << e.source << " " << pair.second << endl;
    }

    for (auto it = visited_vertices.begin(); it != visited_vertices.end(); it++) {
        if ((*it).second == false) { // if not visited, traverse vertex           
            construct(graph, (*it).first);
        }
    }
}

/**
BFS(G, v):
    Queue q
    setLabel(v, VISITED)
    q.enqueue(v)
    
    while !q.empty():
        v = q.dequeue()
        foreach (Vertex w : G.adjacent(v)):
            if getLabel(w) == UNEXPLORED:
                setLabel(v, w, DISCOVERY) - mark the edges as visited
                setLabel(w, VISITED) - mark the new vertex as visited
                q.enqueue(w) - add the new vertex to visit
            elseif getLabel(v, w) == UNEXPLORED:
                setLabel(v, w, CROSS) //? Could be skipped
*/
void BFS::construct(Graph graph, Vertex vertex) {
    queue<Vertex> queue; // queue of vertices to visit
    visited_vertices[vertex] = true;
    queue.push(vertex);

    output_queue_.push(vertex); // adds start vertex to output queue

    while (!queue.empty()) {
        vertex = queue.front();
        queue.pop();
        
        // vector<Vertex> vect_vertex = graph.getAdjacent(vertex);

        for (Vertex temp_vertex : graph.getAdjacent(vertex)) {

            // Edge * edge = new Edge(temp_vertex, vertex);
            // Edge * edge2 = new Edge(vertex, temp_vertex);
            Edge edge(temp_vertex, vertex);
            Edge edge2(vertex, temp_vertex);
            
            if (visited_vertices[temp_vertex] == false) {

                bool crossed = false; // true if added to cross_vector
                // adding edges
                if (discovered.size() == 0) {
                    discovered.push_back(edge);
                } else {
                    for (auto it = discovered.begin(); it != discovered.end(); it++) {
                        if ((*it) == edge || (*it) == edge2) { //? ISSUE WITH THIS STATEMENT
                        // if (((*it).source == edge.source && (*it).dest == edge.dest)
                        //     || ((*it).source == edge.dest && (*it).dest == edge.source)) {
                            cout << __LINE__ << endl; //!
                            crossed = true;
                            cross.push_back(edge); // adds edge to cross
                            break;
                        }
                    }

                    // if (find(discovered.begin(), discovered.end(), (edge)) != discovered.end()) { // if edge is found
                    //     cout << __LINE__ << endl; //!
                    //     crossed = true;
                    //     cross.push_back(e); // adds edge to cross
                    // } else if (find(discovered.begin(), discovered.end(), (edge2)) != discovered.end()) { // if edg2 is found
                    //     cout << __LINE__ << endl; //!
                    //     crossed = true;
                    //     cross.push_back(e2); // adds edge to cross
                    // } else { // not found in discovered, add to discovered
                    //     discovered.push_back(e);
                    // }

                    if (!crossed) discovered.push_back(edge);
                }
                // removes edge from unexplored
                for (size_t i = 0; i < unexplored.size(); i++) {
                    if (unexplored.at(i) == edge || unexplored.at(i) == edge2) {
                        unexplored.erase(unexplored.begin() + i);
                        break;
                    }
                }

                visited_vertices[temp_vertex] = true; // temp_ is now visited, add to queue
                queue.push(temp_vertex);
                
                output_queue_.push(temp_vertex); // adds new vertex to output queue
            
            }
        }
    }

}


/** 
 * Initializing:
 * Add all edges to unexplored_vector
 * 
 * Have an edge
 * If edge is not in discovered_vector
 *      add edge to discovered_vector
 *      rm from unexplored_vector
 *  else if edge is in discovered
 *      add edge to cross
 *      rm from unexplored_vector
 * 
 * FOR WRITEOUT:
 * for all edges of graph
 *  
*/


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
    //! No output
    for (size_t i = 0; i < cross.size(); i++) {
        output += cross.at(i).source + " " + cross.at(i).dest + " CROSS\n";
    }
    // All unvisited should be cross edges/discovered theoretically, hence this should ouptut cross edges
    for (size_t i = 0; i < unexplored.size(); i++) {
        output += unexplored.at(i).source + " " + unexplored.at(i).dest + " CROSS EDGE\n";
        // NOTE: Should be unreachabale
    }

    // for (auto it = visited_edges.begin(); it != visited_edges.end(); it++) {

    //     // pair<Edge, string> pair(edges.at(i), "UNEXPLORED");

    //     Edge edge = (*it).first;
    //     output += edge.source + " " + edge.dest + " ";
    //     output += (*it).second;
    //     output += "\n";
    // }

    myFile << output;
    myFile.close();

    return;
}

//? Getter for test case?




