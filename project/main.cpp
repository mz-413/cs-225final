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

    q.push(string("3"));
    q.push(string("4"));
    q.push(string("2"));


    

}
void graphtest(Graph g){

    vector<string> vertices = g.getVertices();
    vector<Edge> edges = g.getEdges();

    //Vertices Test
    cout << "\nVertices = { ";
    for(size_t i =0; i< vertices.size(); i++){
        
            if(i!=0){
                cout << ", " << vertices.at(i);
            }else{
                cout << vertices.at(i);
            }
    }
    cout << " }" << endl;


    //Edge Test
    cout << "\nEdges (src,dest):weight) = { ";
    for(size_t i =0; i< edges.size(); i++){
        
            if(i!=0){
                cout << ", " << "("<<edges.at(i).source << "," << edges.at(i).dest << "):" << edges.at(i).getWeight();
            }else{
                cout << "("<<edges.at(i).source << "," << edges.at(i).dest << "):" << edges.at(i).getWeight();
            }
    }
    cout << " }" << endl;

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
    /*vector<string> dir_vect = file_to_vector();
    vector<pair<int, int>> dir_mapped = createMap(dir_vect);
    queue<string> q = writeOut(dir_mapped); // contains the queue of string
    */


    //Read from the newly created test file and create graph using that text file
    queue<string> infileQ;
    loadQ(infileQ);//loads Q with 5 vertices, 4 egdes

    Graph PAgraph(infileQ); //create the graph
    graphtest(PAgraph);     //output the graph info
    
    



    return 0;
}