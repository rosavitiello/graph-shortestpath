/*
 * SixDegrees.h
 * COMP15 Fall 2018
 * Purpose:       Interface of SixDegrees class
 * Modified by:   Rosa Vitiello
 * Last modified: Nov. 19, 2018
 */

#include <iostream>
#include "Graph.h"
#include "Actor.h"

using namespace std;

#ifndef SIXDEGREES_H_
#define SIXDEGREES_H_

class SixDegrees 
{
public:
    // default constructor for six degrees (intializes private member graph g)
    SixDegrees();

    // populates g_actors from inputFile actors.txt (hardcoded)
    // adds edges between two actors if they appeared in a movie together
    // only adds one edge of a common movie if more than one movie together
    void populate_graph();

    // prompts user for two actors, runs SixDegrees of Kevin Bacon
    void run(istream &in, ostream &out);

    // prints path between to actors (or lack of path) using BFS
    void BFS(Actor a, Actor b, ostream &out);


private:                
    Graph<Actor> g;                             // graph of actors

    // helper functions
    int get_num_vertices() const;               // gets num actors from txtfile
    void read_actor_data(Actor actors[]) const; // reads actors.txt in array
    Actor get_Actor(istream &in, ostream &out) const; // gets next valid input
};

#endif