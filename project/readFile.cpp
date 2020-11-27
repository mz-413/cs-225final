#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <istream>
#include <iterator>
#include "readFile.hpp"

using namespace std;
// Referencing from the sample files

std::string file_to_string(const std::string & filename) {
	std::ifstream text(filename);
	
	std::stringstream strStream;
	if (text.is_open()) {
		strStream << text.rdbuf();
	}

	return strStream.str();
}

vector<string> file_to_vector(const std::string & filename) {
	std::ifstream text(filename);
	std::vector<std::string> out;

	if (text.is_open()) {
	    istream_iterator<string> iter(text);
		while (!text.eof()) {
			out.push_back(*iter);
			++iter;
		}
	}

	return out;
} 

/** 
 * Make unordered pairs to ordered
 * deduplicate
 * export
*/
// still have to figure out how to collect the data from actual file and connect the code with the file

map<int, int> organize(vector<string> list) {
    map<int, int> organized;

    for (int i = 4; i < list.size(); i++) { // should start on the 4th vector
        string row = list[i];
        int first = NULL; // start node
        int second = NULL; // end node
        istringstream iss (row);
        for (int j = 0; j < 2; j++) {
            if (first == NULL) {
                iss >> first;
                continue;
            } else {
                iss >> second;
            }
        }

        // organized is not altered

        // compare and check if the nodes are already connected
        if (organized.find(second) == 0) { // if startNode is not in the 

        }
            // if can find, rearrange so lower node is at first and higher node is at second
                // continiue
            // else
                // insert new node pair to organized
    }

    return organized;
}



