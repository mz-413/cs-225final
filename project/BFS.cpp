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

    for (Edge edge : graph.getEdges()) { // initiates map
        pair<Edge, string> pair(edge, "UNEXPLORED");
        visited_edges.insert(pair);
    }

    for (auto it = visited_vertices.begin(); it != visited_vertices.end(); it++) {
        if ((*it).second == false) { // if not visited, traverse vertex
            BFS(graph, (*it).first);
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
BFS::BFS(Graph graph, Vertex vertex) {
    queue<Vertex> queue; // queue of vertices to visit
    visited_vertices[vertex] = true;
    queue.push(vertex);

    output_queue_.push(vertex); // adds start vertex to output queue

    while (!queue.empty()) {
        vertex = queue.front();
        queue.pop();
        for (Vertex temp_vertex : graph.getAdjacent(vertex)) {
            Edge edge(vertex, temp_vertex);
            if (visited_vertices[vertex] == false) {
                // pair<Vertex, Vertex> pair = pair<Vertex, Vertex>(vertex, temp_vertex);
                visited_edges[edge] = "DISCOVERY";
                visited_vertices[temp_vertex] = true; // temp_ is now visited, add to queue
                queue.push(temp_vertex);

                output_queue_.push(temp_vertex); // adds new vertex to output queue
                
            } else if (visited_edges[edge] == "UNEXPLORED") {
                visited_edges[edge] = "CROSS";
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
    while (!queue.empty()) {
        output += queue.front();
        cout << queue.front() << endl;
        output += "\n";
        queue.pop();
    }

    myFile << output;
    myFile.close();

    return;
}






