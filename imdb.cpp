/*
 * File: imdb.cpp
 * Course: CS216 - Introduction to Software Engineering
 * Project: Project 1
 * Author: Md Fayek Sharaf
 * Purpose: Implementation of the IMDB class.
 *          Provides a movie-actor database with lookup in both directions.
 */

#include <regex>
#include "imdb.h"

using namespace std;

// Default constructor — map members initialize themselves as empty containers
IMDB::IMDB()
{
}

// Insert an actor and their movies into both maps:
//   actors_db: actor -> movies
//   movies_db: movie -> actors
void IMDB::insert_an_actor(string actorName, set<string> movieTitles)
{
    if (!isExistingActor(actorName))
        actors_db[actorName] = movieTitles;
    else
        actors_db[actorName].insert(movieTitles.begin(), movieTitles.end());

    for (auto it = movieTitles.begin(); it != movieTitles.end(); it++)
    {
        if (movies_db.find(*it) == movies_db.end())
        {
            set<string> actors;
            actors.insert(actorName);
            movies_db[*it] = actors;
        }
        else
        {
            movies_db[*it].insert(actorName);
        }
    }
}

// Insert a movie and its actors into both maps:
//   movies_db: movie -> actors
//   actors_db: actor -> movies
void IMDB::insert_a_movie(string movieTitle, set<string> actorNames)
{
    if (!isExistingMovie(movieTitle))
        movies_db[movieTitle] = actorNames;
    else
        movies_db[movieTitle].insert(actorNames.begin(), actorNames.end());

    for (auto it = actorNames.begin(); it != actorNames.end(); it++)
    {
        if (actors_db.find(*it) == actors_db.end())
        {
            set<string> movies;
            movies.insert(movieTitle);
            actors_db[*it] = movies;
        }
        else
        {
            actors_db[*it].insert(movieTitle);
        }
    }
}

// Search for a movie using movieTitle as a case-insensitive substring pattern
// Returns the first matched movie title from the database, or an empty string
string IMDB::matchExistingMovie(string movieTitle) const
{
    string matchedMovie;
    bool found = false;
    regex reg(movieTitle, regex_constants::icase);

    auto it = movies_db.begin();
    while (!found && it != movies_db.end())
    {
        if (regex_search(it->first, reg))
        {
            found = true;
            matchedMovie = it->first;
        }
        else
            it++;
    }
    return matchedMovie;
}

// Returns true if movieTitle exists in movies_db
bool IMDB::isExistingMovie(string movieTitle) const
{
    return movies_db.find(movieTitle) != movies_db.end();
}

// Returns true if actorName exists in actors_db
bool IMDB::isExistingActor(string actorName) const
{
    return actors_db.find(actorName) != actors_db.end();
}

// Returns the set of movies that actorName appears in
// Returns an empty set if actorName is not found
set<string> IMDB::find_movies_for_an_actor(string actorName) const
{
    if (isExistingActor(actorName))
        return actors_db.at(actorName);

    return set<string>();
}

// Returns the set of actors that appear in movieTitle
// Returns an empty set if movieTitle is not found
set<string> IMDB::find_actors_in_a_movie(string movieTitle) const
{
    if (isExistingMovie(movieTitle))
        return movies_db.at(movieTitle);

    return set<string>();
}
