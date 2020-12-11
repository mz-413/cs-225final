#include "graph.h"

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight);

Graph::Graph(){/*nothing*/
}

//Idea: Pass in queue in which first element is the source edge, 2nd dest edge, 3rd is the edge weight, this cycle repeats until the 
//queue is empty. Main constructor to be used
Graph::Graph(queue<string> infile){
   
    Vertex source;
    Vertex dest;
    int weight;
    total_weight = 0;

    //while queue is not empty
    while(!infile.empty()){

        //grab/remove three elements
        source = infile.front();
        infile.pop();
        dest = infile.front();
        infile.pop();
        weight = std::stoi(infile.front());

        total_weight += weight;

        infile.pop();

        //Add the the edge and set its weight;
        bool  a = insertEdge(source,dest);
        setEdgeWeight(source,dest, weight);
        
    }

}


void Graph::DijkstraSSSP(int source){

    // Renews string
    path_output = "";

    int graphsize = (int)getVertices().size();          //number of vertices in the current graph object  

    //bounds check
    if(source > graphsize-1){

        cout << "ERROR!! The inputted source vertex is outside of range!! Please choose a vertex less than than " << graphsize << "!!" << endl;
        return;
    }

    //Ddistances.clear(); //clear previous run information
    //DprevStep.clear();


    vector<int> distance(graphsize, INFINITY);           //used to track distances from source vertex, index represents node number, initialized to infinity
    vector<bool> visited(graphsize, false);              //used to keep track of which vertices have been processed
    vector<int> prevStep(graphsize, -1);                 //use to keep track of path back to source

    prevStep.at(source) = -1;                           //path starts at the source, we denote it as the "root" with a negative element
    distance.at(source) =0;                             //distance from source at the source is zero


    //iterate through all vertices in the graph and find their distances from the source vertex
    for(int i=0; i<graphsize; i++){

        int minWeight = INT32_MAX;      //large number but not infinite(important note that distance vector elements have been initialized to infinity)
                                        //used to find the vertex w/ smallest weight to process next
        int minIdx;                     //the index of the vertex to process next.
  
        //Iterate through every vertex and select an uvisited vertex with the smallest weight to source vertex
        for (int v = 0; v < graphsize; v++){ 
       
            if (visited[v] == false && distance[v] <= minWeight) { //If vertex is not visited and distance from source is finite(ie less than infinity)
                minWeight = distance[v];                            //set minWeight to the min. weight to source seen so far.
                minIdx = v;                                         //keep track of the "index" (remember index represent vertex)
            }
        }
        //At the end of forLoop we find the next unprocessed vertex at the "edge" of visited vs unvisted vertices w/ the smallest weight.
        int currV= minIdx;          //We process this vertex next
        visited[currV] = true;     //mark current the vertex as visited
      
        //Iterate thru every vertex that is connected to current vertex and update its prevStep and weight if shorter path to source V exists
        for(int v=0; v<graphsize; v++){
            
            //if vertex v is unvisited and an edge exist between vertex v and vertex currV and the distance from currV to the 
            //source + the edge weight of currV and v is less than distance[v] (which is the current best weight back to source), then update.
            if(!visited[v] && edgeExists(to_string(currV),to_string(v)) && 
            distance[currV]+getEdgeWeight(to_string(currV),to_string(v)) < distance[v] ){

                prevStep[v] =currV;                                                                //update new previous step to be the current vertex currV
                distance[v] = distance[currV] + getEdgeWeight(to_string(currV),to_string(v));      //and update the distance from v to source
            }

        }
    }

    /*  At this point we have all the information needed. Distance contains all the distances back to source from any vertex and we can use prevStep 
        to find the exact path back to source

    */

   //Iterate through each vertex
    for(int i=0; i< graphsize; i++){

        vector<int> path;                   
        int nextidx = prevStep.at(i);   //index of the next vertex to get back to source
        path.push_back(i);              //put the first vertex as the current vertex we are processing

        //while not at root, contain to load path with the steps it takes to get back to source
       while(nextidx != -1){

           path.push_back(nextidx);            
           nextidx = prevStep.at(nextidx);
       }
        //std::reverse(path.begin(), path.end());

/*
        //print if weight is more than 30k than its disconnected no path possible
        if(distance.at(i) > 30000)

        }else{


        }
*/
        //Print solution to a txt file & to cout
        string first = "Path from " + to_string(i);
        string second = " to " + to_string(source);
        string third = "";
        bool disconnected = false;
        if (distance.at(i) >= total_weight) {
            third = ": weight = INFINITE, path ={ disconnected, NO PATH EXISTS }";
            disconnected = true;
        } else {
            third = ": weight =" + to_string(distance.at(i)) + ", path ={";
        }
        // cout << "Path from " << i << " to " << source << ": weight =" << distance.at(i) << ", path = { ";

        path_output += first + second + third;

        for(int v:path) {
            // cout << v << " ";
            if (disconnected) break;
            string temp = to_string(v);
            path_output += temp + " ";
            path_output += ",";
        }



        // cout << "}\n";
        if (disconnected) {
            path_output += "\n";
        } else {
            path_output += "}\n";
        }




    }

    DprevStep = prevStep;
    Ddistances = distance;

}




/*
IDEA: call dikstras on landmark you now have the shortest paths from landmark to the source and dest and combine both paths.

*/
vector<int> Graph::Landmark(int source, int dest, int landmark){


    DijkstraSSSP(landmark); //Run Dijkstrass on the landmark and save the prevstep & distances information to the graphs object private variables
                            //DprevStep and Ddistances NOTE: TXT files will NOT be updated

    vector<int> srcToLandmark;              
    vector<int> LandmarkTodest;

    srcToLandmark.push_back(source);       //put the first vertex as the source vertex       
    int nextidx = DprevStep.at(source);   //index of the next vertex to get to landmark 
   

    //while not at root ie landmark, continue to load path with the steps it takes to get back to root (landmark)
    while(nextidx != -1){

       srcToLandmark.push_back(nextidx);            
       nextidx = DprevStep.at(nextidx);
    }

 
    nextidx = DprevStep.at(dest);               //index of the next vertex to get back to from destination vertex
    LandmarkTodest.push_back(dest);              //put the destination vertex as the first vertex in path

    //while not at root ie landmark, continue to load path with the steps it takes to get back to root (landmark) from destination
    while(nextidx != -1){

    LandmarkTodest.push_back(nextidx);            
    nextidx = DprevStep.at(nextidx);

    }


    LandmarkTodest.pop_back();  //remove the landmark element (shows up in both vectors)
       
    //load up the srcToLandmark vector with the LandmarkTodest to combine both paths into one   
    while(!LandmarkTodest.empty()){

        srcToLandmark.push_back(LandmarkTodest.back());
        LandmarkTodest.pop_back();

    }

    /*
    //print out soltion path
    cout << "\nSTD ";
    for(int i=0; i< (int)srcToLandmark.size(); i++)
        cout << srcToLandmark[i] << " ";
    */


    /*
        for weights simply add the 2 paths ie

        int Totalweight = Ddistances[source] + Ddistances[dest];
    */




        return srcToLandmark;

}
























//used to get all adjacent vertices to a given source vertex
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

//get all edges in a graph in a vector container
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

//check if vertex exists
bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

//check if edge exists
bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "");
}

//get an edge's weight
int Graph::getEdgeWeight(Vertex source, Vertex destination) const
{

    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidWeight;
    return adjacency_list[source][destination].getWeight();
}

//insert a vertex
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

//check if vertex exists with an error if not
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

//check if edges exists with an error if not
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

//clear a graph ie clear the u-map
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

