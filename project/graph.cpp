#include "graph.h"
#include <list>

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const int Graph::InvalidWeight = INT_MIN;
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);

Graph::Graph(){
}

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


void Graph::DijkstraSSSPpath(int source){

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


        cout << "Path from " << i << " to " << source << ": weight =" << distance.at(i) << ", path ={";

        for(int v:path)
            cout << v << " ";

        cout << "}\n";


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

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string label)
{
    if (assertEdgeExists(source, destination, __func__) == false)
        return InvalidEdge;
    Edge e = adjacency_list[source][destination];
    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination] = new_edge;


    Edge new_edge_reverse(destination,source, e.getWeight(), label);
    adjacency_list[destination][source] = new_edge_reverse;
    
    return new_edge;
}


string Graph::getEdgeLabel(Vertex source, Vertex destination) const
{
    if(assertEdgeExists(source, destination, __func__) == false)
        return InvalidLabel;
    return adjacency_list[source][destination].getLabel();
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
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination] = new_edge;


    Edge new_edge_reverse(destination,source, weight, e.getLabel());
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
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title)
{
    picNum = 0;
    picName = title;
}

/**
 * Saves a snapshot of the graph to file.
 * initSnapshot() must be run first.
 */
void Graph::snapshot()
{
    std::stringstream ss;
    ss << picNum;
    string newName = picName + ss.str();
    savePNG(newName);
    ++picNum;
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
            string edgeColumn = "edge label = \"" + it2->second.getLabel()+ "\"";
            cout << std::left << std::setw(26) << edgeColumn;

            cout << "weight = " << it2->second.getWeight();
            cout << endl;
        }
        cout << endl;
    }
}

/**
 * Saves the graph as a PNG image.
 * @param title - the filename of the PNG image
 */
void Graph::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = "images/" + title + ".dot";
    neatoFile.open(filename.c_str());

    if (!neatoFile.good())
        error("couldn't create " + filename + ".dot");

    neatoFile
        << "strict graph G {\n"
        << "\toverlap=\"false\";\n"
        << "\tdpi=\"1300\";\n"
        << "\tsep=\"1.5\";\n"
        << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"7.0\"];\n"
        << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    vector<Vertex> allv = getVertices();
    //lambda expression
    sort(allv.begin(), allv.end(), [](const Vertex& lhs, const Vertex& rhs) {
        return stoi(lhs.substr(3)) > stoi(rhs.substr(3));
    });

    int xpos1 = 100;
    int xpos2 = 100;
    int xpos, ypos;
    for (auto it : allv) {
        string current = it;
        neatoFile 
            << "\t\"" 
            << current
            << "\"";
        if (current[1] == '1') {
            ypos = 100;
            xpos = xpos1;
            xpos1 += 100;
        }
        else {
            ypos = 200;
            xpos = xpos2;
            xpos2 += 100;
        }
        neatoFile << "[pos=\""<< xpos << "," << ypos <<"\"]";
        neatoFile << ";\n";
    }

    neatoFile << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            string vertex1Text = it->first;
            string vertex2Text = it2->first;

            neatoFile << "\t\"" ;
            neatoFile << vertex1Text;
            neatoFile << "\" -- \"" ;
            neatoFile << vertex2Text;
            neatoFile << "\"";

            string edgeLabel = it2->second.getLabel();
            if (edgeLabel == "WIN") {
                neatoFile << "[color=\"blue\"]";
            } else if (edgeLabel == "LOSE") {
                neatoFile << "[color=\"red\"]";                
            } else {
                neatoFile << "[color=\"grey\"]";
            }
            if (it2->second.getWeight() != -1)
                neatoFile << "[label=\"" << it2->second.getWeight() << "\"]";
            
            neatoFile<< "[constraint = \"false\"]" << ";\n";
        }
    }

    neatoFile << "}";
    neatoFile.close();
    string command = "neato -n -Tpng " + filename + " -o " + "images/" + title
                     + ".png 2> /dev/null";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output graph saved as images/" << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }

    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}
