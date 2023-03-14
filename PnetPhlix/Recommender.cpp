#include "Recommender.h"

#include "User.h"
#include "Movie.h" // MOVE TO .H ??

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{
    // given ud and md are already loaded
    m_ud = &user_database;
    m_md = &movie_database;
    m_moviesRanks = new unordered_map<string, int>;
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
    unordered_map<string, int>::iterator it;
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

                Movie* tempPtr;
                // Remove the watched movies from the vector
                for (int k = 0; k < watchHistory.size(); k++) {
                    vector<Movie*>::iterator it;
                    tempPtr = m_md->get_movie_from_id(watchHistory[k]);
                    it = find(movieVect.begin(), movieVect.end(), tempPtr);
                    if (it != movieVect.end())
                        movieVect.erase(it);
                }

                for (int k = 0; k < movieVect.size(); k++) {
                    it = m_moviesRanks->find(movieVect[k]->get_id());
                    
                    if (it != m_moviesRanks->end()) {
                        it->second += pointsToAdd;
                    }
                    else {
                        //MovieAndRank mr(m->get_id(), pointsToAdd);
                        m_moviesRanks->insert({ movieVect[k]->get_id(), pointsToAdd });
                    }
                }
            }
        }
    }

    vector<pair<Movie*, int>> v;

    // Get the top movie_count recommended movies
    for (it = m_moviesRanks->begin(); it != m_moviesRanks->end(); it++) {
        Movie* m = m_md->get_movie_from_id(it->first);
        pair<Movie*, int> pair(m, it->second);
        v.push_back(pair);
    }
    
    sort(v.begin(), v.end(), compareMR);

    for (int i = 0; i < movie_count && i < v.size(); i++) {
        MovieAndRank mr(v[i].first->get_id(), v[i].second);
        recommendations.push_back(mr);
    }
    return recommendations;
}

bool Recommender::compareMR(const pair<Movie*, int>& p1, const pair<Movie*, int>& p2) {
    
    // Order based on compatibility score
    if (p1.second > p2.second)
        return true;
    else if (p1.second < p2.second)
        return false;

    // Order by rating
    if (p1.first->get_rating() > p2.first->get_rating())
        return true;
    else if (p1.first->get_rating() < p2.first->get_rating())
        return false;

    // Order by name (first in alphabet comes first)
    if (p1.first->get_title() < p2.first->get_title())
        return true;
    else
        return false;
}