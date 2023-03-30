#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"
#include "User.h"
#include "Movie.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include <unordered_map>

class UserDatabase;
class MovieDatabase;

const int DIRECTORPOINTS = 20;
const int ACTORPOINTS = 30;
const int GENREPOINTS = 1;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;

  private:
      const UserDatabase *m_ud;
      const MovieDatabase *m_md;
      std::unordered_map<std::string, int>* m_moviesRanks;

      static bool compareMR(const std::pair<Movie*, int>& p1, const std::pair<Movie*, int>& p2);
      
};

#endif // RECOMMENDER_INCLUDED
