/* References: 
 * https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search
 * https://www.geeksforgeeks.org/iterative-deepening-searchids-iterative-deepening-depth-first-searchiddfs/
 */

 /* IDDFS - Iterative Deeping Depth First Search // implements the DFS algorithm starting at the source
  * node and going through to various depths; for each iteraton, the search algorithim is restrcited to a limit
  * or a maximum depth, which it cannot search beyond
  */

// Basically, we will be implementing DFS using BFS principles

/* @Param source - the starting node
   @Param target - the node which we aim to find // determine if it exists
   @Param lastNode - the final node we search // we need to find the target node // see if it 
   exists before the last node
   @return true if the target node has been found, otherwise false
 */
bool Graph::IDDFS(int source, int target, int lastNode) { 
    for (int i = 0; i <= lastNode; i++) {
        if (IDDFSHelper(source, target, i)) {
            return true
        }
    }
}

bool Graph::IDDFSHelper(int source, int target, int limit) { 
    if (source = target) {
        return true;
    }

    if (limit <= 0) {
        return false;
    }

    for (auto i = adj[source].begin(); i != adj[source].end(); ++i)  {
        if (IDDFSHelpe(i, target, limit - 1)) {
            return true;
        }
    }
    
    return false; 
} 

void Graph::IDDFSTest() {

}