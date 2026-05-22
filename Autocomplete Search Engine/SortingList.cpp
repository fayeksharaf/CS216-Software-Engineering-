/*
 * File: SortingList.cpp
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 2
 * Author: Md Fayek Sharaf
 * Purpose: Implementation of the SortingList template class.
 *          Provides selection sort, bubble sort, merge sort, and STL sort.
 *          Each sorting algorithm (except std_sort) accepts a function pointer
 *          to define custom comparison criteria.
 */

#ifndef SORTINGLIST_CPP
#define SORTINGLIST_CPP

#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include "SortingList.h"

// Insert newitem at the end of the sequence
template <typename T>
void SortingList<T>::insert(T newitem)
{
    items.push_back(newitem);
}

// Return the number of items in the sequence
template <typename T>
int SortingList<T>::size() const
{
    return items.size();
}

// Direct access by index
template <typename T>
T& SortingList<T>::operator[](int index)
{
    return items[index];
}

// Sort in ascending order using operator "<" via STL sort
template <typename T>
void SortingList<T>::std_sort()
{
    std::sort(items.begin(), items.end());
}

// Sort using selection sort with a custom comparison function
template <typename T>
void SortingList<T>::selection_sort(int (*compare)(T T1, T T2))
{
    int min_index = 0;
    for (size_t i = 0; i < items.size() - 1; i++)
    {
        min_index = i;
        for (size_t j = i + 1; j < items.size(); j++)
        {
            if ((*compare)(items[min_index], items[j]) < 0)
                min_index = j;
        }
        if (min_index != i)
            swap(items[i], items[min_index]);
    }
}

// Sort using bubble sort with a custom comparison function
template <typename T>
void SortingList<T>::bubble_sort(int (*compare)(T T1, T T2))
{
    for (size_t i = 1; i < items.size(); i++)
    {
        for (size_t j = 0; j < items.size() - 1; j++)
        {
            if ((*compare)(items[j], items[j + 1]) < 0)
                swap(items[j], items[j + 1]);
        }
    }
}

// Sort using merge sort with a custom comparison function
template <typename T>
void SortingList<T>::merge_sort(int (*compare)(T t1, T t2))
{
    merge_sortHelper(0, items.size() - 1, (*compare));
}

// Shuffle items randomly
template <typename T>
void SortingList<T>::shuffle()
{
    for (size_t i = items.size() - 1; i > 1; i--)
    {
        size_t j = rand() % (i + 1);
        swap(items[i], items[j]);
    }
}

// Display all items in the sequence
template <typename T>
void SortingList<T>::print() const
{
    cout << "Data items in the list: " << endl;
    for (size_t i = 0; i < items.size(); i++)
        cout << items[i] << endl;
    cout << endl;
}

// Merge two sorted halves of the items vector back together
template <typename T>
void SortingList<T>::merge(int first, int mid, int last, int (*compare)(T T1, T T2))
{
    vector<T> temp(items.size());
    int first1 = first, last1 = mid;
    int first2 = mid + 1, last2 = last;
    int index = first1;

    while (first1 <= last1 && first2 <= last2)
    {
        if ((*compare)(items[first1], items[first2]) > 0)
        {
            temp[index] = items[first1];
            first1++;
        }
        else
        {
            temp[index] = items[first2];
            first2++;
        }
        index++;
    }
    while (first1 <= last1)
    {
        temp[index] = items[first1];
        first1++;
        index++;
    }
    while (first2 <= last2)
    {
        temp[index] = items[first2];
        first2++;
        index++;
    }
    for (int i = first; i <= last; i++)
        items[i] = temp[i];
}

// Recursively divide and merge sort the sequence
template <typename T>
void SortingList<T>::merge_sortHelper(int min, int max, int (*compare)(T t1, T t2))
{
    if (min < max)
    {
        int mid = (min + max) / 2;
        merge_sortHelper(min, mid, (*compare));
        merge_sortHelper(mid + 1, max, (*compare));
        merge(min, mid, max, (*compare));
    }
}

#endif  /* SORTINGLIST_CPP */
