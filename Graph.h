/*
 * Filename: Graph.h
 * Contains: Interface of the template Graph class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 * Modified By:   Rosa Vitiello
 * Last Modified: Nov. 17, 2018
 */

#include "Queue.h"
#include <iostream>
#include <ostream>

#ifndef GRAPH_H_
#define GRAPH_H_

// Exceptions
class FullGraph : public exception {
public:
  const char *what() const throw() { return "My graph is full";}
};

class EmptyGraph : public exception {
public:
  const char *what() const throw() { return "My graph is empty";}
};

const string NULL_EDGE = "";
const int NULL_PRED = -1;

// wrapper functions
template<class Vertex>
int index_is(Vertex *vertices, Vertex v);

template<class Vertex>
class Graph
{
public:
    //Constructor functions
    Graph();
    Graph(int);

    //Destructor
    ~Graph();

    //Copy Constructor
    Graph(const Graph<Vertex> &);

    // Assignment Overload
    Graph &operator = (const Graph<Vertex> &);

    // Functions needed to modify the graph
    void initialize_graph(int);         //allocates space for vertices
    void add_vertex(Vertex);            //adds a single vertex to the graph
    void add_edge(Vertex, Vertex, string); //adds an edge to the graph

    void print_matrix(ostream &) const; //reports the edges of the graph

    // Helper functions for implementing BFS and DFS
    bool is_vertex(Vertex) const;                        //checks if exists
    void get_to_vertices(Vertex, Queue<Vertex> &) const; //enqueues neighbors
    void clear_marks();                                  //clears all marks
    void mark_vertex(Vertex);                            //marks a vertex
    bool is_marked(Vertex) const;                        //checks if marked
    void initialize_path();                              //clears path info
    void update_predecessor(Vertex, Vertex);             //stores predecessor
    void report_path(ostream &, Vertex, Vertex) const;   //reports path

    string get_edge(Vertex, Vertex) const;               //gets edge between
                                                         //vertices

private:
    int num_vertices;       // number of vertices of the graph
    Vertex *vertices;       // stores label of vertices, if any
    string **edges;         // weighted 2-D array to store edges 


    int *path;              // array used to store a path
    int curr_vertex;        // variable to track current vertex in DFS
    bool *marks;            // 2-D array of vertices to 

    void delete_graph();                // deletes graph and frees mem
    void copy(const Graph<Vertex> &);   // make this graph a copy of another 
                                        // graph

};

#endif


