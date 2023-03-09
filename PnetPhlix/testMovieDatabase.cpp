#include "MovieDatabase.h"
#include "Movie.h"
#include <iostream>
#include "User.h"
using namespace std;

const string FILENAME = "movies.txt";

int main()
{
	MovieDatabase ud;

	ud.load(FILENAME);

	string inputID;
	cout << "Input: ";
	cin >> inputID;
	Movie* u = ud.get_movie_from_id(inputID);
	if (u == nullptr) {
		"Invalid ID";
		return -1;
	}
	
	cout << u->get_id() << endl;
	/*
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


}