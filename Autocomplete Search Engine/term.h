/*
 * File: term.h
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 2
 * Author: Md Fayek Sharaf
 * Purpose: Declaration of the Term class.
 *          A Term represents a single autocomplete entry:
 *          a query string paired with a nonnegative integer weight.
 */

#ifndef TERM_H
#define TERM_H

#include <string>

using namespace std;

class Term
{
    public:
        // Default constructor
        Term();

        // Initialize a term with the given query string and weight
        Term(string query, long weight);

        // Compare two terms in descending order by weight
        // Returns  1 if T1 > T2 by weight
        // Returns  0 if equal weight
        // Returns -1 if T1 < T2 by weight
        static int compareByWeight(Term T1, Term T2);

        // Compare two terms in lexicographic order using only the first r characters
        // Returns  1 if T1 comes before T2
        // Returns  0 if first r characters are equal
        // Returns -1 if T1 comes after T2
        static int compareByPrefix(Term T1, Term T2, int r);

        // T1 < T2 if the query of T1 is lexicographically less than the query of T2
        friend bool operator<(Term T1, Term T2);

        // Output format: weight TAB query
        friend ostream& operator<<(ostream& out, const Term& t);

        // Autocomplete needs direct access to Term's private members
        friend class Autocomplete;

    private:
        string query;
        long weight;
};

#endif  /* TERM_H */
