#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>

#include "treemm.h"
#include <fstream>

const int MAXMOVIES = 40000;
const int IDLINENUMBER = 1;
const int TITLELINENUMBER = 2;
const int YEARLINENUMBER = 3;
const int DIRECTORLINENUMBER = 4;
const int ACTORLINENUMBER = 5;
const int GENRELINENUMBER = 6;
const int RATINGLINENUMBER = 7;

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    ~MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    // Case Insensitive search
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
      TreeMultimap <std::string, int> m_idTree;
      TreeMultimap <std::string, int> m_directorTree;
      TreeMultimap <std::string, int> m_actorTree;
      TreeMultimap <std::string, int> m_genreTree;

      Movie* m_movies[MAXMOVIES];
      int m_movieCount;

      void parseLine(std::ifstream& infile, std::vector<std::string>& v);
      void lowerVectorAndInsertIntoTree(std::vector<std::string>& v, TreeMultimap<std::string, int>& t);
};

#endif // MOVIEDATABASE_INCLUDED
