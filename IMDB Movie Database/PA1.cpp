/*
 * File: PA1.cpp
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 1
 * Author: Md Fayek Sharaf
 * Purpose: Main driver for the IMDB database application.
 *          Reads actor/movie data from a file, then lets the user search by:
 *            Option 1 - Find actors in one or both of two movies (union, intersection, symmetric difference)
 *            Option 2 - Find all co-actors for a given actor name
 */

#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <algorithm>
#include <map>
#include <sstream>
#include "imdb.h"

using namespace std;

void analyzeMovies(const IMDB& imdb);
void analyzeCoActors(const IMDB& imdb);

int main(int argc, char* argv[])
{
    const int COMM_NUM = 2;

    if (argc != COMM_NUM)
    {
        cout << "Warning: need exactly " << COMM_NUM - 1 << " command line argument." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1;
    }

    ifstream in_file;
    in_file.open(argv[COMM_NUM - 1]);

    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[COMM_NUM - 1] << "!" << endl;
        return 2;
    }

    // Read data line by line — each line format: ActorName; movie1; movie2; ... ; movieN;
    IMDB cs216_imdb;

    while (!in_file.eof())
    {
        string line;
        getline(in_file, line);
        string actorName, movieTitle;

        if (line.length() != 0)
        {
            istringstream iss(line);
            getline(iss, actorName, ';');
            iss >> ws;

            set<string> movies;
            while (getline(iss, movieTitle, ';'))
            {
                movies.insert(movieTitle);
                iss >> ws;
            }
            cs216_imdb.insert_an_actor(actorName, movies);
        }
    }
    in_file.close();

    int option;
    while (true)
    {
        bool validInput = true;
        cout << "This application stores information about Actors and their Movies, please choose your option (Enter Q or q to quit):" << endl;
        cout << "1. Actors in Movies" << endl;
        cout << "2. Actors and co-actors" << endl;
        cin >> option;

        if (cin.fail())
        {
            string input_to_check;
            cin.clear();
            cin >> input_to_check;
            if (input_to_check == "Q" || input_to_check == "q")
                break;
            else
            {
                cout << "Expecting a number as the option!" << endl;
                validInput = false;
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (validInput)
        {
            switch (option)
            {
                case 1: analyzeMovies(cs216_imdb);
                        break;
                case 2: analyzeCoActors(cs216_imdb);
                        break;
                default:
                        cout << "Invalid option number!" << endl;
            }
        }
    }
    cout << "Thank you for using my program, bye..." << endl;
    return 0;
}

/*
 * Asks the user to input two movie titles, finds them in the database,
 * then lets the user repeatedly choose a set operation:
 *   A - union (all actors in either movie)
 *   C - intersection (actors in both movies)
 *   O - symmetric difference (actors in only one movie)
 */
void analyzeMovies(const IMDB& imdb)
{
    string movie1, movie2;
    cout << "Please input the first movie title: ";
    getline(cin, movie1);
    cout << "Please input the second movie title: ";
    getline(cin, movie2);

    string matchedMovie1 = imdb.matchExistingMovie(movie1);
    string matchedMovie2 = imdb.matchExistingMovie(movie2);

    bool notValid = false;
    if (matchedMovie1.length() == 0)
    {
        cout << "\" " << movie1 << " \"" << " is not a VALID movie title!" << endl;
        notValid = true;
    }
    if (matchedMovie2.length() == 0)
    {
        cout << "\" " << movie2 << " \"" << " is not a VALID movie title!" << endl;
        notValid = true;
    }
    if (notValid)
        return;

    if (imdb.isExistingMovie(matchedMovie1) && imdb.isExistingMovie(matchedMovie2))
    {
        cout << "Your input matches the following two movies: " << endl;
        cout << matchedMovie1 << endl;
        cout << matchedMovie2 << endl;
        cout << "Both movies are in the database, Please Continue...." << endl;

        string choice;
        while (true)
        {
            cout << "Please input your menu option (enter Q or q to quit)" << endl;
            cout << "A -- to print all the actors in either of the two movies." << endl;
            cout << "C -- to print all the common actors in both of the movies." << endl;
            cout << "O -- to print all the actors who are in only one movie, but not in both." << endl;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == "Q" || choice == "q")
                break;

            if (choice == "A" || choice == "a")
            {
                // Union: all actors in either movie
                set<string> all = imdb.find_actors_in_a_movie(matchedMovie1);
                set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(matchedMovie2);
                for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++)
                    all.insert(*i);

                cout << "All the actors in either of the two movies:" << endl;
                for (auto i = all.begin(); i != all.end(); i++)
                    cout << *i << endl;
            }
            else if (choice == "C" || choice == "c")
            {
                // Intersection: actors in both movies
                set<string> actors_in_movie1 = imdb.find_actors_in_a_movie(matchedMovie1);
                set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(matchedMovie2);
                set<string> actors_in_common;

                for (const string& actor : actors_in_movie1)
                {
                    if (actors_in_movie2.count(actor) > 0)
                        actors_in_common.insert(actor);
                }

                cout << "Common actors in both movies:" << endl;
                for (const string& actor : actors_in_common)
                    cout << actor << endl;
            }
            else if (choice == "O" || choice == "o")
            {
                // Symmetric difference: actors in exactly one of the two movies
                set<string> actors_in_movie1 = imdb.find_actors_in_a_movie(matchedMovie1);
                set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(matchedMovie2);
                set<string> only_in_one;

                for (const string& actor : actors_in_movie1)
                {
                    if (actors_in_movie2.count(actor) == 0)
                        only_in_one.insert(actor);
                }
                for (const string& actor : actors_in_movie2)
                {
                    if (actors_in_movie1.count(actor) == 0)
                        only_in_one.insert(actor);
                }

                cout << "Actors only in one of the two movies:" << endl;
                for (const string& actor : only_in_one)
                    cout << actor << endl;
            }
            else
            {
                cout << "Invalid option." << endl;
            }
        }
    }
    else
    {
        cout << "isExistingMovie function is not correct!!!" << endl;
    }
}

/*
 * Asks the user for an actor name, then prints all of that actor's
 * co-actors grouped by movie.
 */
void analyzeCoActors(const IMDB& imdb)
{
    string actor_name;
    cout << "Finding the co-actors of the actor by typing his/her name: ";
    getline(cin, actor_name);

    if (!imdb.isExistingActor(actor_name))
    {
        cout << "The actor name you entered is not in the database." << endl;
        return;
    }

    set<string> movies_of_actor = imdb.find_movies_for_an_actor(actor_name);
    for (auto im = movies_of_actor.begin(); im != movies_of_actor.end(); im++)
    {
        cout << "The co-actors of " << actor_name << " in the movie \"" << *im << "\" are: " << endl;
        set<string> coactors = imdb.find_actors_in_a_movie(*im);
        for (auto ia = coactors.begin(); ia != coactors.end(); ia++)
        {
            if (*ia == actor_name)
                continue;
            cout << *ia << endl;
        }
        cout << "***********************************" << endl;
    }
}
