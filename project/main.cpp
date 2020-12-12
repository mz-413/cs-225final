#include "graph.h"
#include "BFS.h"
#include <fstream>
#include <istream>
#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

/** 
 * Loads a sample smaller graph for testing purposes
*/
void loadQ(queue<string> & q){
    
    q.push(string("0"));    //source vertex
    q.push(string("1"));    //dest vertex
    q.push(string("10"));   //edge weight

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

/** 
 * Tests the graph and prints results to terminal
*/
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

/** 
 * Prints results of BFS traversal to BFS.txt
*/
void BFSTest(Graph g) {
    BFS graph(g);
    graph.writeOut();
}

/** 
 * Reads undirected_list.txt and returns the queue of the nodes and weights
 * @return src & dest & weights to create the graph 
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

/** 
 * Outputs the graph results (edges and vertices) to Graph.txt file
*/
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

/** 
 * Outputs Dijkstras algorithm results to Dijkstras.txt file
*/
void  writeOutDijkstras(string output) {

    ofstream myFile;
    myFile.open("Dijkstras.txt");

    myFile << output;
    myFile.close();

    return;
}

/** 
 * Outputs Landmark algorithm results to Landmark.txt file
*/
void writeOutLandmark(string output) {
    ofstream myFile;
    myFile.open("Landmark.txt");

    myFile << output;
    myFile.close();   
}

/** 
 * Creates an interactive testing menu in the terminal to test Dijkstras algorithm
 * Results foe each test are shown on Dijstras.txt
*/
void DijkstrasTestMenu(Graph &g){

    bool done =false;
    string selection;
    int count=1;

    while(!done){
        cout << "\n\n\n\nWelcome to our interactive Dijkstras SSSP Test!";
        cout << "\n===================================================";
        cout << "\n(Enter 'q' to quit) ";

        if(count ==1)
            cout <<"NOTE: First run will not work, you must run at least twice.";
        
        cout << "\n\nPlease select a vertex to run the algorithm on from 0 to " << g.getVertices().size()-1 << " : ";
        
        cin >> selection;
        cout << "\nSaved to txt file!!";
        
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
     
    count++;
    }

}

/** 
 * Creates an interactive testing menu in the terminal to test Landmark algorithm
 * Results foe each test are shown on Landmark.txt
*/
void LandmarkTestMenu(Graph &g){

    bool done =false;
    string selection;
    string source;
    string dest;
    string landmark;
    int count=0;
    string output = "______LANDMARK RUNS______";

    while(!done){
        cout << "\n\n\n\n\nWelcome to our interactive Landmark Test!";
        cout <<"\n================================================";
        cout << "\n(Enter 'q' to quit, or any key to continue):";
        cin >> selection;

        if(selection != "q"){

            cout << "\nPlease select 3 vertices to run the algorithm on from 0 to " << g.getVertices().size()-1 << ".";
            cout << "\nPlease select a source vertex: ";
            cin >> source;
            cout << "Please select a destination vertex: ";
            cin >> dest;
            cout << "Please select the landmark vertex: ";
            cin >> landmark;

            vector<int> result = g.Landmark(stoi(source),stoi(dest),stoi(landmark));

            string run = "\nRun #" + to_string(count);
            string path = " Path from " + source + " to " + dest + " through " + landmark + ":  weight = ";
            int distance = g.Ddistances[stoi(source)] + g.Ddistances[stoi(dest)];
            string dist = "";
            bool disconnected = false;
            if (distance > 2500) {
                dist = "DNE";
                disconnected = true;
            } else {
                dist = to_string(distance);
            }

            cout << "\nRun #" << count << " Path from " << source << " to " << dest << " through "<< landmark << ": " << " weight = ";
            cout << g.Ddistances[stoi(source)] +g.Ddistances[stoi(dest)] << ", path ={ ";

            output += run + path + dist + ", path ={ ";

            if (disconnected) {
                output += "DNE ";
            } else {
                for(int v:result){
                    cout << v << " ";
                    output += to_string(v);
                    output += " ";
                }
            }

            cout << "}";
            cout << "\nSaved to Landmark.txt!! Please open file to view more information.";

            output += "}";

            writeOutLandmark(output);

        }else{


            done =true;
        }

    count++;
    }
    
}

void Exit(){

    cout << "\n\n\n\nThank you for testing our program and helping as with our final project this has been";
    cout << "\na very rewarding and great experience, we all have learned alot through the process!!";
    cout << "\nHave a great winter break, thanks again take care! :)\n\n\n\n";

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
    //infileQ = readFromFile(); //load from "undirected_list.txt"

    Graph PAgraph(infileQ); //create the graph object

//Test the graph
////////////////////////////////////////////////////////////////////////////////////////////////////////

    graphtest(PAgraph);         //output the graph info simple
    //graphtest2(PAgraph);    //output graph detailed

//Output into a Graph.txt, 
//////////////////////////////////////////////////////////////////////////////////////////////////////
    writeOutGraph(PAgraph);
    cout << "Updated Graph.txt open file to view graph info." << endl;
    
    BFSTest(PAgraph);
    cout << "Updated BFS.txt open file to view BFS traversal." << endl;

    // to initialize? For some reason the first time this
    // is called the code does not work as intended
    // PAgraph.DijkstraSSSP(6);    //0 =source
//////////////////////////////////////////////////////


/////////////////////////////////////////////////////interactive Dijkstras test
    DijkstrasTestMenu(PAgraph); //no output, just to file only.
    LandmarkTestMenu(PAgraph);

    
    //vector<int> landmarkpath = PAgraph.Landmark(4,7,0);



    Exit();
    return 0;
}



