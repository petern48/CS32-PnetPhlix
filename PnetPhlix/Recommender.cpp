#include "Recommender.h"

#include "UserDatabase.h"
#include "MovieDatabase.h" // Move to .h ??
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    // given ud and md are already loaded
    m_ud = &user_database;
    m_md = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const // ADDED const
{
    vector<MovieAndRank> recommendations;
    if (movie_count <= 0)
        return recommendations; // return empty vector

    User *u = m_ud->get_user_from_email(user_email);
    // Get all movies the user has watched
    vector<string> watchHistory = u->get_watch_history();

    // Determine compatibility score for each movie watched
    for (int i = 0; i < watchHistory.size(); i++) {
        Movie* movie = m_md->get_movie_from_id(watchHistory[i]);
        vector<string> directors = movie->get_directors();
        for (int i = 0; i < directors.size(); i++) {

        }
        
    }

    return vector<MovieAndRank>();  // Replace this line with correct code.
}
