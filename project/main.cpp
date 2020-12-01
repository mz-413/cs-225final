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
    // string d_list = "temp_directed_list.txt";
    vector<string> dir_vect = file_to_vector();
    map<int, int> dir_mapped = createMapDirected(dir_vect);
    map<int, int> undir_mapped = createMapUndirected(dir_mapped);
    writeOut(undir_mapped);
    cout << "test" << endl;

    return 0;
}