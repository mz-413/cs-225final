#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

// Referencing from the sample files
// adapted from CS 225 Final Project AMA

/** 
 * Reads a file into a vector
//  * @param filename The file to read from
 * @return a vector containing filename's contents
 */
vector<string> file_to_vector();

/** 
 * Creates directed map
*/
vector<pair<int, int>> createMapDirected(vector<string> list);

/**
 * Creates undirected map
*/
vector<pair<int, int>> createMapUndirected(vector<pair<int, int>> directed);

/** Output:
 * Overwrite a new textfile to be the list of undirected nodes
*/
void writeOut(vector<pair<int, int>> undirected);




