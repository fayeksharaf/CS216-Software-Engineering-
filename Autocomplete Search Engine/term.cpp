/*
 * File: term.cpp
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 2
 * Author: Md Fayek Sharaf
 * Purpose: Implementation of the Term class.
 *          A Term represents a single autocomplete entry:
 *          a query string paired with a nonnegative integer weight.
 */

#include <iostream>
#include "term.h"

// Default constructor
Term::Term()
{
}

// Initialize a term with the given query string and weight
Term::Term(string query, long weight)
{
    this->query = query;
    this->weight = weight;
}

// Compare two terms in descending order by weight
// Returns 1 if T1 > T2, 0 if equal, -1 if T1 < T2
int Term::compareByWeight(Term T1, Term T2)
{
    if (T1.weight > T2.weight)
        return 1;
    if (T1.weight == T2.weight)
        return 0;
    return -1;
}

// Compare two terms lexicographically using only the first r characters
// Returns 1 if T1 comes before T2, 0 if equal, -1 if T1 comes after T2
int Term::compareByPrefix(Term T1, Term T2, int r)
{
    if (r < 0)
    {
        cout << "The length of the prefix should be a positive number!" << endl;
        return 2;
    }
    string T1_prefix = T1.query.substr(0, r);
    string T2_prefix = T2.query.substr(0, r);

    if (T1_prefix < T2_prefix)
        return 1;
    if (T1_prefix == T2_prefix)
        return 0;
    return -1;
}

// T1 < T2 if the query of T1 is lexicographically less than the query of T2
bool operator<(Term T1, Term T2)
{
    return T1.query < T2.query;
}

// Output format: weight TAB query
ostream& operator<<(ostream& out, const Term& t)
{
    out << t.weight << "\t" << t.query;
    return out;
}
