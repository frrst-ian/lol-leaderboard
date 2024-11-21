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

  int parent(int i) { return (i - 1) / 2; }
  int leftChild(int i) { return 2 * i + 1; }
  int rightChild(int i) { return 2 * i + 2; }

  bool compare(const User &a, const User &b) {
    return isMaxHeap ? (a.power > b.power) : (a.power < b.power);
  }

  void heapifyDown(int i) {
    int target = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap.size() && compare(heap[left], heap[target]))
      target = left;

    if (right < heap.size() && compare(heap[right], heap[target]))
      target = right;

    if (target != i) {
      swap(heap[i], heap[target]);
      heapifyDown(target);
    }
  }

  void heapifyUp(int i) {
    while (i > 0 && compare(heap[i], heap[parent(i)])) {
      swap(heap[i], heap[parent(i)]);
      i = parent(i);
    }
  }

public:
  LeaderboardHeap(bool maxHeap = true) : isMaxHeap(maxHeap) {}

  void insert(const User &user) {
    heap.push_back(user);
    heapifyUp(heap.size() - 1);
  }

  User extract() {
    if (heap.empty()) {
      cout << "Leaderboard is empty!\n";
      return User();
    }

    User topUser = heap[0];

    heap[0] = heap.back();
    heap.pop_back();

    if (!heap.empty()) {
      heapifyDown(0);
    }

    return topUser;
  }

  User top() const {
    if (heap.empty()) {
      cout << "Leaderboard is empty!\n";
      return User();
    }

    return heap[0];
  }

  string getRankByPower(int power) {
    if (power < 100)
      return "Bronze";
    if (power < 300)
      return "Silver";
    if (power < 500)
      return "Gold";
    if (power < 700)
      return "Platinum";
    if (power < 900)
      return "Diamond";
    if (power < 1100)
      return "Master";
    return "Grandmaster";
  }

  void updateRank(User &user) { user.rank = getRankByPower(user.power); }

  
};