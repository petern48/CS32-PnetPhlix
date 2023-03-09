#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>

const int IDLINENUMBER = 1;
const int TITLELINENUMBER = 2;
const int YEARLINENUMBER = 3;

class Movie;

class MovieDatabase // CASE INSENSITIVE search
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;

  private:
};

#endif // MOVIEDATABASE_INCLUDED
