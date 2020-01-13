/*
 * Filename: LinkedList.h
 * Contains: Interface of the template LinkedList class 
 *
 */

#include <iostream>
#include <exception>
#include "NodeType.h"
using namespace std;

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

const int FAIL = -1;

// Exceptions
class FullList : public exception{
public:
    const char * what() const throw() {return "Oh no, the list is full!\n";}; 
};

class EmptyList : public exception{
public:
    const char * what() const throw() {return "Sad, the list is empty!\n";}
};

template<class E> class LinkedList
{
 public:

    LinkedList();
    LinkedList(const LinkedList &);
    ~LinkedList();
    LinkedList & operator =(const LinkedList &);

    //Standard linked list operations
	void insert(E);
	int get_length() const;
    bool is_empty() const;
    bool is_full() const;
    E get_value_at(int) const;

	void make_empty();             //empties the linked list
    void print(ostream &) const;   //writes the list in cout
    void delete_value_at(int);     //Removes element at given position  
    E find(E, bool &) const;       //Looks for E in the list


  private:
	NodeType<E> *head;
};

#endif
