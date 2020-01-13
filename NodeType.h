/*
 * Filename: Nodetype.h
 * Contains: Interface of the template NodeType class (a node of a linked list) 
 *
 */

#ifndef NODE_TYPE_H_
#define NODE_TYPE_H_

template<class E>
struct NodeType
{
    E info;
    NodeType<E> *next;
};

#endif
