/* Code For Dijkstra's Algorithm
 * This code references the lecture notes (https://docs.google.com/document/d/1Dh6uhdn4YyYZ8hTm-r2W01fDJlqV6OuJNK3PAO3BHs0/edit?usp=sharing) 
 * and handout (https://courses.engr.illinois.edu/cs225/fa2020/assets/lectures/handouts/cs225fa20-39-Dijkstra-handout.pdf) from December 2, 2020
 * Additional References: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
 */
#include "graph.h"


// Within the Graph class (Graph.h)
using namespace std;

// integer pair --> may not need to use
typedef pair<int, int> iPair;

class Graph {
    // number of vertices
    int numVertices;

    // for every edge in the graph, store the vertex and weight pair
    list<pair<int, int>> *allVertices; 

    public:
    // Graph constructor to create a Graph object with "numVertices" number of vertices
    Graph(int num);

    // addEdge fuction to add an edge from point (u, v) with weight w
    void addEdge(int u, int v, int w);

    // Dijkstra's shortest path algorithm which returns a vector of distances from each vertex in the graph
    vector<int> DijkstrasSSSP(int s);

};

// Within the Graph class (Graph.cpp)

Graph::Graph(int num) { 
    numVertices = num;
    allVertices = new list<iPair> [numVertices]; 
}

void Graph::addEdge(int u, int v, int w) { 
    /* for every point of (u, v) with weight w:
     *     (1) make a pair of (v, w) and add this pair at index u
     *     (2) make a pair of (u, w) and add this pair at index v
     */ 
    adj[u].push_back(make_pair(v, w)); 
    adj[v].push_back(make_pair(u, w)); 
}

vector<int> Graph::DijkstrasSSSP(int s) {
    // establish the source vertex
    int theSource = s;

    // (1) Create a vector of size "numVertices" to hold the distances of each vertex
    vector<int> returnDistances;

    // (2) Initialize the distance at each vertex as infinity
    for (int i = 0; i < returnDistances.size(); i++) {
        returnDistances.push_back(INT32_MAX);
    }

    // (3) Create a Min-Heap priority_queue which takes in the following arguments:
        // a. the datatype (pair<int,int>)
        // b. the comparator (greater<pair<int,int>> is used as a default to find the smaller value b/c in a Min-Heap 
        // the parent node value is smaller than or equal to children node value)
    priority_queue<iPair, vector <iPair>, greater<iPair>> myQ;

    // make a pair at the source
    myQ.push(make_pair(0, theSource));

    // the distance from the source the source is 0
    dist[theSource] = 0;

    // for as long as the priority_queue isn't empty
    while (theQ.size() != 0) {
        // store second element of the top most object
        int current = theQ.top().second;
        // remove the top most object
        theQ.pop();

        // iterate through the current object's adjacent objects
        list< pair<int, int> >::iterator iter;

        for (iter = allVertices[current].begin(); iter != allVertices[current].end(); ++iter) {
            // find and store an adjacent vertex current and the weight 
            int currentAdj = (*i).first; 
            int adjWeight = (*i).second;
            int compareDist = dist[current] + adjWeight;
  
            if (compareDist < dist[currentAdj]) { 
                dist[currentAdj] = compareDist; 
                pq.push(make_pair(dist[currentAdj], currentAdj)); 
            } 
        }
    }

    return returnDistances; 
}




//Our Working graph implementation dijsktras, attempt one, works but no path with priority queue
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Idea: Pass in vector in which first element is the source edge, 2nd dest edge, 3rd is the edge weight, this cycle repeats until the end
//with this creat the graph
Graph::Graph(queue<string> infile){
   
    Vertex source;
    Vertex dest;
    int weight;

    //while queue is not empty
    while(!infile.empty()){

        //grab/remove three elements
        source = infile.front();
        infile.pop();
        dest = infile.front();
        infile.pop();
        weight = std::stoi(infile.front());
        infile.pop();


        //Add the 2 vertices to adjacency List, no need will be added with insertedge, possible missing edges if done this way
        //insertVertex(source);
        //insertVertex(dest);
        
        //Add the the edge and set its weight;
        bool  a = insertEdge(source,dest);
        setEdgeWeight(source,dest, weight);
        

    }

}



//Our first Dijkstrsa algorithm, works but does not output path correctly due to priority queue
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> Graph::DijkstrasSSSP(int source) {
    // establish the source vertex
    int theSource = source;
    
    // (1) Create a vector of to size of graph to hold the distances of each vertex
    //index represents vertex, element is the distance(weight)
    vector<int> dist(getVertices().size(), INT32_MAX);  //distances from source
    vector<bool> visited(getVertices().size(),false);    //used to see if we have visited a node
    vector<Edge> shortestpath;
    

    // (3) Create a Min-Heap priority_queue which takes in the following arguments:
        // a. the datatype (pair<int,int>)
        // b. the comparator (greater<pair<int,int>> is used as a default to find the smaller value b/c in a Min-Heap 
        // the parent node value is smaller than or equal to children node value)
    std::priority_queue<pair<int,int>, vector <pair<int,int>>, std::greater<pair<int,int>>> myQ;

    // make a pair at the source
    myQ.push(make_pair(0, theSource));

    // the distance from the source the source is 0
    dist[theSource] = 0;
    //visited.at(0) =true;
    
    int count=1;
    // for as long as the priority_queue isn't empty
    while (!myQ.empty()) {
        // store second element of the top most object
        int currV = myQ.top().second;   //= to the current vertex
        int currMinEdge = INT32_MAX;    //the smallest adj path 
        Edge temp;
        // remove the top most object
        //cout<< "loop("<<count<<") " << "current vertex being processed:" <<currV<< endl;
        myQ.pop();

        // iterate through the current object's adjacent objects
        for (auto it = adjacency_list[std::to_string(currV)].begin(); it != adjacency_list[std::to_string(currV)].end(); it++) {
            
            //store the current adjacent vertex
            int currAdjV = std::stoi((*it).first);  //current adj vertex

            if(visited.at(currAdjV))    //if adjV was already processed skip to next one.
                continue;

            //cout << "innerloop adjvertex:" << currAdjV << endl;
            int adjWeight = (*it).second.getWeight(); // the adj vertex edge weight
            int compareDist = dist[currV] + adjWeight;  //weight from source vertex
  
            if (compareDist < dist[currAdjV]) { 
                dist[currAdjV] = compareDist; 
                myQ.push(make_pair(dist[currAdjV], currAdjV)); 
                //cout << currAdjV << "pushed to queue" << endl;
            } 

            if(adjWeight < currMinEdge && visited.at(currAdjV) == false){

                currMinEdge =adjWeight;
                temp = getEdge(std::to_string(currV),std::to_string(currAdjV));
                
            }      
                
            
        }
        visited.at(currV) = true;

        if(temp.source != "")
            shortestpath.push_back(temp);

        /*    
        if(count ==9){
            cout << "\ncurrV: " << currV<<" " << visited[currV] << endl;
            visited[7] = true;

        }else if(count==10){
            cout << "\ncurrV: " << currV<<" " << visited[currV] << endl;
            visited[7] = true;

        }else if(count <8){
            visited[currV] = true;

        }

        //visited[currV] = true;
        int j = std::stoi(temp.dest);
        
        if(visited.at(j) != true){
            shortestpath.push_back(temp);
    
        }
    

        */
    count++;
    }

    cout << "shortest path: ";
    for(Edge e: shortestpath)
        cout << e.source<< ":" << e.dest << " ";
    
    cout << endl;
    
    return dist;
 
}