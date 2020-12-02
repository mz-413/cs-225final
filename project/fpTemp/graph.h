#include <list>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>

using std::vector;

class Graph{

public:

    Graph();







//helper functions
    void insertNodesFromFile(); //function that reads from file to insert all nodes 
    





private:
    /*vector<std::pair<DEST,Edge/Weight>>* AdjList;

        Because our nodes have integer names we can represent them as indices and so we will use a array of pointers in which
        the index indicate which node and the the pointer will point to an array of pairs in which the first number indicates the destination node
        and the second num indicates the weight to said node.
        we will have a pointer array of size 1,088,092 and each pointer will point to array of pairs, an example is below

    	std::pair<int, int>* B[8];                      // an array of 8 pointers to int's

	    B[0] = new std::pair<int, int>[2];              // the first ptr in the array points to an array of pairs

    	B[0][0] = std::make_pair(5, 2);                 // setting a value in the array that B[0] points to

	    cout << B[0][0].first << " " << B[0][0].second << endl;

        For more informtaion reference: https://www.youtube.com/watch?v=k1wraWzqtvQ&t=1s&ab_channel=mycodeschool    @ about 9:30

    */
    

    std::pair<int,int> *AdjList[1088092];    //adjacency list implemented as a an array of pointers that point to arrays(which contain destination node and edge weight)






};l