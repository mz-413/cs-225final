#include "readFile.hpp"
#include <fstream>
#include <istream>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
/*
OUTLINE:
1) Read from file,
2) load and Create graph object
3) test cases outputs in main;



void test1 ();
void test2();

*/
    /** Read file of directed nodes, write the undirected nodes into "undirected_list.txt" */
    //? there is not output for queue in main but there's output in test?
    // string d_list = "temp_directed_list.txt";
    vector<string> dir_vect = file_to_vector();
    vector<pair<int, int>> dir_mapped = createMap(dir_vect);
    queue<string> queue = writeOut(dir_mapped); // contains the queue of string
    
    

    return 0;
}