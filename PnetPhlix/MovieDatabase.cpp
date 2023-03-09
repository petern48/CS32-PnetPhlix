#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

// I added the following
#include <iostream>

#include <sstream> // To convert string to int

MovieDatabase::MovieDatabase()
{
    m_tree = new TreeMultimap<string, Movie*>;
}

MovieDatabase::~MovieDatabase() {
    if (m_tree != nullptr)
        delete m_tree;
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Couldn't open file " << filename << endl;
        return false;
    }
    string currLine, temp;
    string id;
    string title;
    string releaseYear;
    vector<string> directors; // Maybe just insert as a string with commas
    vector<string> actors;
    vector<string> genres;
    // int numDirectors, numActors, numGenres;
    float rating;
    Movie* movie = nullptr;
    while (true) {

        int lineCount = 1;

        // Read in the first 3 lines
        while (getline(infile, currLine)) {
            if (lineCount == IDLINENUMBER)
                id = currLine;
            else if (lineCount == TITLELINENUMBER)
                title = currLine;
            else if (lineCount == YEARLINENUMBER) {
                releaseYear = currLine;
                break;
            }
            lineCount++;
        }
        parseLine(infile, directors);
        parseLine(infile, actors);
        parseLine(infile, genres);
        stringstream ss;
        if (getline(infile, currLine)) {
            ss << currLine;
            ss >> rating;
        }
        
        // Create Movie and push to tree
        movie = new Movie(id, title, releaseYear, directors, actors, genres, rating);

        m_tree->insert(id, movie); // UNSURE if sort by ID

        // We should now be at the end of the Movie Record
        if (!getline(infile, currLine))
            break;
    }

    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    TreeMultimap<string, Movie*>::Iterator it = m_tree->find(id);
    if (it.is_valid() && it.get_value() != nullptr)
        return it.get_value();
    return nullptr;
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

void MovieDatabase::parseLine(ifstream& infile, vector<string>& v) {
    string currLine;
    char c;
    // Make into function
    // Read each word until no comma encountered
    while (infile.get(c)) {
        // Remove the comma if there is one
        if (currLine.back() == ',') {
            v.push_back(currLine); // Push words to vector
            currLine = "";
        }
        // If no comma, we reached end of line
        else
            currLine += c;

    }
}
