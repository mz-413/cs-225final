#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

// Referencing from the sample files
// adapted from CS 225 Final Project AMA

/** 
 * Reads a file into a string
 * @param filename The file to read from 
 * @return a string containing filename's contents
 */
string file_to_string(const string & filename);

/** 
 * Reads a file into a vector
 * @param filename The file to read from
 * @return a vector containing filename's contents
 */
vector<string> file_to_vector(const string & filename);


map<int, int> organize(vector<string> list);



