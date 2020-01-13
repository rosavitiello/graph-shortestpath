/*
 * Filename: Queue.h
 * Contains: Interface for (template) queue class 
 *
 */

#include <iostream>
#include "NodeType.h"
using namespace std;

#ifndef QUEUE_H_
#define QUEUE_H_

// Exceptions
class FullQueue : public exception {
public:
  const char *what() const throw() { return "NO MEMORY LEFT. CANNOT INSERT";}
};

class EmptyQueue : public exception {
public:
  const char *what() const throw() { return "QUEUE IS EMPTY";}
};


template<class E>
class Queue
{
private:
    NodeType<E> *front;
    NodeType<E> *rear;

public:
    Queue();

    ~Queue();
    Queue(const Queue &);
    Queue & operator = (const Queue &);

    //Standard operations on queue class
    void make_empty();
    void enqueue(E);
    void dequeue(E &);
    bool is_empty() const;
    bool is_full() const;
};

#endif
