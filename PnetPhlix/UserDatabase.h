#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
// I added the following
#include "treemm.h"
const int MAXUSERS = 100000; // Page 1
const int NAMELINENUMBER = 1;
const int EMAILLINENUMBER = 2;
const int MOVIECOUNTLINENUMBER = 3;

class User;

class UserDatabase // CASE SENSITIVE
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;
    ~UserDatabase();

  private:
      TreeMultimap<std::string, int> m_tree;
      User* m_users[MAXUSERS];
      int m_numUsers;
};

#endif // USERDATABASE_INCLUDED
