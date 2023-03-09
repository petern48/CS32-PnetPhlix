#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>

#include "treemm.h"

const int IDLINENUMBER = 1;
const int TITLELINENUMBER = 2;
const int YEARLINENUMBER = 3;
const int DIRECTORLINENUMBER = 4;
const int ACTORLINENUMBER = 5;
const int GENRELINENUMBER = 6;
const int RATINGLINENUMBER = 7;

class Movie;

class MovieDatabase // CASE INSENSITIVE search
{
  public:
    MovieDatabase();
    ~MovieDatabase(); // Added Destructor
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
      TreeMultimap <std::string, std::vector<Movie*>> *m_tree;
        
      void parseLine(ifstream& infile, std::vector<std::string>& v);
};

#endif // MOVIEDATABASE_INCLUDED
