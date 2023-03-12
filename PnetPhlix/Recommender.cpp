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
    vector<string> criteriaVect;
    TreeMultimap<string, MovieAndRank>::Iterator it;
    int pointsToAdd;

    // Determine compatibility score based on each movie watched
    for (int i = 0; i < watchHistory.size(); i++) {
        Movie* m = m_md->get_movie_from_id(watchHistory[i]); // For each movie m

        for (int criteria = 0; criteria < 3; criteria++) {

            movieVect.clear();

            switch (criteria) {
            case 0:
                pointsToAdd = DIRECTORPOINTS;
                criteriaVect = m->get_directors(); break; // Directors
            case 1:
                pointsToAdd = ACTORPOINTS;
                criteriaVect = m->get_actors(); break; // Actors
            case 2:
                pointsToAdd = GENREPOINTS;
                criteriaVect = m->get_genres(); break; // Genres
            }
            
            for (int j = 0; j < criteriaVect.size(); j++) {

                // Get vector of movies according for current director, actor, or genre
                switch (criteria) {
                case 0:
                    movieVect = m_md->get_movies_with_director(criteriaVect[j]); break; // For each director d
                case 1:
                    movieVect = m_md->get_movies_with_actor(criteriaVect[j]); break; // For each actor
                case 2:
                    movieVect = m_md->get_movies_with_genre(criteriaVect[j]); break; // For each genre
                }

                for (int k = 0; k < movieVect.size(); k++) {
                    it = m_moviesRanks->find(m->get_id());
                    if (it.is_valid())
                        it.get_value().compatibility_score += pointsToAdd;
                    else {
                        MovieAndRank mr(m->get_id(), pointsToAdd);
                        m_moviesRanks->insert(m->get_id(), mr);
                    }
                }
            }
        }
    }

    // Get the top movie_count recommended movies



    // add to recommendations.push_back()

    return recommendations;
}
