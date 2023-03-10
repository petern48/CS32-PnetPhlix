#include "MovieDatabase.h"
#include "Movie.h"
#include <iostream>
#include "User.h"
using namespace std;

const string FILENAME = "myMovies.txt";

int main()
{
	MovieDatabase ud;

	ud.load(FILENAME);

	
	// TEST inputID
	string input;
	/*
	cout << "Input: ";
	cin >> input;
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
	*/

	// Test getmovies with director
	cout << "Input Director: ";
	cin >> input;
	vector<Movie*> moviesWithDirectors = ud.get_movies_with_director(input);
	/*
	if ( == nullptr) {
		"Invalid ID";
		return -1;
	}
	*/

	for (int i = 0; i < moviesWithDirectors.size(); i++) {
		cout << moviesWithDirectors[i]->get_title() << endl;
		vector<string> directors = moviesWithDirectors[i]->get_directors();
		for (int i = 0; i < directors.size(); i++)
			cout << directors[i] << ", ";
		cout << endl;
	}
}