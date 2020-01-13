/*
 * Actor.h
 * COMP15 Fall 2018
 * Purpose: Interface of Actor class
 * Modified by: Rosa Vitiello
 * Last modified: Nov. 15, 2018
 */

#include <iostream>
#include "LinkedList.h"

using namespace std;

#ifndef ACTOR_H_
#define ACTOR_H_

class Actor
{

public:
    // default constructor
    Actor();

    // parameterized constructor
    Actor(string a_name);

    // inserts movie into movie list;
    void add_movie(string movie);

    // determines if actor is in a given movie
    bool in_movie(string movie) const;

    // takes in an Actor as a parameter. Returns the name of a movie in which 
    // the actor object and Actor argument have appeared in together
    // if no movies in common, returns an empty string
    // if more than one, returns any common movie
    string connect(Actor a) const;

    // == overload: returns true if the name of both actors are the same,
    //              false otherwise
    friend bool operator == (const Actor &a1, const Actor &a2);

    // != overload: returns the opposite of the equal overload operator
    //              (i.e. returns true if name of actors is not the same)
    friend bool operator != (const Actor &a1, const Actor &a2);

    // << overload: prints the name of the actor
    friend ostream &operator << (ostream &out, const Actor &a1); 


private:
    string name;                  // actor name
    LinkedList<string> movieList; // list of actor's movies

};

#endif