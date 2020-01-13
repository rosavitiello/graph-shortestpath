/*
 * Actor.cpp
 * COMP15 Fall 2018
 * Purpose: Implementation of Actor class
 * Modified by: Rosa Vitiello
 * Last modified: Nov. 15, 2018
 */

#include <iostream>
#include "Actor.h"
using namespace std;

/* ----------------------------  Constructor  --------------------------------*/

/*
 * Function: default constructor
 * Input:    nothing
 * Returns:  nothing
 * Purpose:  creates deafault instance of Actor, name is empty string
 */

Actor::Actor()
{
    name = "";
}

/*
 * Function: parameterized constructor
 * Input:    string name of actor
 * Returns:  nothing
 * Purpose:  creates instance of Actor with given string name of actor
 */
Actor::Actor(string a_name)
{
    name = a_name;
}

/* --------------------------  Public Functions ------------------------------*/

/*
 * Function: add_movie
 * Input:    string movie
 * Returns:  nothing
 * Purpose:  adds a movie to an Actor's movie LinkedList
 */
void Actor::add_movie(string movie)
{
    movieList.insert(movie);
}

/*
 * Function: in_movie
 * Input:    string movie
 * Returns:  boolean
 * Purpose:  returns whether or not an actor starred in a given movie
 */
bool Actor::in_movie(string movie) const
{
    bool found = false;

    movieList.find(movie, found); // updates found 

    return found;
}

/*
 * Function: connect
 * Input:    Actor object
 * Returns:  string movie 
 * Purpose:  returns one string movie name in common (still one when multiple 
 *           common movies). Returns empty string if no movies in common
 */
string Actor::connect(Actor a) const
{
    int length = movieList.get_length();

    for (int i = 0; i < length; i++) {
        string movie = movieList.get_value_at(i);

        if (a.in_movie(movie)) {
            return movie;
        }

    }

    return "";
}

/* ------------------------  Operator Overloads  -----------------------------*/


/*
 * Function: overload operator == 
 * Input:    address of two Actors
 * Returns:  boolean
 * Purpose:  overloads == (returns true if actor names are the same)
 */
bool operator == (const Actor &a1, const Actor &a2) 
{
    return a1.name == a2.name;
}

/*
 * Function: overload operator !=
 * Input:    address of two Actors
 * Returns:  boolean
 * Purpose:  overloads != (returns true if actor names are not the same)
 */
bool operator != (const Actor &a1, const Actor &a2)
{
    return a1.name != a2.name;
}

/*
 * Function: overload operator <<
 * Input:    address of ostream and address of Actor
 * Returns:  ostream address
 * Purpose:  overloads << to print an Actor by printing his/her/their name
 */
ostream &operator << (ostream &out, const Actor &a1)
{
    out << a1.name;
    return out;
}