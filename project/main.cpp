#include "readFile.hpp"
#include "graph.h"
#include <fstream>
#include <istream>
#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

void loadQ(queue<string> & q){
    
    q.push(string("0")); 
    q.push(string("1"));
    q.push(string("5"));

    q.push(string("2"));
    q.push(string("1"));
    q.push(string("3"));

 
    q.push(string("1"));
    q.push(string("3"));
    q.push(string("5"));

    q.push(string("4"));
    q.push(string("3"));
    q.push(string("2"));

}
void graphtest(Graph g){

    vector<string> vertices = g.getVertices();
    vector<Edge> edges = g.getEdges();

    cout << "Vertices = {";
    for(string n: vertices)
        cout << n << ", ";

    cout << "}" << endl;

    cout << "Edges(src:dest(wieght)) = {";
    for(Edge n: edges)
        cout << n.source << ":" << n.dest << "("<<n.getWeight() <<")"<<", ";
    cout << "}" <<endl;

}

int main() {
/*
OUTLINE:
1) Read from file,
2) load and Create graph object
3) test cases outputs in main;



void test1 ();
void test2();
*/

    /** Read file of directed nodes, write the undirected nodes into "undirected_list.txt" */
    //? there is not output for queue in main but there's output in test?
    // string d_list = "temp_directed_list.txt";
    vector<string> dir_vect = file_to_vector();
    vector<pair<int, int>> dir_mapped = createMap(dir_vect);
    queue<string> q = writeOut(dir_mapped); // contains the queue of string
    


    //Read from the newly created test file and create graph using that text file
    queue<string> infileQ;
    loadQ(infileQ);//loads Q with 5 vertices

    Graph PAgraph(infileQ); //creat the graph
    graphtest(PAgraph);
    
    



    return 0;
}