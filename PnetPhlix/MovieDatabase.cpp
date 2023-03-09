#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

// I added the following
#include <iostream>
#include <fstream>

MovieDatabase::MovieDatabase()
{
    // Replace this line with correct code.
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Couldn't open file " << filename << endl;
        return false;
    }

    string currLine;
    string id;
    string title;
    string releaseYear;
    vector<string> directors; // Maybe just insert as a string with commas
    vector<string> actors;
    vector<string> genres;
    int rating, numDirectors, numActors, numGenres;

    int lineCount = 1;

    while (getline(infile, currLine)) {
        if (lineCount == IDLINENUMBER)
            id = currLine;
        else if (lineCount == TITLELINENUMBER)
            title = currLine;
        else if (lineCount == YEARLINENUMBER)
            releaseYear = currLine;
        // CONT
    }


    return false;  // Replace this line with correct code.
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    return nullptr;  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    return vector<Movie*>();  // Replace this line with correct code.
}
