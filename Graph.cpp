/*
 * Filename: Graph.cpp
 * Contains: Implementation of the template Graph class 
 * Part of: Homework 5 assignment "Graph Traversal" for Comp 15 Fall 2018
 *
 * Modified by: Rosa Vitiello
 * Last modified: Nov. 17, 2018
 * 
 */

#include <iostream>
#include "Graph.h"
#include "Stack.h"
#include "Actor.h"
using namespace std;

/*
 * Function: destructor ~Graph
 * Input:    none
 * Returns:  none
 * Purpose:  frees any dynamically allocated memory from the heap
 */
template<class Vertex>
Graph<Vertex>::~Graph()
{
    delete_graph();
}

/*
 * Function: delete_graph
 * Input:    none
 * Returns:  none
 * Purpose:  helper function for Big Three. Empties graph and frees any 
 *           dynamically allocated from the heap
 */
template<class Vertex>
void Graph<Vertex>::delete_graph()
{
    // delete 1-D Arrays
    delete [] vertices;
    delete [] path;
    delete [] marks;

    // delete 2-D Arrays
    for (int i = 0; i < num_vertices; i++) {
        delete [] edges[i];
    }
    delete [] edges;

    // update all to NULL (not really necessary but in case)
    vertices = NULL;
    path = NULL;
    marks = NULL;
    edges = NULL;
    curr_vertex = 0;
    num_vertices = 0;
}

/*
 * Function: copy constructor
 * Input:    address of graph
 * Returns:  none
 * Purpose:  makes a copy of a graph into this newly allocated graph object 
 */
template<class Vertex>
Graph<Vertex>::Graph(const Graph<Vertex> &source)
{
    // deep copy source into this graph
    copy(source);

}

/*
 * Function: copy
 * Input:    address of graph
 * Returns:  none
 * Purpose:  makes a copy of a given graph into this graph
 */
template<class Vertex>
void Graph<Vertex>::copy(const Graph<Vertex> &source)
{
    initialize_graph(source.num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        // copy 1-D arrays
        vertices[i] = source.vertices[i]; 
        path[i] = source.path[i];
        marks[i] = source.marks[i];

        // copy 2-D array
        for (int j = 0; j < num_vertices; j++) {
            edges[i][j] = source.edges[i][j];
        }
    }
}

/*
 * Function: assignment operator
 * Input:    address of graph
 * Returns:  graph object class
 * Purpose:  makes a copy of a graph into another graph object 
 */
template<class Vertex>
Graph<Vertex> & Graph<Vertex>::operator = (const Graph<Vertex> &source)
{
    if (this != &source) { // check self-assignment
        delete_graph();

        copy(source);
    }

    return *this;
}


/*
 * Function: constructor
 * Parameters: none
 * Returns: nothing
 * Does: default constructor. Initializes with zero vertices
 */ 
template<class Vertex>
Graph<Vertex>::Graph()
{
    curr_vertex = 0;
    edges = NULL;
    path = NULL;
    vertices = NULL;
    marks = NULL;
}

/*
 * Function: parametrized constructor
 * Parameters: integer (size of graph)
 * Returns: nothing
 * Does: default constructor. Initializes with num_v vertices
 */
template<class Vertex>
Graph<Vertex>::Graph(int num_v)
{
    initialize_graph(num_v);
}

/*
 * Function: initialize_graph
 * Input: integer, number of vertices
 * Returns: void
 * Does: dynamically allocates all memory
 *       for a graph of num_v vertices 
 *       without any vertices
 *       and prepares all DFS,BFS variables
 */ 
template<class Vertex>
void Graph<Vertex>::initialize_graph(int num_v)
{
    curr_vertex = 0;
    num_vertices = num_v;
    vertices = new Vertex[num_vertices];
    marks = new bool[num_vertices];
    path = new int[num_vertices];

    edges = new string*[num_vertices];
    for (int i = 0; i < num_vertices; i++)
        edges[i] = new string[num_vertices];

    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
        path[i] = NULL_PRED;
        for (int j = 0; j < num_vertices; j++)
            edges[i][j] = NULL_EDGE;
    }
}

/*
 * Function: add_vertex
 * Parameters: Vertex, by value
 * Returns: void
 * Does: Add a new vertex to the end of the 2d array
 *      Initializes every from/to edge to be NULL
 */ 
template<class Vertex>
void Graph<Vertex>::add_vertex(Vertex v)
{
     vertices[curr_vertex] = v;
     for (int i = 0; i < num_vertices; i++)
     {
         edges[curr_vertex][i] = NULL_EDGE;
         edges[i][curr_vertex] = NULL_EDGE;
     }
     curr_vertex++;
 }

/*
 * Function: add_edge
 * Parameters: Two vertices, and string (weight)
 * Returns: void
 * Does: Adds an edge between the two vertices and 
 *       assigns their weight equal to the given integer
 *       (in case the edge did not exist) 
 */ 
 template<class Vertex>
 void Graph<Vertex>::add_edge(Vertex f, Vertex t, string weight)
 {
     int row;
     int col;

     row = index_is(vertices, f);
     col = index_is(vertices, t);
     if (edges[row][col] == NULL_EDGE)
         edges[row][col] = weight;
 }


/*
 * Function: print_matrix
 * Parameters: ostream
 * Returns: void
 * Does: Prints the 2d adjacency matrix of the graph
 */
template <class Vertex>
void Graph<Vertex>::print_matrix(ostream & out) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
            if (edges[i][j] == "") {
                out << "-1" << " ";
            }
            else { out << edges[i][j] << " "; }
        out << endl;
    }
}


/*
 * Function: clear_marks
 * Parameters: none
 * Returns: none
 * Does: sets all the marks to be false
 *      For algorithms that need to mark vertices (BFS, DFS)
 */ 
template<class Vertex>
void Graph<Vertex>::clear_marks()
{
    for (int i = 0; i < num_vertices; i++)
    {
        marks[i] = false;
    }
}

/*
 * Function: initialize_path
 * Parameters: none
 * Returns: none
 * Does: sets every value in the predecessor path to be NULL edge
 */ 
template<class Vertex>
void Graph<Vertex>::initialize_path()
{
    for (int i = 0; i < num_vertices; i++)
        path[i] = NULL_PRED;
}

/*
 * Function: update_predecessor
 * Parameters: Two vertices
 * Returns: None
 * Does: sets pred as the predecessor of curr in the path
 *       (in case that curr did not have any predecessor)
 *       Nothing otherwise.
 */ 
template<class Vertex>
void Graph<Vertex>::update_predecessor(Vertex pred, Vertex curr)
{
    int pred_index, curr_index;
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == pred)
            pred_index = i;
        if (vertices[i] == curr)
            curr_index = i;
    }
    if (path[curr_index] == NULL_PRED)
        path[curr_index] = pred_index;
}

/*
 * Function: report_path
 * Parameters: ostream to print, start and end vertices
 * Returns: none
 * Does: finds path from start to end and prints it
 *       uses the information stored on predecessor path 
 */ 
template<class Vertex>
void Graph<Vertex>::report_path(ostream &out, Vertex start, Vertex end) const
{
    Stack<Vertex> s;

    int index = index_is(vertices, end);
    s.push(vertices[index]);

    int co_dist = 0;

    bool done = false;
    while (!done)
    {
        index = path[index];
        if (vertices[index] == start)
            done = true;
        s.push(vertices[index]);
        co_dist++;
    }

    cout << start << " and " << end <<  " have a costar distance of " 
         << co_dist << endl;

    while (!s.is_empty())
    {
        Vertex v1 = s.top();
        s.pop();

        if (!s.is_empty()) {
            Vertex v2 = s.top();
            string movie = get_edge(v1, v2);
            out << v1 << " was in " << movie << " with " << v2 << endl;
        }
    }
}

/*
 * Function: mark_vertex
 * Parameters: Vertex
 * Returns: none
 * Does: sets the mark of the given vertex to true
 */ 
template<class Vertex>
void Graph<Vertex>::mark_vertex(Vertex v)
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            marks[i] = true;
    }
}

/*
 * Function: is_marked
 * Parameters: Vertex
 * Returns: bool
 * Does: returns true if the vertex is marked
 *       false otherwise
 */ 
template<class Vertex>
bool Graph<Vertex>::is_marked(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return marks[i];
    }
    return false;
}

/*
 * Function: is_vertex
 * Parameters: vertex
 * Returns: bool
 * Does: returns true if vertex exists in the graph,
 *       false otherwise.
 */ 
template <class Vertex>
bool Graph<Vertex>::is_vertex(Vertex v) const
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (vertices[i] == v)
            return true;
    }
    return false;
}

/*
 * Function: get_to_vertices
 * Parameters: Vertex, queue of vertices by reference
 * Returns: void
 * Does: Finds all neighbors of the the given vertex
 *       enqueues all of its neighbors to the queue
 */ 
 template<class Vertex>
 void Graph<Vertex>::get_to_vertices(Vertex v, Queue<Vertex> &adj) const
 {
    int from;
    int to;
    from = index_is(vertices, v);
    for (to = 0; to < num_vertices; to++)
        if (edges[from][to] != NULL_EDGE)
            if (vertices[to] != vertices[from])
                   adj.enqueue(vertices[to]);
}

/*
 * Function: get_edge
 * Input:    two Vertices
 * Returns:  string
 * Purpose:  returns the weight of the edge between the two given vertices
 *           (empty string if no edge exists)
 */
template <class Vertex>
string Graph<Vertex>::get_edge(Vertex v1, Vertex v2) const
{
    int row = index_is(vertices, v1);
    int col = index_is(vertices, v2);

    return edges[row][col];
}

/*
 * Function: index_is
 * Parameters: array of vertices, Vertex
 * Returns: integer
 * Does: Finds the target vertex in the list of vertices
 *       returns the index of v
 */
template<class Vertex>
int index_is(Vertex *vertices, Vertex v)
{
    int index = 0;
    while (!(v == vertices[index]))
        index++;
    return index;
}

template class Graph<int>;
template class Graph<char>;
template class Graph<string>;
template class Graph<Actor>;

