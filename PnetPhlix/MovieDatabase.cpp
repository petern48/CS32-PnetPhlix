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
    m_movieCount = 0;
}

MovieDatabase::~MovieDatabase() {
    // Delete the Movies
    for (int i = 0; i < m_movieCount; i++) {
        if (m_movies[i] != nullptr)
            delete m_movies[i];
        m_movies[i] = nullptr;
    }
}

bool MovieDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Couldn't open file " << filename << endl;
        return false;
    }

    string currLine;
    string id, title, releaseYear;
    vector<string> directors, actors, genres;
    float rating;
    Movie* movie = nullptr;
    while (true) {
        int lineCount = 1;
        id = "";
        // Read in the first 3 lines
        while (getline(infile, currLine)) {
            if (lineCount == IDLINENUMBER)
                id = currLine;
            /*
                for (int i = 0; i < currLine.size(); i++) // Lowercase the key for case insensitive search
                    id += tolower(currLine[i]);
            */
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
        // Increment m_movieCount after inserting in trees

        // Lowercase everything to insert as a key (case insensitive)
        for (int i = 0; i < id.size(); i++)
            id[i] = tolower(id[i]);

        // Insert index values into trees
        m_idTree.insert(id, m_movieCount);


        // Lowercase vector, insert into tree, and clear vector
        lowerVectorAndInsertIntoTree(actors, m_actorTree);
        lowerVectorAndInsertIntoTree(directors, m_directorTree);
        lowerVectorAndInsertIntoTree(genres, m_genreTree);
       

        m_movieCount++;

        // We should now be at the end of the Movie Record, throw away empty line
        if (!getline(infile, currLine))
            break;
    }

    return true;

}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string loweredInput;
    for (int i = 0; i < id.size(); i++) // Lowercase the key for case insensitive search
        loweredInput += tolower(id[i]);
    TreeMultimap<string, int>::Iterator it = m_idTree.find(loweredInput);
    if (it.is_valid())
        return m_movies[it.get_value()]; // Get the position of the movie and return the respective movie
    return nullptr;
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string loweredInput;
    for (int i = 0; i < director.size(); i++) // Lowercase the key for case insensitive search
        loweredInput += tolower(director[i]);
    vector<Movie*> v;
    Movie* movie;
    TreeMultimap<string, int>::Iterator it = m_directorTree.find(loweredInput);
    while (it.is_valid()) {
        movie = m_movies[it.get_value()];
        v.push_back(movie);
        it.advance();
    }
    return v;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string loweredInput;
    for (int i = 0; i < actor.size(); i++) // Lowercase the key for case insensitive search
        loweredInput += tolower(actor[i]);
    vector<Movie*> v;
    Movie* movie;
    TreeMultimap<string, int>::Iterator it = m_actorTree.find(loweredInput);
    while (it.is_valid()) {
        movie = m_movies[it.get_value()];
        v.push_back(movie);
        it.advance();
    }
    return v;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string loweredInput;
    for (int i = 0; i < genre.size(); i++) // Lowercase the key for case insensitive search
        loweredInput += tolower(genre[i]);
    vector<Movie*> v;
    Movie* movie;
    TreeMultimap<string, int>::Iterator it = m_genreTree.find(loweredInput);
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

void MovieDatabase::lowerVectorAndInsertIntoTree(vector<string>& v, TreeMultimap<string, int>& t) {
    for (int i = 0; i < v.size(); i++) {
        // Lowercase all strings in vector
        for (int j = 0; j < v[i].length(); j++)
            v[i][j] = tolower(v[i][j]);

        // Insert into tree
        t.insert(v[i], m_movieCount);
    }
    // Clear vector
    v.clear();
}