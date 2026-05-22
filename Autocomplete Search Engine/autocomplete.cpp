/*
 * File: autocomplete.cpp
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 2
 * Author: Md Fayek Sharaf
 * Purpose: Implementation of the Autocomplete class.
 *          Sorts terms by query, uses binary search to find prefix matches,
 *          then returns results ranked in descending order by weight.
 */

#include <iostream>
#include "autocomplete.h"

// Default constructor — terms initializes as an empty SortingList
Autocomplete::Autocomplete()
{
}

// Insert a new term into the sequence
void Autocomplete::insert(Term newterm)
{
    terms.insert(newterm);
}

// Sort all terms in lexicographic order by query
void Autocomplete::sort()
{
    terms.std_sort();
}

// Recursive binary search helper
// Returns the index of any term whose query prefix-matches key, or -1 if not found
int Autocomplete::binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index)
{
    if (right_index < left_index)
        return -1;

    Term keyterm(key, 0);
    int r = key.length();
    int middle = (left_index + right_index) / 2;

    int cmp = Term::compareByPrefix(keyterm, terms[middle], r);
    if (cmp > 0)
        return binary_searchHelper(terms, key, left_index, middle - 1);
    else if (cmp < 0)
        return binary_searchHelper(terms, key, middle + 1, right_index);
    else
        return middle;
}

// Return the index of any term whose query prefix-matches the given prefix
int Autocomplete::binary_search(string prefix)
{
    return binary_searchHelper(terms, prefix, 0, terms.size() - 1);
}

// Find the full range [first, last] of terms matching the given prefix
// Calls binary_search to find one match, then expands outward in both directions
void Autocomplete::search(string key, int& firstIndex, int& lastIndex)
{
    int foundIndex = binary_search(key);
    if (foundIndex == -1)
    {
        firstIndex = -1;
        lastIndex = -1;
        return;
    }

    int r = key.length();

    int tryingFirst = foundIndex;
    while (tryingFirst >= 0 && Term::compareByPrefix(terms[tryingFirst], terms[foundIndex], r) == 0)
        tryingFirst--;

    int tryingLast = foundIndex;
    while (tryingLast < terms.size() && Term::compareByPrefix(terms[tryingLast], terms[foundIndex], r) == 0)
        tryingLast++;

    firstIndex = tryingFirst + 1;
    lastIndex  = tryingLast - 1;
}

// Return all terms matching the given prefix, sorted in descending order by weight
SortingList<Term> Autocomplete::allMatches(string prefix)
{
    SortingList<Term> matched;
    int firstIndex = 0;
    int lastIndex = 0;

    search(prefix, firstIndex, lastIndex);

    if (firstIndex == -1 || lastIndex == -1)
        return matched;

    for (int i = firstIndex; i <= lastIndex; i++)
        matched.insert(terms[i]);

    matched.merge_sort(Term::compareByWeight);
    return matched;
}

// Display all terms in the sequence
void Autocomplete::print()
{
    terms.print();
}
