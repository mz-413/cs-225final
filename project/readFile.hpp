#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <queue>

using namespace std;

// Referencing from the sample files
// adapted from CS 225 Final Project AMA

/** 
 * Reads a file into a vector
 * @return a vector containing filename's contents
 */
vector<string> file_to_vector();

/** 
 * Creates directed map
*/
vector<pair<int, int>> createMap(vector<string> list);

/** Output:
 * Overwrite a new textfile to be the list of undirected nodes
*/
queue<string> writeOut(vector<pair<int, int>> undirected);




