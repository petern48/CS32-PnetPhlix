#include "MovieDatabase.h"
#include "Movie.h"
#include <iostream>
#include "User.h"
#include <chrono>
using namespace std;

const string FILENAME = "movies.txt";

int main()
{
	MovieDatabase ud;
	auto start = chrono::steady_clock::now();
	ud.load(FILENAME);
	auto stop = chrono::steady_clock::now();
	cout << "Load md Took " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << "ms" << endl;
	
	// TEST inputID
	string input = "Id12611";

	cout << "Input: " << input << endl;

	Movie* u = ud.get_movie_from_id(input);
	if (u == nullptr) {
		"Invalid ID";
		return -1;
	}
	
	cout << u->get_id() << endl;
	cout << u->get_title() << endl;
	cout << u->get_release_year() << endl;
	vector<string> v = u->get_actors();
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
	v = u->get_directors();
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
	v = u->get_genres();
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
	cout << u->get_rating() << endl;


	// Test getmovies with director
	getline(cin, input);
	input = "valery Todorovsky";
	cout << "Input Director: " << input << endl;
	vector<Movie*> movieVect = ud.get_movies_with_director(input);

	for (int i = 0; i < movieVect.size(); i++) {
		cout << movieVect[i]->get_title() << endl;
		vector<string> directors = movieVect[i]->get_directors();
		for (int i = 0; i < directors.size(); i++)
			cout << directors[i] << ", ";
		cout << endl;
	}

	getline(cin, input);
	input = "tom Hanks";
	cout << "Input Actor: " << input << endl;
	movieVect = ud.get_movies_with_actor(input);

	for (int i = 0; i < movieVect.size(); i++) {
		cout << movieVect[i]->get_title() << endl;
		vector<string> v2 = movieVect[i]->get_actors();
		for (int i = 0; i < v2.size(); i++)
			cout << v2[i] << ", ";
		cout << endl;
	}

	getline(cin, input);
	input = "drama";
	cout << "Input Genre: " << input << endl;
	movieVect = ud.get_movies_with_genre(input);

	for (int i = 0; i < movieVect.size(); i++) {
		cout << movieVect[i]->get_title() << endl;
		vector<string> v2 = movieVect[i]->get_genres();
		for (int i = 0; i < v2.size(); i++)
			cout << v2[i] << ", ";
		cout << endl;
	}
}