/**
 * @file edge.h
 * Definition and (minimal) implementation of an edge class.
 */

#pragma once

#include <string>
#include <limits.h>

using std::string;

typedef string Vertex;
/*
Edge: 
-source and destination intersection
-weight = distance between 2 nodes ? How about the number of nodes it connects to = weight


*/


/**
 * Represents an edge in a graph; used by the Graph class.
 *
 * @author Sean Massung
 * @date Spring 2012
 */
class Edge
{
  public:
    Vertex source; /**< The source of the edge **/
    Vertex dest; /**< The destination of the edge **/



    /**
     * Parameter constructor for weighted graphs.
     * @param u - one vertex the edge is connected to
     * @param v - the other vertex it is connected to
     * @param w - the weight of the edge
     */
    Edge(Vertex u, Vertex v, int w)
        : source(u), dest(v), weight(w)
    { /* nothing */
    }

    /**
     * Default constructor.
     */
    Edge() : source(""), dest(""), weight(-1)
    { /* nothing */
    }

    /**
     * Compares two Edges.
     * operator< is defined so Edges can be sorted with std::sort.
     * @param other - the edge to compare with
     * @return whether the current edge is less than the parameter
     */
    bool operator<(const Edge& other) const
    {
        return weight < other.weight;
    }


    /**
     * Gets edge weight.
     */
    int getWeight() const
    {
        return this->weight;
    }

    /**
     * Compares two edges' source and dest.
     * @param other - the edge to compare with
     */
    bool operator==(Edge& other) const
    {
        if (this->source != other.source)
            return false;
        if (this->dest != other.dest)
            return false;
        return true;
    }
private:
    int weight; /**< The edge weight (if in a weighed graph) **/

};
