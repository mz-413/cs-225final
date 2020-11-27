#include "graph.h"

Graph::Graph();

Graph::Graph(int numVertices);


void Graph::insertVertex(Vertex v);                                 //insert a vertex
void Graph::insertEdge(Vertex source, Vertex destination);         //inset a edge

vector<Vertex> Graph::getAdjacent(Vertex source) const;            //get all adjacent vertices from source
Vertex Graph::getStartingVertex() const;                           //
    

vector<Vertex> Graph::getVertices() const;                         
vector<Edge> Graph::getEdges() const;
 
int Graph::getEdgeWeight(Vertex source, Vertex destination) const;

Edge Graph::setEdgeWeight(Vertex source, Vertex destination, int weight);

bool Graph::vertexExists (Vertex v) const;
bool Graph::edgeExists(Vertex source, Vertex destination) const;