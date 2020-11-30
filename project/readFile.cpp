#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <istream>
#include <iterator>
#include "readFile.hpp"
// #include "undirected_list.txt"
// #include "temp_directed_list.txt"


using namespace std;
// Referencing from the sample files
// TODO: Debug the code, figure out Makefile issue
//? Makefile issue with stdlib?
//? Sometime's file cannot be read due to "invalid preprocessing directive"

/** 
 * Turns the directedlist file to a vectorString
*/
vector<string> file_to_vector() {
	ifstream text;
    text.open("temp_directed_list.txt"); //! CHANGE TO OFFICIAL DIRECTED LIST FOR FINAL PRODUCT
	vector<string> out;

	if (text.is_open()) {
	    istream_iterator<string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}
    text.close();

	return out;
} 


/** Reformats the list of directed nodes to be undirected list of nodes.
 * @param list of nodes, each index reps a new line of the list ("int of start node" + " " + "int of end node")
 * @return the organized map of ints that contains the undirected list of nodes
*/
// still have to figure out how to collect the data from actual file and connect the code with the file
map<int, int> createMapDirected(vector<string> list) {
    map<int, int> directed;

    for (size_t i = 4; i < list.size(); i++) { // should start on the 4th line
        string row = list[i];
        int first = -1; // start node
        int second = -1; // end node
        istringstream iss (row);
        for (int j = 0; j < 2; j++) {
            if (first == -1) {
                iss >> first;
            } else {
                iss >> second;
            }
        }

        directed.insert(pair<int, int>(first, second));
    }

    return directed;
}

// PROBABLY WILL NEED TO EDIT
map<int, int> createMapUndirected(map<int, int> directed) {
    map<int, int> undirected;
    for (auto it = directed.begin(); it != directed.end(); it++) {
        int toCheck = undirected.find((*it).second)->first; // toCheck = first node of directed
        if (toCheck == 0) { // toCheck DNE OR == node0
            undirected.insert(pair<int, int>((*it).first, (*it).second));
        } else { // if pair alrdy exists
            continue;
        }
    }
    return undirected;
}

void writeOut(map<int, int> undirected) {
    ofstream myFile;

    // // !Find a way to clear the contents within undirected_list.txt
    myFile.open("undirected_list.txt");

    // myFile << "insert anything here to write";
    // convert int to string and writeOut in forloop
    string output = "";
    for (auto it = undirected.begin(); it != undirected.end(); it++) {
        string first = to_string((*it).first);
        string second = to_string((*it).second);
        output += first + " " + second + "\n";
    }
    myFile << output;
    myFile.close();
    return;
}



/** Documentation:
 * readFile method reads the entire txt file of the directed nodes,
 * converts the list of directed nodes into undirected nodes.
*/

/** Plan:
 * 1) convert all into a map (directedMap)
 * 2) loop through entire directedMap to created undirectedMap to create organized deduplicated map
 *      Remember: IF edge from startNode to endNode DNE, 0 is returned -- clashes with 0 node
 * 3) Create a brand new textfile
*/

/** To Work On / Questions:
 * 1) Still not too sure how to call readFile 
 * 2) Change readFile.hpp to readFile.h?
 * 3) Test cases? can't be certain if this code works the way intended (reference past map labs?)
 * 4) How to display the graph at end?
*/

/** Overall procedure:
 * 1) Read File, change the list so that it only has a list of undirected nodes
 * 2) Go through DFS traversal
 * 3) Go through the algorithms
 * 4) Display graph
 * 5) Show results and stuff on final presentation
*/
