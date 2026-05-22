/*
 * File: imdb.h
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 1
 * Author: Md Fayek Sharaf
 * Purpose: Declaration of the IMDB class.
 *          Represents a movie-actor database using two maps:
 *            movies_db: maps a movie title to the set of actors in it
 *            actors_db: maps an actor name to the set of movies they appear in
 */

#ifndef IMDB_H
#define IMDB_H

#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class IMDB
{
    public:
        IMDB();

        // Insert a pair <actorName, set of movie titles> into the database
        void insert_an_actor(string actorName, set<string> movieTitles);

        // Insert a pair <movieTitle, set of actor names> into the database
        void insert_a_movie(string movieTitle, set<string> actorNames);

        // Match a movie title from the database using movieTitle as a substring
        // Returns the matched movie title, or an empty string if not found
        // Performs case-insensitive matching
        string matchExistingMovie(string movieTitle) const;

        // Returns true if movieTitle exists in the database
        bool isExistingMovie(string movieTitle) const;

        // Returns true if actorName exists in the database
        bool isExistingActor(string actorName) const;

        // Returns the set of movies that actorName appears in
        // Returns an empty set if actorName is not found
        set<string> find_movies_for_an_actor(string actorName) const;

        // Returns the set of actors that appear in movieTitle
        // Returns an empty set if movieTitle is not found
        set<string> find_actors_in_a_movie(string movieTitle) const;

    private:
        map<string, set<string>> movies_db;  // movie title -> set of actors
        map<string, set<string>> actors_db;  // actor name  -> set of movies
};

#endif  /* IMDB_H */
