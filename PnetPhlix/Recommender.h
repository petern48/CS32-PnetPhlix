#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"
#include "MovieDatabase.h"
#include "UserDatabase.h"
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
      //TreeMultimap<std::string, MovieAndRank> *m_moviesRanks;
      std::unordered_map<std::string, int>* m_moviesRanks;

      static bool compareMR(const std::pair<Movie*, int>& p1, const std::pair<Movie*, int>& p2);

      /*
      struct Heap {
      private:
          MovieAndRank maxHeap[MAXMOVIES];
          int count = 0;
      public:
          int getRootLoc() { return 0; }
          int leftChildLoc(int i) { return(2 * i + 1); }
          int rightChildLoc(int i) { return(2 * i + 2); }
          int parentLoc(int i) { return((i - 1) / 2); }
          int getRank(int i) { return maxHeap[i].compatibility_score; }
          int getSize() { return count; }
          int addNode(MovieAndRank v) { 
              maxHeap[count] = v; 
              count++; 
              return count - 1; // Returns pos of Node
          }
          int swapWithParent(int curr, int parent) {
              MovieAndRank temp = maxHeap[curr];
              maxHeap[curr] = maxHeap[parent];
              maxHeap[parent] = temp;
              return parent;
          } // Return position of curr

          void addVal(MovieAndRank m) {
              // If empty, create new root
              if (getSize() == 0) {
                  addNode(m);
                  return;
              }
              int pos = addNode(m);
              while (true) {
                  // If greater than parent, swap
                  if (m.compatibility_score > getRank(parentLoc(pos)))
                      pos = swapWithParent(pos, parentLoc(pos));
                  else
                      return;
              }
          }
          void updateVal() {}
      };
      */
      
};

// UNSURE if can declare theses TODO
/*
inline
bool operator==(const MovieAndRank lhs, const MovieAndRank rhs) {
    return lhs.movie_id == rhs.movie_id;
}
inline
bool operator<(const MovieAndRank lhs, const MovieAndRank rhs) {
    return lhs.compatibility_score < rhs.compatibility_score;
}
inline
bool operator>(const MovieAndRank lhs, const MovieAndRank rhs) {
    return lhs.compatibility_score > rhs.compatibility_score;
}
*/

#endif // RECOMMENDER_INCLUDED
