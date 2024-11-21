#include <climits>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector> // Use vector instead of array for dynamic sizing

using namespace std;

struct User {
  string username;
  string rank;
  int power;

  User(const string &name = "", const string &userRank = "", int userPower = 0)
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

  static User getUserInput() {
    string username;
    string userRank;
    int power;

    while (true) {
      cout << "Enter user details (username rank power) space-separated: ";

      cin.clear();

      if (cin >> username >> userRank >> power) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return User(username, userRank, power);
      } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again.\n";
      }
    }
  }

  void printHeap() const {
    cout << "LEADERBOARD\n";
    cout << "Username" << setw(3) << "Rank" << setw(3) << "Power" << '\n';
    for (const auto &user : heap) {
      cout << setw(3) << user.username << setw(3) << user.rank << setw(3)
           << user.power << '\n';
    }
  }

  int size() const { return heap.size(); }

  bool isEmpty() const { return heap.empty(); }
};

int main() {
  LeaderboardHeap maxUserHeap(true);

  int choice;

  while (true) {
    cout << "Leaderboard Operations\n";
    cout << "[1] Add User:\n"
         << "[2] View Top User:\n"
         << "[3] View Leaderboard\n"
         << "[4] Find User\n"
         << "[5] Remove Top User\n"
         << "[0] Exit\n"
         << "Enter your choice: ";
    cin >> choice;
    if (cin.fail()) {
      cout << "Invalid choice! Try again...\n";
      return 1;
    }

    switch (choice) {
    case 1: {
      User newUser = LeaderboardHeap::getUserInput();
      maxUserHeap.updateRank(newUser);
      maxUserHeap.insert(newUser);
      cout << "User added successfully.\n";
      break;
    }
    case 2: {
      if (!maxUserHeap.isEmpty()) {
        User topUser = maxUserHeap.top();
        cout << "Top User: " << topUser.username << ", Rank: " << topUser.rank
             << ", Power: " << topUser.power << '\n';
      } else {
        cout << "Leaderboard is empty.\n";
      }
      break;
    }
    case 3: {
      maxUserHeap.printHeap();
      break;
    }
    case 4: {
    }
    case 5: {
      if (!maxUserHeap.isEmpty()) {
        User removedUser = maxUserHeap.extract();
        cout << "Successfully removed " << removedUser.username << '\n';

      } else {
        cout << "Leaderboard is empty.\n";
      }
      break;
    }
    case 0: {
      cout << "Exiting the program...\n";
      return 0;
    }
    default: {
      cout << "Invalid choice. Please try again.\n";
    }
    }
  }

  return 0;
}