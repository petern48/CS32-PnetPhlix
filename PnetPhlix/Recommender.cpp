#include "Recommender.h"

#include "User.h"
#include "Movie.h" // MOVE TO .H ??

#include <string>
#include <vector>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    // given ud and md are already loaded
    m_ud = &user_database;
    m_md = &movie_database;
    m_moviesRanks = new TreeMultimap<string, MovieAndRank>;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    vector<MovieAndRank> recommendations;
    if (movie_count <= 0)
        return recommendations; // return empty vector

    User *user = m_ud->get_user_from_email(user_email);
    vector<string> watchHistory = user->get_watch_history();
    vector<Movie*> movieVect;
    TreeMultimap<string, MovieAndRank>::Iterator it;

    // Determine compatibility score based on each movie watched
    for (int i = 0; i < watchHistory.size(); i++) {
        Movie* m = m_md->get_movie_from_id(watchHistory[i]); // For each movie m

        vector<string> criteriaVect;

        // DIRECTORS
        vector<string> directors = m->get_directors();
        for (int i = 0; i < directors.size(); i++) {
            movieVect = m_md->get_movies_with_director(directors[i]); // For each director d
            for (int i = 0; i < movieVect.size(); i++) {
                it = m_moviesRanks->find(m->get_id());
                if (it.is_valid())
                    it.get_value().compatibility_score += DIRECTORPOINTS;
                else {
                    MovieAndRank mr(m->get_id(), DIRECTORPOINTS);
                    m_moviesRanks->insert(m->get_id(), mr); // Won't insert if already there
                }
            }
        }
        movieVect.clear();
        vector<string> actors = m->get_actors();
        for (int i = 0; i < actors.size(); i++) {
            movieVect = m_md->get_movies_with_actor(actors[i]);
            for (int i = 0; i < movieVect.size(); i++) {
                it = m_moviesRanks->find(m->get_id());
                if (it.is_valid()) {
                    it.get_value().compatibility_score += ACTORPOINTS;
                }
                // Create new MovieAndRank
                else {
                    MovieAndRank mr(m->get_id(), ACTORPOINTS);
                    m_moviesRanks->insert(m->get_id(), mr);
                }

            }
        }
        // Genres
        movieVect.clear();
        vector<string> genres = m->get_genres();
        for (int i = 0; i < genres.size(); i++) {
            movieVect = m_md->get_movies_with_genre(genres[i]);
            for (int i = 0; i < movieVect.size(); i++) {
                it = m_moviesRanks->find(m->get_id());
                if (it.is_valid()) {
                    it.get_value().compatibility_score += GENREPOINTS;
                }
                // Create new MovieAndRank
                else {
                    MovieAndRank mr(m->get_id(), GENREPOINTS);
                    m_moviesRanks->insert(m->get_id(), mr);
                }

            }
        }
    }



    return vector<MovieAndRank>();  // Replace this line with correct code.
}
