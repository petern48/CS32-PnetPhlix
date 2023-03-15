//#if defined(_MSC_VER)  &&  !defined(_DEBUG)
//#include <iostream>
//#include <windows.h>
//#include <conio.h>
//
//struct KeepWindowOpenUntilDismissed
//{
//	~KeepWindowOpenUntilDismissed()
//	{
//		DWORD pids[1];
//		if (GetConsoleProcessList(pids, 1) == 1)
//		{
//			std::cout << "Press any key to close this window . . . ";
//			_getch();
//		}
//	}
//} keepWindowOpenUntilDismissed;
//#endif
//// Click Build -> Configuration Manager. Under Active Solution Config, select Release instead of Debug (for speed)
//
//#include "Recommender.h"
//#include "Movie.h"
//#include "MovieDatabase.h"
//#include "User.h"
//#include "UserDatabase.h"
//#include <string>
//#include <iostream>
//#include <chrono> // Test Time
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
//
//const string USERFILENAME = "users.txt";
//const string MOVIEFILENAME = "movies.txt";
//const string userEmail = "HezekF0394@aol.com";
//const int NUMTORECOMMEND = 3;
//
//int main() {
//	UserDatabase ud;
//	auto start = chrono::steady_clock::now();
//	ud.load(USERFILENAME);
//	auto stop = chrono::steady_clock::now();
//	cout << "Load ud Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
//	
//	start = chrono::steady_clock::now();
//	MovieDatabase md;
//	md.load(MOVIEFILENAME);
//	stop = chrono::steady_clock::now();
//	cout << "Load md Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
//	Recommender r(ud, md);
//
//	cout << "User Email: " << userEmail << endl;
//
//
//	start = chrono::steady_clock::now();
//	findMatches(r, md, userEmail, NUMTORECOMMEND);
//	stop = chrono::steady_clock::now();
//	cout << "findMatches Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
//}