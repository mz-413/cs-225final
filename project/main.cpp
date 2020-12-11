#include "graph.h"
#include "BFS.h"
#include <fstream>
#include <istream>
#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

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

////////////extended graph
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
void graphtest2(Graph g){

    g.print();
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
    text.open("undirected_list.txt");

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

void DijkstrasTestMenu(Graph &g){

    bool done =false;
    string selection;

    while(!done){
        cout << "\nWelcome to our interactive Dijkstras SSSP Test!";
        cout << "\n(Enter q to exit)";
        cout << "\n\nPlease select a vertex to run the algorithm on from 0 to " << g.getVertices().size()-1 << " : ";
        
        cin >> selection;
        
        if(selection !="q"){

            string temp = "-----DIJKSTRAS PATH RESULTS-----\n";

            g.DijkstraSSSP(stoi(selection));
            
            temp += g.getPaths();
    
            temp += "\n-----ADJACENCY LIST OF NODES-----\n\n";
            temp += g.toPrint();

            writeOutDijkstras(temp);
            cout << "Updated Dijkstras.txt" << endl;

        }else{

            done =true;
        }
     

    }

}


int main() {
/*
OUTLINE:
1) Read from file, 
2) load and Create graph object and output to text file, vertices, edges, and weights,
3) Do a BFS Traversal, output traversal info to txt file
4) Run Dijkstras algorithm, output information to txt file
6) Any addition test cases to ouput to screen in main;
*/
    
//Create Graph object from a modified text file,
///////////////////////////////////////////////////////////////////////////////////////////////////////
    queue<string> infileQ; 

    /*Manual load of a predefined queue uncomment line below*/
    loadQ(infileQ);//loads graph, manually 

    /*Read from a modified large dataset txt file and load that into the queue, uncomment line below*/        
    // infileQ = readFromFile(); //load from "undirected_list.txt"

    Graph PAgraph(infileQ); //create the graph object

//Test the graph
////////////////////////////////////////////////////////////////////////////////////////////////////////

    graphtest(PAgraph);         //output the graph info simple
    //graphtest2(PAgraph);    //output graph detailed

//Output into a Graph.txt, 
//////////////////////////////////////////////////////////////////////////////////////////////////////
    writeOutGraph(PAgraph);
    cout << "Updated Graph.txt" << endl;
    
    BFSTest(PAgraph);
    cout << "Updated BFS.txt" << endl;

    // to initialize? For some reason the first time this
    // is called the code does not work as intended
    PAgraph.DijkstraSSSP(6);    //0 =source
//////////////////////////////////////////////////////


/////////////////////////////////////////////////////interactive Dijkstras test
    //DijkstrasTestMenu(PAgraph);



    //landmark test
    vector<int> landmarkpath = PAgraph.Landmark(4,7,0);


return 0;
}

/** 
 * Fix readFile.cpp
 * Test cases
 * Clean
 * Explain/Fix cross edge?
*/


