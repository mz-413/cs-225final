// yes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <ostream>
#include <iterator>
#include <stack>

#include "../cs225/catch/catch.hpp"
#include "../graph.h"
#include "../edge.h"
#include "../BFS.h"

using namespace std;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//////////////////////// Start of Tests ////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// helper function to load sample graph info
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
}

//
// Basic tests
//
TEST_CASE("test graph vertices", "[part=graph]") {
  queue<string> q;
  loadQ(q);
  Graph g(q);

  string result = "";
  vector<string> vertices = g.getVertices();

  //Vertices Test
  result += "Vertices = { ";
  for(size_t i =0; i< vertices.size(); i++){
      
          if(i!=0){
              result += (", " + vertices.at(i));
          }else{
              result += vertices.at(i);
          }
  }
  result += " }";

  REQUIRE(result == "Vertices = { 6, 4, 3, 2, 1, 7, 5, 0 }");
}

TEST_CASE("test graph edges", "[part=graph]") {
  queue<string> q;
  loadQ(q);
  Graph g(q);

  string result = "";
  vector<Edge> edges = g.getEdges();

  //Edge Test
  result += "Edges\n(src,dest):weight) = { ";
  for(size_t i =0; i< edges.size(); i++){
      
    if(i!=0){
        result += (", (" + edges.at(i).source + "," + edges.at(i).dest + "):" + to_string(edges.at(i).getWeight()));
    }else{
        result += ("("+ edges.at(i).source + "," + edges.at(i).dest + "):" + to_string(edges.at(i).getWeight()));
    }
  }
  result += " } ";

  REQUIRE(result == "Edges\n(src,dest):weight) = { (6,7):5, (6,4):2, (6,5):4, (4,2):6, (4,7):3, (4,5):5, (3,1):5, (3,0):3, (2,7):4, (2,1):7, (1,0):10, (5,0):7 } ");
}

//
// Traversal
//

TEST_CASE("test bfs traverse order", "[part=bfs]") {
  queue<string> q;
  loadQ(q);
  Graph g(q);
  BFS bfsGraph(g);
  queue<string> traversed = bfsGraph.getTraverseOrder();

  string result = "";
  while (!traversed.empty()) {
    result += traversed.front();
    traversed.pop();
  }

  REQUIRE(result == "05314627");
}

TEST_CASE("test bfs edge states", "[part=bfs]") {
  queue<string> q;
  loadQ(q);
  Graph g(q);
  BFS bfsGraph(g);
  vector<Edge> discov = bfsGraph.getEdgesDiscovered();
  vector<Edge> cross = bfsGraph.getEdgesCross();

  string result = "";
  for (auto it : discov) {
    result += (it.source) + " " + (it.dest) + " DISCOVERED\n";
  }
  for (auto it : cross) {
    result += (it.source) + " " + (it.dest) + " CROSS EDGE\n";
  }

  string answer = "5 0 DISCOVERED\n3 0 DISCOVERED\n1 0 DISCOVERED\n4 5 DISCOVERED\n6 5 DISCOVERED\n2 1 DISCOVERED\n7 4 DISCOVERED\n7 6 CROSS EDGE\n";
  answer += "7 2 CROSS EDGE\n1 3 CROSS EDGE\n2 4 CROSS EDGE\n4 6 CROSS EDGE\n";

  REQUIRE(result == answer);
}

//
// Algorithm - Dijkstras
//

TEST_CASE("test dijkstras simple graph (node = 0)", "[part=dijkstras]") {
  queue<string> q;
  loadQ(q);
  Graph g(q);
  g.DijkstraSSSP(0);
  g.DijkstraSSSP(0);

  string output = g.getPaths();

  REQUIRE(output == "Path from 0 to 0: weight =0, path ={0 ,}\nPath from 1 to 0: weight =8, path ={1 ,3 ,0 ,}\nPath from 2 to 0: weight =15, path ={2 ,1 ,3 ,0 ,}\nPath from 3 to 0: weight =3, path ={3 ,0 ,}\nPath from 4 to 0: weight =12, path ={4 ,5 ,0 ,}\nPath from 5 to 0: weight =7, path ={5 ,0 ,}\nPath from 6 to 0: weight =11, path ={6 ,5 ,0 ,}\nPath from 7 to 0: weight =15, path ={7 ,4 ,5 ,0 ,}\n");

}

TEST_CASE("test dijksrtas simple graph (node = 1)", "[part=dijkstras]") {
  queue<string> q;
  loadQ(q);
  Graph g(q);
  g.DijkstraSSSP(1);
  string output = g.getPaths();

  REQUIRE(output == "Path from 0 to 1: weight =8, path ={0 ,3 ,1 ,}\nPath from 1 to 1: weight =0, path ={1 ,}\nPath from 2 to 1: weight =7, path ={2 ,1 ,}\nPath from 3 to 1: weight =5, path ={3 ,1 ,}\nPath from 4 to 1: weight =13, path ={4 ,2 ,1 ,}\nPath from 5 to 1: weight =15, path ={5 ,0 ,3 ,1 ,}\nPath from 6 to 1: weight =15, path ={6 ,4 ,2 ,1 ,}\nPath from 7 to 1: weight =11, path ={7 ,2 ,1 ,}\n");
}


TEST_CASE("test dijksrtas simple graph (node = 3)", "[part=dijkstras]") {
  queue<string> q;
  loadQ(q);
  Graph g(q);
  g.DijkstraSSSP(3);
  string output = g.getPaths();

  REQUIRE(output == "Path from 0 to 3: weight =3, path ={0 ,3 ,}\nPath from 1 to 3: weight =5, path ={1 ,3 ,}\nPath from 2 to 3: weight =12, path ={2 ,1 ,3 ,}\nPath from 3 to 3: weight =0, path ={3 ,}\nPath from 4 to 3: weight =15, path ={4 ,5 ,0 ,3 ,}\nPath from 5 to 3: weight =10, path ={5 ,0 ,3 ,}\nPath from 6 to 3: weight =14, path ={6 ,5 ,0 ,3 ,}\nPath from 7 to 3: weight =16, path ={7 ,2 ,1 ,3 ,}\n");
}

TEST_CASE("test dijkstras simple graph - Adjacency List", "[part=dijkstras]") {
  queue<string> q;
  loadQ(q);
  Graph g(q);
  g.DijkstraSSSP(3);
  string output = g.toPrint();

  string answer = "6\n";
  answer += "    => 7 weight = 5\n";
  answer += "    => 4 weight = 2\n";
  answer += "    => 5 weight = 4\n\n";
  
  answer += "4\n";
  answer += "    => 2 weight = 6\n";
  answer += "    => 7 weight = 3\n";
  answer += "    => 6 weight = 2\n";
  answer += "    => 5 weight = 5\n\n";
  
  answer += "3\n";
  answer += "    => 1 weight = 5\n";
  answer += "    => 0 weight = 3\n\n";
  
  answer += "2\n";
  answer += "    => 4 weight = 6\n";
  answer += "    => 7 weight = 4\n";
  answer += "    => 1 weight = 7\n\n";
  
  answer += "1\n";
  answer += "    => 3 weight = 5\n";
  answer += "    => 2 weight = 7\n";
  answer += "    => 0 weight = 10\n\n";
  
  answer += "7\n";
  answer += "    => 2 weight = 4\n";
  answer += "    => 4 weight = 3\n";
  answer += "    => 6 weight = 5\n\n";
  
  answer += "5\n";
  answer += "    => 4 weight = 5\n";
  answer += "    => 6 weight = 4\n";
  answer += "    => 0 weight = 7\n\n";
  
  answer += "0\n";
  answer += "    => 5 weight = 7\n";
  answer += "    => 3 weight = 3\n";
  answer += "    => 1 weight = 10\n\n";

  REQUIRE(output == answer);
}

