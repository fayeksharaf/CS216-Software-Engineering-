/*
 * File: Project2.cpp
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 2
 * Author: Md Fayek Sharaf
 * Purpose: Main driver for the Autocomplete search engine.
 *          Reads a dataset of (weight, query) pairs from a file,
 *          then repeatedly prompts the user for a prefix and displays
 *          the top N matching terms in descending order by weight.
 *
 * Usage: ./Project2 <filename> <number_of_suggestions>
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"

using namespace std;

int main(int argc, char** argv)
{
    const int ARGUMENTS = 2;

    if (argc != ARGUMENTS + 1)
    {
        cout << "Usage: " << argv[0] << " <filename> <number_of_suggestions>" << endl;
        return 1;
    }

    int numOfSuggestions = stoi(argv[2]);

    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << "Cannot open the file named " << argv[1] << endl;
        return 2;
    }

    // Read (weight, query) pairs from the input file and load into Autocomplete
    Autocomplete autocomplete;
    long weight;
    string query;

    while (!infile.eof())
    {
        infile >> weight >> ws;
        getline(infile, query);
        if (query != "")
        {
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }
    }

    // Sort all terms and report how long it took
    clock_t tstart, tstop;
    tstart = clock();
    autocomplete.sort();
    tstop = clock();
    double elapsed = (double)(tstop - tstart) / CLOCKS_PER_SEC;
    cout << "Time for sorting all terms: " << elapsed << " seconds." << endl;

    string prefix;
    cout << "Please input the search query (type \"exit\" to quit): " << endl;
    getline(cin, prefix);

    while (prefix != "exit")
    {
        // Find all matches and report how long the search took
        clock_t tstart, tstop;
        tstart = clock();
        SortingList<Term> matchedTerms = autocomplete.allMatches(prefix);
        tstop = clock();
        double elapsed = (double)(tstop - tstart) / CLOCKS_PER_SEC;
        cout << "Time for searching matched terms: " << elapsed << " seconds." << endl;

        if (matchedTerms.size() == 0)
        {
            cout << "No matched query!" << endl;
        }
        else
        {
            // Display up to numOfSuggestions results
            int size = (numOfSuggestions > matchedTerms.size()) ? matchedTerms.size() : numOfSuggestions;
            for (int i = 0; i < size; i++)
                cout << matchedTerms[i] << endl;
        }

        cout << "Please input the search query (type \"exit\" to quit): " << endl;
        getline(cin, prefix);
    }

    return 0;
}
