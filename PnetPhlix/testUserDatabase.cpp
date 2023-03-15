//#include "UserDatabase.h"
//#include <iostream>
//#include "User.h"
//using namespace std;
//
//const string FILENAME = "users.txt";
//
//int main()
//{
//	UserDatabase ud;
//
//	ud.load(FILENAME);
//	
//	string inputEmail;
//	cout << "Input: AbFow2483@charter.net";
//	inputEmail = "AbFow2483@charter.net";
//	User* u = ud.get_user_from_email(inputEmail);
//	if (u == nullptr) {
//		cout << "Invalid Email";
//		return -1;
//	}
//	cout << u->get_full_name() << endl;
//	cout << u->get_email() << endl;
//	vector<string> v = u->get_watch_history();
//	for (int i = 0; i < v.size(); i++) {
//		cout << v[i] << endl;
//	}
//
//
//
//
//}