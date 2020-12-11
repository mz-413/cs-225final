#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <queue>

using namespace std;

/** 
 * Referencing from the sample files from CS 225 Final Project AMA
*/
class readFile {
public:
    /** Empty Constructor */
    readFile();
    /** Constructor to read and output file */
    readFile(string unused);

    /** 
     * Reads the given file "roadNet-PA.txt"
     * @return a vector containing filename's contents
     */
    vector<string> file_to_vector();

    /** 
     * Creates a vector pair from list of string
    */
    vector<pair<int, int>> createVector(vector<string> list);

    /** 
     * Prints the filtered out list of nodes and weights to undirected_list.txt
    */
    void writeOut(vector<pair<int, int>> undirected);

private:
    /** 
     * NOTE: CURRENTLY NOT USED IN readFile.cpp
     * For testing - to check for any floating nodes 
     *  nodes that are not connected to any other nodes after reducing to 250 nodes 
     *  If node has been visited, index of vector(node) = 1. 
     *  If floating, vector(node) = 0
    */
    vector<int> empty_nodes_check;
};



