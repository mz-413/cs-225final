/* Code For Dijkstra's Algorithm
 * This code references the lecture notes (https://docs.google.com/document/d/1Dh6uhdn4YyYZ8hTm-r2W01fDJlqV6OuJNK3PAO3BHs0/edit?usp=sharing) 
 * and handout (https://courses.engr.illinois.edu/cs225/fa2020/assets/lectures/handouts/cs225fa20-39-Dijkstra-handout.pdf) from December 2, 2020
 * Additional References: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
 */

// Within the Graph class (Graph.h)
using namespace std;

// integer pair --> may not need to use
typedef pair<int, int> iPair;

class Graph {
    // number of vertices
    int numVertices

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
        returnDistances.push_back(INF);
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