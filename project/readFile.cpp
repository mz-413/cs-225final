#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <istream>
#include <iterator>
#include <queue>
#include "readFile.h"

using namespace std;

// Referencing from the sample files


// empty constructor
readFile::readFile(){}

readFile::readFile(string empty) {
    empty_nodes_check.clear();
    string d_list = "temp_directed_list.txt";
    vector<string> dir_vect = file_to_vector();
    vector<pair<int, int>> dir_mapped = createMap(dir_vect);
    queue<string> q = writeOut(dir_mapped); // contains the queue of string
}

/** 
 * Turns the directedlist file to a vectorString
*/
vector<string> readFile::file_to_vector() {

    ofstream outfile;
    outfile.open("roadNet-PA.txt", std::ios_base::app); // append instead of overwrite
    outfile << "\n";
    outfile << "0 1"; // adds a new line to bottom to avoid missing any nodes
    outfile.close();

	ifstream text;
    text.open("roadNet-PA.txt"); //! CHANGE TO OFFICIAL DIRECTED LIST FOR FINAL PRODUCT
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
vector<pair<int, int>> readFile::createMap(vector<string> list) {
    vector<pair<int, int>> undirected;

    for (size_t i = 0; i < 250; i++) {
        empty_nodes_check.push_back(0);
    }

    undirected.push_back(pair<int,int>(stoi(list[0]), stoi(list[1]))); // First and second entry

    for (size_t i = 2; i < list.size() - 1; i+=2) {
        int first = stoi(list[i]); // start node
        int second = stoi(list[i+1]); // end node
        bool state = false;

        if (first > 249 || second > 249) {
            continue;
        }

        empty_nodes_check.at(first) = 1;
        empty_nodes_check.at(second) = 1;

        for (size_t i = 0; i < undirected.size(); i++) {
            pair<int, int> toCheck = undirected.at(i);
            if (toCheck.second == first && toCheck.first == second) {
                state = true;
                break;
            }
        }

        if (state == false) { // toCheck DNE OR == node0
            undirected.push_back(pair<int, int>(first, second));
        } else { // if pair alrdy exists
            continue;
        }
    }

    // int first = stoi(list[list.size()]); // start node
    // cout << first << endl;
    // int second = stoi(list[list.size()]); // end node

    // directed.push_back(pair<int, int>(first, second));

    // for (auto it = directed.begin(); it != directed.end(); it++) {
    //     cout << (*it).first << " " << (*it).second << endl;
    // }

    return undirected;
}

queue<string> readFile::writeOut(vector<pair<int, int>> undirected) {
    ofstream myFile;

    // // !Find a way to clear the contents within undirected_list.txt
    myFile.open("undirected_list.txt");

    // myFile << "insert anything here to write";
    // convert int to string and writeOut in forloop
    string output = "";
    queue<string> to_return;
    int count = 0;
    for (auto it = undirected.begin(); it != undirected.end(); it++) {
        string first = to_string((*it).first);
        string second = to_string((*it).second);
        string weight = to_string(rand() % 10 + 1);
        
        if (first == "0" && second == "1") {
            count++;
        }

        if (count > 1) { // if reached to end, stop adding
            break;
        } else {
            to_return.push(first);
            to_return.push(second);
            to_return.push(weight);
            //? counter for weights
            output += first + " " + second + " " + weight + "\n";
        }
    }

    // output += "\n\n\n--------TO CHECK--------\n\n\n";
    output += "0";
    // for (size_t i = 0; i < empty_nodes_check.size(); i++) {
    //     output += to_string(i) + " " + to_string(empty_nodes_check.at(i)) + "\n";
    // }
    myFile << output;
    myFile.close();
    return to_return;
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
