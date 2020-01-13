/*
 * Filename: Stack.h
 * Contains: Interface for template stack class 
 *
 */

#include <exception>
#include "NodeType.h"
using namespace std;


#ifndef STACK_H_
#define STACK_H_

// Exceptions
class FullStack : public exception {
public:
    const char *what() const throw() { return "NO MEMORY LEFT. CANNOT PUSH";}
    };

class EmptyStack : public exception {
public:
    const char *what() const throw() { return "OPERATION NOT ALLOWED ON AN EMPTY STACK"; } 
};


template<class E> class Stack
{
public:
    Stack();

    ~Stack();
    Stack(const Stack &);
    Stack & operator = (const Stack &);

    // Standard stack operations
    void push(E);
    void pop();
    E top() const;
    int get_size() const;

    bool is_full() const;
    bool is_empty() const;

    void make_empty();  //completely empties the stack

private:
    NodeType<E> *top_ptr;  
    int size;
};



#endif
