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

class LeaderboardHeap {
    private:
        vector<User> heap;
        bool isMaxHeap;

        int parent(int i){ return (i-1)/ 2;}
        int leftChild(int i ) { return 2 * i + 1;}
        int rightChild(int i) { return 2 * i + 2;}

        bool compare (const User &a , const User& b){
            return isMaxHeap ? ( a.power > b.power) : (a.power < b.power);
        }


};