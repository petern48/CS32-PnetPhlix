#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
// I added the following
#include "treemm.h"
const int NAMELINENUMBER = 1;
const int EMAILLINENUMBER = 2;
const int MOVIECOUNTLINENUMBER = 3;

class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;
    ~UserDatabase();

  private:
      TreeMultimap<std::string, User*> *m_tree;
};

#endif // USERDATABASE_INCLUDED
