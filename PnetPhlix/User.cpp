#include "User.h"

#include <string>
#include <vector>
using namespace std;

User::User(const string& full_name, const string& email,
           const vector<string>& watch_history)
{
    // Replace this line with correct code.
    m_name = full_name;
    m_email = email;
    m_watchHistory = watch_history;
}


string User::get_full_name() const {
    return m_name;
}

string User::get_email() const {
    return m_email;
}

vector<string> User::get_watch_history() const {
    return m_watchHistory;
}