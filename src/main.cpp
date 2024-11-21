#include <climits>
#include <iostream>
#include <vector> // Use vector instead of array for dynamic sizing

using namespace std;

struct User {
  string username;
  string rank;
  int power;

  User(const string &name = "", const string &userRank, int userPower = 0)
      : username(name), rank(userRank), power(userPower) {}
};