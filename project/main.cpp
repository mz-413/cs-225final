#include "readFile.hpp"
#include "temp_directed_list.txt"
#include <fstream>
#include <istream>
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]){
/*
OUTLINE:
1) Read from file,
2) load and Create graph object
3) test cases outputs in main;



void test1 ();
void test2();

*/
    /** Read file of directed nodes, write the undirected nodes into "undirected_list.txt" */
    string d_list = "temp_directed_list.txt";
    vector<string> dir_vect = file_to_vector(d_list);
    map<int, int> dir_mapped = createMapDirected(dir_vect);
    map<int, int> undir_mapped = createMapUndirected(dir_mapped);
    writeOut(undir_mapped);






}