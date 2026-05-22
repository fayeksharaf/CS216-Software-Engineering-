/*
 * File: SortingList.h
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 2
 * Author: Md Fayek Sharaf
 * Purpose: Declaration of the SortingList template class.
 *          Stores a sequence of objects and provides multiple sorting algorithms.
 *          Accepts a function pointer as a parameter to support custom sort criteria.
 */

#ifndef SORTINGLIST_H
#define SORTINGLIST_H

#include <vector>
#include <string>

using namespace std;

template <typename T>
class SortingList
{
    public:
        // Insert newitem at the end of the sequence
        void insert(T newitem);

        // Return the number of items in the sequence
        int size() const;

        // Direct access by index
        T& operator[](int index);

        // Sort in ascending order using operator "<" via STL sort
        void std_sort();

        // Sort using selection sort with a custom comparison function
        void selection_sort(int (*compare)(T t1, T t2));

        // Sort using bubble sort with a custom comparison function
        void bubble_sort(int (*compare)(T T1, T T2));

        // Sort using merge sort with a custom comparison function
        void merge_sort(int (*compare)(T t1, T t2));

        // Shuffle items randomly
        void shuffle();

        // Display all items in the sequence
        void print() const;

    private:
        vector<T> items;

        // Merge sort helper functions
        void merge(int first, int mid, int last, int (*compare)(T t1, T t2));
        void merge_sortHelper(int min, int max, int (*compare)(T t1, T t2));
};

#endif  /* SORTINGLIST_H */

#include "SortingList.cpp"
