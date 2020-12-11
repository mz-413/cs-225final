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

/** 
 * Referencing from the sample files of CS225 Final Project
*/

/**
 * empty constructor
*/
readFile::readFile(){}

/**
 * Constructor that constructs and writes the file
*/
readFile::readFile(string unused) {
    string d_list = "directed_list.txt";
    vector<string> dir_vect = file_to_vector();
    vector<pair<int, int>> dir_mapped = createVector(dir_vect);
    writeOut(dir_mapped);
}

/** 
 * Turns the directed list of nodes file ("roadNet-PA.txt") to a vector<String>
 *  Remember to match formatting of roadNet-PA.txt for successful reads
 * @return vector<string> of final nodes
*/
vector<string> readFile::file_to_vector() {

    ofstream outfile;
    outfile.open("roadNet-PA.txt", std::ios_base::app); // append instead of overwrite to avoid bugs
    outfile << "\n";

    // add a new line to bottom to avoid missing any nodes
    // will not cause duplication as 0,1 is a pair of visited nodes, will be ignored later on the code
    outfile << "0 1"; 

    outfile.close();

    // reads file.txt and pushes nodes to vector
	ifstream text;
    text.open("roadNet-PA.txt");
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
 *  Cuts the list from 3,000,000+ nodes to 0-249 nodes 
 * @param list each index reps a new line of the nodes to insert ("source" + " " + "dest")
 * @return vector of pairs of nodes (source , dest)
*/
vector<pair<int, int>> readFile::createVector(vector<string> list) {
    vector<pair<int, int>> undirected;

    // push first and second entry to undirected vector 
    undirected.push_back(pair<int,int>(stoi(list[0]), stoi(list[1])));

    // loop through entire list 
    for (size_t i = 2; i < list.size() - 1; i+=2) {
        int first = stoi(list[i]); // source node
        int second = stoi(list[i+1]); // dest node
        bool duplicate = false; // true if pair of edge already exists

        if (first > 249 || second > 249) {
            continue;
        }

        // filters list of duplicating edges (process of turning list of directed nodes to undirected list)
        for (size_t i = 0; i < undirected.size(); i++) {
            pair<int, int> toCheck = undirected.at(i);
            if (toCheck.second == first && toCheck.first == second) {
                duplicate = true;
                break;
            }
        }

        // checks for duplicates; pushback if no dupes found
        if (duplicate == false) { 
            undirected.push_back(pair<int, int>(first, second));
        } else {
            continue;
        }
    }

    return undirected;
}

/** 
 * Outputs the results into undirected_list.txt
 * @param undirected vector of deduplicated edges
*/
void readFile::writeOut(vector<pair<int, int>> undirected) {
    ofstream myFile;
    myFile.open("undirected_list.txt");

    string output = ""; // To print to undirected_list.txt
    queue<string> to_return;
    int count = 0;

    // convert the nodes to strings, add randomized weights, push all to queue
    for (auto it = undirected.begin(); it != undirected.end(); it++) {
        string first = to_string((*it).first);
        string second = to_string((*it).second);
        string weight = to_string(rand() % 10 + 1);
        
        // count++ if we have reached edge 0,1 pair.
            // Implemented to avoid deduplication error when originally reading file
        if (first == "0" && second == "1") {
            count++;
        }

        if (count > 1) {
            // stop adding as we have added all meaningful nodes.
            break;
        } else {
            to_return.push(first);
            to_return.push(second);
            to_return.push(weight);
            output += first + " " + second + " " + weight + "\n";
        }
    }

    // To avoid file reading issues that may exist for future methods
    output += "0";
    
    // Print output of edges and edge weights to undireected_list.txt
    myFile << output;
    myFile.close();
}