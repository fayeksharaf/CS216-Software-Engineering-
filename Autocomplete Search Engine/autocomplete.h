/*
 * File: autocomplete.h
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 2
 * Author: Md Fayek Sharaf
 * Purpose: Declaration of the Autocomplete class.
 *          Given a set of Term objects, finds all terms whose query
 *          starts with a given prefix, sorted in descending order by weight.
 */

#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H

#include <string>
#include "term.h"
#include "SortingList.h"

using namespace std;

class Autocomplete
{
    public:
        // Default constructor
        Autocomplete();

        // Insert a new term into the sequence
        void insert(Term newterm);

        // Sort all terms in lexicographic order by query
        // Must be called before binary search can be applied
        void sort();

        // Return the index of a term whose query prefix-matches the given prefix
        // Uses binary search — requires the sequence to be sorted first
        int binary_search(string prefix);

        // Set first and last to the index range of all terms matching the prefix
        // Sets both to -1 if no match is found
        void search(string key, int& first, int& last);

        // Return all terms matching the given prefix, in descending order by weight
        SortingList<Term> allMatches(string prefix);

        // Display all terms in the sequence
        void print();

    private:
        SortingList<Term> terms;

        // Recursive helper for binary_search
        int binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index);
};

#endif  /* AUTOCOMPLETE_H */
