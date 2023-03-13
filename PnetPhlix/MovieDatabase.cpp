#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

// I added the following
#include <iostream>
#include <sstream> // To convert string to int
#include <cctype>

MovieDatabase::MovieDatabase()
{   
    m_idTree = new TreeMultimap<string, int>;
    m_actorTree = new TreeMultimap<string, int>;
    m_directorTree = new TreeMultimap<string, int>;
    m_genreTree = new TreeMultimap<string, int>;
    m_movieCount = 0;
}

MovieDatabase::~MovieDatabase() {
    delete m_idTree;
    delete m_actorTree;
    delete m_directorTree;
    delete m_genreTree;
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Couldn't open file " << filename << endl;
        return false;
    }

    string currLine, temp;
    string id, title, releaseYear;
    vector<string> directors, actors, genres;
    // int numDirectors, numActors, numGenres;
    float rating;
    Movie* movie = nullptr;
    while (true) {
        id = "";
        int lineCount = 1;

        // Read in the first 3 lines
        while (getline(infile, currLine)) {
            if (lineCount == IDLINENUMBER)
                for (int i = 0; i < currLine.size(); i++) // Lowercase the key for case insensitive search
                    id += tolower(currLine[i]);
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

        // Create Movie and push to vector
        movie = new Movie(id, title, releaseYear, directors, actors, genres, rating);
        m_movies[m_movieCount] = movie;
        // Increment count after for loops

        // Insert into trees
        m_idTree->insert(id, m_movieCount);

        for (int i = 0; i < actors.size(); i++)
            m_actorTree->insert(actors[i], m_movieCount);

        for (int i = 0; i < directors.size(); i++)
            m_directorTree->insert(directors[i], m_movieCount);

        for (int i = 0; i < genres.size(); i++)
            m_genreTree->insert(genres[i], m_movieCount);

        directors.clear();
        actors.clear();
        genres.clear();

        m_movieCount++;

        // We should now be at the end of the Movie Record, throw away empty line
        if (!getline(infile, currLine))
            break;
    }

    return true;

}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string lowerID;
    for (int i = 0; i < id.size(); i++) // Lowercase the key for case insensitive search
        lowerID += tolower(id[i]);
    TreeMultimap<string, int>::Iterator it = m_idTree->find(lowerID);
    if (it.is_valid())
        return m_movies[it.get_value()]; // Get the position of the movie and return the respective movie
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    vector<Movie*> v;
    Movie* movie;
    TreeMultimap<string, int>::Iterator it = m_directorTree->find(director);
    while (it.is_valid()) {
        movie = m_movies[it.get_value()];
        v.push_back(movie);
        it.advance();
    }
    return v;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    vector<Movie*> v;
    Movie* movie;
    TreeMultimap<string, int>::Iterator it = m_actorTree->find(actor);
    while (it.is_valid()) {
        movie = m_movies[it.get_value()];
        v.push_back(movie);
        it.advance();
    }
    return v;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    vector<Movie*> v;
    Movie* movie;
    TreeMultimap<string, int>::Iterator it = m_genreTree->find(genre);
    while (it.is_valid()) {
        movie = m_movies[it.get_value()];
        v.push_back(movie);
        it.advance();
    }
    return v;
}

void MovieDatabase::parseLine(ifstream& infile, vector<string>& v) {
    string currLine;
    char c;
    // Make into function
    // Read each word until no comma encountered
    while (infile.get(c)) {
        // Remove the comma if there is one
        if (c == ',') {
            v.push_back(currLine); // Push words to vector
            currLine = "";
        }
        else if (c == '\n') {
            v.push_back(currLine);
            return;
        }
        else
            currLine += c; 
    }
}

