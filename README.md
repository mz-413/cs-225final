Final Project
Running/Testing

Note: Please run make in the project folder for any of the following to work.

To Run Test Cases:
run make test in terminal
run ./test in terminal To test any specific cases, run ./test [part=____] eg part=graph, part=bfs …
NOTE: BFS, Graph, test cases are fully functional, the other 6 test cases unfortunately are not. We ran out of time to correct those after implementing the landmark algorithm.

Testing the code:
There are 3 different ways of testing our code: Manual graph, Read from file, or Default read from file.

Manual Graph:
To create a graph of your choosing, in main.cpp at the top find “void loadQ(.....)”.  You can then push edges as string to a queue that will then be used to generate a graph following the format already specified in that function. It is IMPORTANT to add the strings in the following order: “source_vertex, destination_vertex, edge_weight”. A default graph has been preset (in void loadQ(...)) to be generated if none is specified(refer to DefaultGraph.png). In the main.cpp, if not already uncommented, uncomment line approx. 356 ( loadQ(infileQ); ) and comment line approx. 359 ( infileQ =readFromFile(); ). Save, make, and run ./finalproj.

(IV) Upon running all vertices and edges are outputted to the screen and are also saved to Graph.txt. A BFS traversal occurs and the info is outputted to BFS.txt please open txt files to verify that graph and traversal was implemented correctly. You will then be prompted via the terminal to select a vertex to run Dijkstra's Single Source Path on. Enter a vertex within the range. IMPORTANT: Because of the way we implemented our Dijkstra's algorithm and write to files, the first run will NOT work. You must run through the Dijkstra's test at least twice. After entering a second vertex check the Dijkstras.txt, it will contain the shortest path from the inputted source as well as the adjacency list with weights. Each run will overwrite and update this txt file. Continue to check vertices to verify Dijkstras is correct. If using the default graph specified in void loadQ(...), you can refer to DefaultGraph.png. Once satisfied that dijkstra's SSSP works, exit loop by entering ‘q’ in the terminal.
You will now enter the Landmark Test. Enter any random char/num to continue. You will then be prompted to enter 3 vertices, a source vertex, a destination vertex, and a landmark vertice(ie the vertex to pass through on the way to the destination). Please enter 3 valid vertices within range. After doing so, the Landmark.txt file will be updated, please open this file to view and verify that path is correct. Each loop will create a “run” in the txt file, continue to run through the landmark test loop until satisfied that our landmark algorithm is working properly. Once satisfied exit loop by entering ‘q’.

Default Read From File (IE our DATASET):
To use the dataset that we have chosen from the stanford website all that is needed is to uncomment line approx. 359 and comment line approx. 356 if it is not already done. Save, make, and run ./finalproj. NOTE: because we cut down on our data there are lots of discontinuities. Some paths to certains vertices do not exist and some vertices have no edges. 
Instructions are the same as (IV) but there is no png so it may be a little difficult to verify that BFS, Dijkstras, and Landmark are working but they indeed are. We verified our results by drawing small sub sections of our dataset graph and comparing the results from the txt files. This may prove to be difficult but we could not think of how to test our graph any other way than creating a png which we did not have time for. You may find it easier to verify results by running the Landmark test several times with many vertices. The Landmark.txt appends each run entered. You can then compare the paths from dijkstras.txt to landmark.txt to compare if indeed this information is correct. You can also compare the Graph.txt and BFS.txt to see if these edges exists and if weights are accurate. Cross analyzing the txt files proved to very effective in verifying this large dataset.

Read From File:
To read a new file of data (directed or undirected), rename your file to “roadNet-PA.txt”. Our code will only read the file with that specific name. Also keep in mind that we will already have an existing roadNet-PA.txt in our original project folder, so please be aware that our original data may be replaced or lost here. After renaming the file and importing it to the project folder, open Makefile and uncomment lines 11-13 as instructed in Makefile.
Next, run “make” in the terminal, then run “./read”. Once ./read completes, review the file undirected_list.txt as it should have been successfully updated. After reviewing the txt file, comment back lines 11-13 in Makefile using #.
Notes: Make sure the file is formatted correctly (similar to the given roadNet-PA.txt) to avoid issues, following the format below:

Source1 dest1
Source2 dest2
Source3 dest3
    :

Basically the txt file will consist of edges where the first integer is the source vertex, the second integer is the destination vertex. Separate source and destination with a single space and move to the next line after inserting the destination vertex.
Refer to (IV) to continue to testing and verification.






Understanding Our Code

Our dataset: Our dataset was chosen from the Stanford Large Dataset Collection.  It models the road networks of Pennsylvania.  In this dataset, intersections and endpoints are represented by nodes while the roads connecting these intersections or endpoints are represented by undirected edges.  This original dataset includes 1088092 nodes and 1541898 edges.  

The source for this dataset is J. Leskovec, K. Lang, A. Dasgupta, M. Mahoney. Community Structure in Large Networks: Natural Cluster Sizes and the Absence of Large Well-Defined Clusters. Internet Mathematics 6(1) 29--123, 2009.

Generating a smaller dataset: For the purposes of our project, a smaller dataset of the road networks of PA were chosen from the original dataset.  The readFile class was established for this purpose.  The dataset file “roadNet-PA.txt” was read in the function readFile::file_to_vector() and converted to a vector of strings.  readFile::createMap then takes this vector of strings and reformats the list of directed nodes to be an undirected vector containing the first 250 pairs of nodes such that no two nodes are repeated.  The function readFile::writeOut then writes out this undirected vector of nodes into the file "undirected_list.txt". 

Graph Class: The graph class serves as a helper class which provides the graph object and additional methods to aid in the implementation of our BFS traversal, Dijkstra’s algorithm, and Landmark Path algorithm. It is a subset of the graph class previously used in lab machine learning and lab flow. Because we were familiar with it we decided to to adopted this class and edit it to suit our needs.

BFS: The BFS class implements a breadth-first search algorithm for traversing the graph of the road network.  This class includes a BFS constructor, some getter functions, a function BFS::construct which implements a BFS algorithm and stores the traversed nodes in the private variable output_queue, and a function BFS::writeOut() which saves the breadth-first searched vertices visited in order and the visit state of each edge in the file "BFS.txt”. 

Dijksrtas:
Our Dijkstra's Algorithm works by using three vectors in which the index represent the vertice. For our distance vector the element represents the distance from source, for our visited vector the element represents whether a vertex has been processed yet, and the prevStep vector elements’ represent the vertex with the smallest weight to reach the source vertex. We iterate through every vertex each time and then look at each adjacent vertex and select the one with the smallest edge weight. We then update our vectors and continue this process until all vertices are processed. The end result is a distance vector with all distance to the source vertex, a prevStep vector with essentially an uptree that eventually leads back to the “root” (source). We then set the current graph object’s vector variable Ddistance and DprevStep to be used with the landmark algorithm.

Landmark Path:
Our Landmark algorithm works by essentially running our dijkstra's algorithm on the a given landmark vertex. After running, the current graph object’s vector variables Ddistance and DprevStep are correctly updated with all the information needed to determine the landmark path and the weight. We determine the path from the “source” (in this case landmark is the true source vertex and source is just the starting vertex) to the landmark and store that in a vector. We do the same for the destination vertex to the landmark. We now have 2 vectors one with the shortest path from the “source” vertex to landmark and another with the shortest path from destination to landmark. Combining these two paths and their individual weight gives us the complete landmark path and weight.






