#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>

// I added the following
#include "User.h"
#include <iostream>
#include <fstream>
#include <sstream> // To convert string to an int

using namespace std;

UserDatabase::UserDatabase()
{
    m_numUsers = 0;
}

UserDatabase::~UserDatabase() {
    // Delete the allocated users
    for (int i = 0; i < m_numUsers; i++) {
        if (m_users[i] != nullptr) {
            delete m_users[i];
            m_users[i] = nullptr;
        }
    }

}

bool UserDatabase::load(const string& filename)
{
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Couldn't open file " << filename << endl;
        return false;
    }

    string currLine;
    string name;
    string email;
    vector<string> watchHistory;
    int lineCount = 1;
    int totalMovieCount = 0;
    while (getline(infile, currLine)) {
        if (lineCount == NAMELINENUMBER)
            name = currLine;
        else if (lineCount == EMAILLINENUMBER)
            email = currLine;
        // Count of number of movies
        else if (lineCount == MOVIECOUNTLINENUMBER) {
            stringstream ss; // Convert string to an int
            ss << currLine;
            ss >> totalMovieCount;
        }
        else if (lineCount > MOVIECOUNTLINENUMBER) {
            watchHistory.push_back(currLine); // Push Movie ID

            // If done with this User record, reset values and create user
            if (lineCount == totalMovieCount + MOVIECOUNTLINENUMBER) {
                // Create user and push to tree
                m_users[m_numUsers] = new User(name, email, watchHistory);
                m_tree.insert(email, m_numUsers);
                m_numUsers++;

                watchHistory.clear();
                // Skip new line after each User record
                infile.ignore(10000, '\n');
                lineCount = 0; // Will become 1 at end of loop
            }
        }
        lineCount++;
    }
    return true;  // Replace this line with correct code.
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<string, int>::Iterator it = m_tree.find(email);
    if (it.is_valid())
        return m_users[it.get_value()];
    return nullptr;
}
