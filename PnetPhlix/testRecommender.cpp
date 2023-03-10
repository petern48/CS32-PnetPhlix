//#include "Recommender.h"
//#include "Movie.h"
//#include "MovieDatabase.h"
//#include <string>
//#include <iostream>
//using namespace std;
//
//void findMatches(const Recommender& r,
//	const MovieDatabase& md,
//	const string& user_email,
//	int num_recommendations) {
//	// get up to ten movie recommendations for the user
//	vector<MovieAndRank> recommendations =
//		r.recommend_movies(user_email, 10);
//	if (recommendations.empty())
//		cout << "We found no movies to recommend :(.\n";
//	else {
//		for (int i = 0; i < recommendations.size(); i++) {
//			const MovieAndRank& mr = recommendations[i]; // Replace parentheses with ;
//			Movie* m = md.get_movie_from_id(mr.movie_id);
//			cout << i << ". " << m->get_title() << " ("
//				<< m->get_release_year() << ")\n Rating: "
//				<< m->get_rating() << "\n Compatibility Score: "
//				<< mr.compatibility_score << "\n";
//}
//		}
//	}