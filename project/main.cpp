#include "graph.h"
#include "BFS.h"
#include <fstream>
#include <istream>
#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

//void BFStest()
//void LandmarkTest()
void loadQ(queue<string> & q){
    
    q.push(string("0"));    //src
    q.push(string("1"));    //dest
    q.push(string("10"));   //weight

    q.push(string("1"));
    q.push(string("2"));
    q.push(string("7"));
 
    q.push(string("0"));
    q.push(string("3"));
    q.push(string("3"));

    q.push(string("1"));
    q.push(string("3"));
    q.push(string("5"));

    q.push(string("0"));
    q.push(string("5"));
    q.push(string("7"));

    q.push(string("5"));
    q.push(string("4"));
    q.push(string("5"));

    q.push(string("5"));
    q.push(string("6"));
    q.push(string("4"));

    q.push(string("6"));
    q.push(string("4"));
    q.push(string("2"));
    
    q.push(string("6"));
    q.push(string("7"));
    q.push(string("5"));

    q.push(string("4"));
    q.push(string("7"));
    q.push(string("3"));

    q.push(string("7"));
    q.push(string("2"));
    q.push(string("4"));

    q.push(string("4"));
    q.push(string("2"));
    q.push(string("6"));

////////////pt2 graph
  /*  q.push(string("6"));
    q.push(string("10"));
    q.push(string("1"));

    q.push(string("7"));
    q.push(string("9"));
    q.push(string("3"));

    q.push(string("9"));
    q.push(string("8"));
    q.push(string("8"));

    q.push(string("10"));
    q.push(string("9"));
    q.push(string("1"));

    q.push(string("10"));
    q.push(string("11"));
    q.push(string("3"));


    q.push(string("10"));
    q.push(string("12"));
    q.push(string("2"));

    q.push(string("11"));
    q.push(string("12"));
    q.push(string("6"));
*/
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
    cout << "\nEdges\n(src,dest):weight) = { ";
    for(size_t i =0; i< edges.size(); i++){
        
            if(i!=0){
                cout << ", " << "("<<edges.at(i).source << "," << edges.at(i).dest << "):" << edges.at(i).getWeight();
            }else{
                cout << "("<<edges.at(i).source << "," << edges.at(i).dest << "):" << edges.at(i).getWeight();
            }
    }
    cout << " }\n" << endl;

}
void BFSTest(Graph g) {
    BFS graph(g);
    graph.writeOut();
}

/** 
 * Reads undirected_list.txt
 * Returns queue<string> of nodes & weights
*/
queue<string> readFromFile() {

	ifstream text;
    text.open("temp_undirected_list.txt");

	queue<string> out;

	if (text.is_open()) {
	    istream_iterator<string> iter(text);
		while (!text.eof()) {
			out.push(*iter);
			++iter;
		}
	}

    text.close();

	return out;
} 

void  writeOutGraph(Graph g) {

    ofstream myFile;
    myFile.open("Graph.txt");

    string output = "";
    // vertices
    // edge + weight

    vector<string> vertices = g.getVertices();
    vector<Edge> edges = g.getEdges();

    //Vertices Test
    output += "\nVertices = { ";
    for(size_t i =0; i< vertices.size(); i++){
        
            if(i!=0){
                output+= ", " + vertices.at(i);
            }else{
                output+= vertices.at(i);
            }
    }
    output += " }\n" ;

    output += "\nEdges\n(src,dest):weight) = { ";
    for(size_t i =0; i< edges.size(); i++){
        
            if(i!=0){
                output += ", (" + edges.at(i).source + "," + edges.at(i).dest + "):" + to_string(edges.at(i).getWeight());
            }else{
                output += "(" + edges.at(i).source + "," + edges.at(i).dest + "):" + to_string(edges.at(i).getWeight());
            }
    }
    output += " }\n";

    myFile << output;
    myFile.close();

    return;
}

void  writeOutDijkstras(string output) {

    ofstream myFile;
    myFile.open("Dijkstras.txt");

    myFile << output;
    myFile.close();

    return;
}


int main() {
/*
OUTLINE:
1) Read from file, 
2) load and Create graph object and output to text file, vertices, edeges, weights,
3) Do a BFS Traversal, output traversal info to txt file
4) Run Dijkstras algorithm, output information to txt file
5) Run xxxxx algorithm, ouptut information to txt file
6) Any addition test cases to ouput to screen in main;


*/
    /** Read file of directed nodes, write the undirected nodes into "undirected_list.txt" */
    //? there is not output for queue in main but there's output in test?
   /* // string d_list = "temp_directed_list.txt";
    vector<string> dir_vect = file_to_vector();
    vector<pair<int, int>> dir_mapped = createMap(dir_vect);
    queue<string> q = writeOut(dir_mapped); // contains the queue of string
    */
    

    //Manual load of a predefined queue;
    //queue<string> infileQ;
    //loadQ(infileQ);//loads graph, manually 

    //Queue Read from the newly created test file and create graph using that text file
    queue<string> infileQ = readFromFile(); //load from "   "

    Graph PAgraph(infileQ); //create the graph
    graphtest(PAgraph);     //output the graph info

    // Output into a Graph.txt
    writeOutGraph(PAgraph);
    cout << "Updated Graph.txt" << endl;
    
    BFSTest(PAgraph);
    cout << "Updated BFS.txt" << endl;

    PAgraph.DijkstraSSSP(6);    //0 =source
    
    string temp = "Dijkstra results: \n";

    temp += PAgraph.getPaths();
    // PAgraph.print();
    temp += "\n-----PATH NODES WENT THROUGH-----\n\n";
    temp += PAgraph.toPrint();

    // Output into a Dijkstras.txt
    writeOutDijkstras(temp);
    cout << "Updated Dijkstras.txt" << endl;



    return 0;
}

/** 
 * Fix readFile.cpp
 * Test cases
 * Clean
 * Explain/Fix cross edge?
*/


