/*
 * SixDegrees.cpp
 * COMP15 Fall 2018
 * Purpose:       Implementation of SixDegrees class which can run the 
                  SixDegrees simulation
 * Modified by:   Rosa Vitiello
 * Last modified: Nov. 19, 2018
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include "SixDegrees.h"
using namespace std;


/* ----------------------------  Constructor  --------------------------------*/

/*
 * Function: default constructor
 * Input:    none
 * Return:   none
 * Purpose:  initializes instance of Six Degrees, initializes graph g with
 *           vertices for every actor in actors.txt
 */
SixDegrees::SixDegrees() 
{
    int num_actors = get_num_vertices();
    g.initialize_graph(num_actors);
}

/* -------------------------  Public Functions  ------------------------------*/

/*
 * Function: populate_graph
 * Input:    none
 * Return:   none
 * Purpose:  populates graph g with information from actors.txt
 */
void SixDegrees::populate_graph() 
{
    // read in actors from actors.txt into a dynamic array
    int num_actors = get_num_vertices();
    Actor actors[num_actors];
    read_actor_data(actors);

    // populate graph
    for (int i = 0; i < num_actors; i++) {
        g.add_vertex(actors[i]);

        for (int j = 0; j < i; j++) {
            string movie = actors[i].connect(actors[j]);

            if (movie != "") {
                g.add_edge(actors[i], actors[j], movie);
                g.add_edge(actors[j], actors[i], movie);
            }
        }
    }
}

/*
 * Function: BFS
 * Input:    two actors and ostream object address
 * Return:   none
 * Purpose:  finds shortest path between a and b (using BFS algorithm) + prints 
 *           result for user
 */
void SixDegrees::BFS(Actor a, Actor b, ostream &out)
{
    // clear path and graph for a BFS
    g.clear_marks();
    g.initialize_path();

    // BFS between actor a and b (shortest path)
    Queue <Actor> primary;
    Queue <Actor> neighbors;
    Actor vertex;
    Actor item;

    bool found = false;
    primary.enqueue(a);
    while (!primary.is_empty() and !found) {
        primary.dequeue(vertex);
        g.mark_vertex(vertex);
        g.get_to_vertices(vertex, neighbors);

        while (!neighbors.is_empty() and !found) {
            neighbors.dequeue(item);

            if (!g.is_marked(item)) {
                primary.enqueue(item);
                g.update_predecessor(vertex, item);

                if (item == b) {
                    found = true;
                }
            }
        }
    }

    // print path (or no connection if no path found)
    if(a == b) { // edge case: path to itself
        out << a << " and " << b <<  " have a costar distance of 0\n";
    }
    else if (!found) {
        out << a << " and " << b << ": No connection" << endl;
    }
    else { g.report_path(out, a, b); }
}

/*
 * Function: run
 * Input:    istream and ostream object address
 * Return:   none
 * Purpose:  runs SixDegrees simulation. Takes in valid user input and prints
 *.          shortest path between the user's actor input
 */
void SixDegrees::run(istream &in, ostream &out)
{
    // put all info from inFile into graph of actors:
    populate_graph(); 

    // interaction with user (get input, report path if exists): 
    out << "Enter two actor names separated by a new line." << endl
        << "Press ctrl-D to quit" << endl;

    do {
        Actor a1 = get_Actor(in, out);
        Actor a2 = get_Actor(in, out);

        if (!in.eof()) {
            BFS(a1, a2, out);
            out << endl;
        }

    } while (!in.eof());
}

/* -------------------------  Private Functions  -----------------------------*/

/*
 * Function: get_num_vertices
 * Input:    none
 * Return:   int
 * Purpose:  gets num_vertices needed in graph to store actors from actors.txt
 */
int SixDegrees::get_num_vertices() const
{
    ifstream inFile;
    inFile.open("actors.txt");

    int num_v = 0;
    string line;
    while (getline(inFile, line)) {
        if (line == "*") // num asterisks in file = num actors = num vertices
            num_v++;
    }

    inFile.close();
    return num_v;
}

/*
 * Function: read_actor_data
 * Input:    array of Actors
 * Return:   none
 * Purpose:  puts actor data from actors.txt into an array of Actors which
 *.          will be used to populate graph g
 */
void SixDegrees::read_actor_data(Actor actors[]) const
{
    ifstream in;
    in.open("actors.txt");

    string line;
    int index = 0;

    while (getline(in, line)) {
        Actor a = Actor(line);
        bool next_actor = false; 

        // adds movies to actor
        do {
            getline(in, line);

            if (line == "*") { // no more movies to add for this actor
                next_actor = true;
            }
            else { // input is a movie to add
                a.add_movie(line);
            }

        } while (!next_actor);

        actors[index] = a;
        index++;
    }

    in.close();
}

/*
 * Function: get_Actor
 * Input:    istream and ostream object address
 * Return:   Actor
 * Purpose:  gets a valid actor from user and prints to user if not valid
 */
Actor SixDegrees::get_Actor(istream &in, ostream &out) const
{
    string a_name;
    getline(in, a_name);
    Actor a = Actor(a_name);

    while (!in.eof() and !g.is_vertex(a)) {
        out << "Sorry, " << a << " is not in the list" << endl << endl;
        getline(in, a_name);
        a = Actor(a_name);
    }

    return a;
}