#include "graph.h"
#include <list>

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight);

Graph::Graph(){
}

//Idea: Pass in vector in which first element is the source edge, 2nd dest edge, 3rd is the edge weight, this cycle repeats until the end
//main constructor used
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


void Graph::DijkstraSSSP(int source){

    int graphsize = (int)getVertices().size();      

    vector<int> distance(graphsize, INFINITY);           //used to track distances from source, index represents node number, initialiezed to infinity
    vector<bool> visited(graphsize, false);             //used to keep track of which vertices have been processed
    vector<int> prevStep(graphsize, -1);                 //use to keep track of path to source

    prevStep.at(source) = -1;                           //path starts at the source
    distance.at(source) =0;                             //distance from source


    //iterate through all vertices in the graph and find their distances from the source vertex
    for(int i=0; i<graphsize; i++){

        int minWeight = INT32_MAX; //large number but not infinite, used to find the vertex w/smallest to process next
        int minIdx;                 //the index of the vertex to 
  
        //iterate through every vertex and select an uvisited vertex with smallest weight
        for (int v = 0; v < graphsize; v++){ 
       
            if (visited[v] == false && distance[v] <= minWeight) { //if not visited and distance from source is finite
                minWeight = distance[v]; 
                minIdx = v; 
            }
        }
        //at the end of for loop we found the next unprocessed vertex at the "edge" of visited vs unvisted nodes w/ smallest weight.
        int currV= minIdx; 
        visited[currV] = true;     //mark current vertex as visited
        //cout << "LOOP:" << i << " currV=" << currV << "\n";
        

        //iterate thru every vertex that is connected to current vertex and update its prevStep and weight if shorter path to source exists
        for(int v=0; v<graphsize; v++){
            //if v not visited and edge exist between v and currV and distance from currV to source + the edge weight of currV and V is less than distance v to src
            if(!visited[v] && edgeExists(to_string(currV),to_string(v)) && 
            distance[currV]+getEdgeWeight(to_string(currV),to_string(v)) < distance[v] ){

                prevStep[v] =currV;
                distance[v] = distance[currV] + getEdgeWeight(to_string(currV),to_string(v));
                //cout << "iloop:" << v << "\n";
            }

        }

        

        
    }


    ///Print solution: indexes represent vertex number, and the element is the distance from source in the distance vector and the element in the prevStep 
    //vector represent the previous step to which takes you back eventually to the source.

    for(int i=0; i< graphsize; i++){

        vector<int> path;
       int nextidx = prevStep.at(i);    //i=7 , nxt=4
       path.push_back(i);

        //find path
       while(nextidx != -1){

           path.push_back(nextidx);
           nextidx = prevStep.at(nextidx);
       }
        std::reverse(path.begin(), path.end()); //reverse

        string first = "Path from " + to_string(i);
        string second = " to " + to_string(source);
        string third = ": weight =" + to_string(distance.at(i)) + ", path ={";
        // cout << "Path from " << i << " to " << source << ": weight =" << distance.at(i) << ", path ={";

        path_output += first + second + third;

        for(int v:path) {
            // cout << v << " ";
            string temp = to_string(v);
            path_output += temp + " ";
            // path_output += ",";
        }



        // cout << "}\n";
        path_output += "}\n";


    }


}








vector<Vertex> Graph::getAdjacent(Vertex source) const {
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source , Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return Edge();
    Edge ret = adjacency_list[source][destination];
    return ret;
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                ret.push_back(its->second);
                seen.insert(make_pair(source,destination));
 
                
                seen.insert(make_pair(destination, source));
                
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}


int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    //removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, Edge>();
}


Vertex Graph::removeVertex(Vertex v)
{

    if (adjacency_list.find(v) != adjacency_list.end())
    {
  
        for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++){
                Vertex u = it->first;
                adjacency_list[u].erase(v); 
        }
        adjacency_list.erase(v);
        return v;
        
        
        adjacency_list.erase(v);
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination)
{
    if(adjacency_list.find(source)!= adjacency_list.end() //if source is in adjList & its dest is also in adList edge already exists
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        //edge already exist return no need to do anything return false
        return false;
    }

    if(adjacency_list.find(source)==adjacency_list.end())   //if source is not in adjList......
    {
        adjacency_list[source] = unordered_map<Vertex, Edge>(); //add it
    }
        //source vertex exists
    adjacency_list[source][destination] = Edge(source, destination);    //add the edge too 

    if(adjacency_list.find(destination)== adjacency_list.end())         //if destination Vertex is not adjList....
    {
        adjacency_list[destination] = unordered_map<Vertex, Edge>();    //add it 
    }
    adjacency_list[destination][source] = Edge(source, destination);    //and add the same edge
    
    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination)
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    adjacency_list[source].erase(destination);
    // if undirected, remove the corresponding edge

    adjacency_list[destination].erase(source);
    
    return e;
}


Edge Graph::setEdgeWeight(Vertex source, Vertex destination, int weight)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight);
    adjacency_list[source][destination] = new_edge;


    Edge new_edge_reverse(destination,source, weight);
    adjacency_list[destination][source] = new_edge_reverse;
        

    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination)== adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }


        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + destination + " -> " + source);
            return false;
        }
    
    return true;
}

void Graph::clear()
{
    adjacency_list.clear();
}


/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}





/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;

            cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

/** 
 * To print on txtfile for main
*/
string Graph::toPrint() const { 
    string output = "";
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        output += it->first + "\n";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            output += vertexColumn;

            output += "weight = " + to_string(it2->second.getWeight()) + "\n";
        }
        output += "\n";
    }
    return output;
}

/** returns string of path to main */
string Graph::getPaths() const {
    return path_output;
}



