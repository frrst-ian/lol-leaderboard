/*
 * League of Legends Leaderboard using Max Heap
 * Tracks player rankings based on power level
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;

// Console color definitions for visual feedback
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// Represents a player with username, rank, and power
struct User {
  string username;
  string rank;
  int power;

  // Constructor with automatic rank calculation
  User(const string &name = "", int userPower = 0)
      : username(name), power(userPower) {
    rank = getRankByPower(power);
  }

  // Determine player's rank based on power level
  static string getRankByPower(int power) {
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
};

// Manages the leaderboard using a heap data structure
class LeaderboardHeap {
private:
  vector<User> heap; // Underlying heap storage
  bool isMaxHeap;    // Heap type (max or min)

  // Heap navigation helpers
  int parent(int i) { return (i - 1) / 2; }
  int leftChild(int i) { return 2 * i + 1; }
  int rightChild(int i) { return 2 * i + 2; }

  // Compare users based on heap type
  bool compare(const User &a, const User &b) {
    return isMaxHeap ? (a.power > b.power) : (a.power < b.power);
  }

  // Restore heap property after removal
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

  // Restore heap property after insertion
  void heapifyUp(int i) {
    while (i > 0 && compare(heap[i], heap[parent(i)])) {
      swap(heap[i], heap[parent(i)]);
      i = parent(i);
    }
  }

public:
  // Constructor with heap type
  LeaderboardHeap(bool maxHeap = true) : isMaxHeap(maxHeap) {}

  // Add a new user to the leaderboard
  void insert(const User &user) {
    heap.push_back(user);
    heapifyUp(heap.size() - 1);
  }

  // Create leaderboard with example players
  void loadExampleLeaderboard() {
    heap.clear();
    vector<User> exampleUsers = {User("Ian", 1300), User("Faker", 1400),
                                 User("Chovi", 1350), User("Zeus", 1300)};
    for (const auto &user : exampleUsers) {
      insert(user);
    }
    cout << "Sample leaderboard loaded with " << heap.size() << " users.\n";
  }

  // Remove and return the top user
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

  // Get the top user without removing
  User top() const {
    if (heap.empty()) {
      cout << "Leaderboard is empty!\n";
      return User();
    }
    return heap[0];
  }

  // Interactively get user input
  static User getUserInput() {
    string username;
    int power;

    while (true) {
      cout << "Enter username and power (space-separated): ";
      cin.clear();

      if (cin >> username >> power) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return User(username, power);
      } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Try again.\n";
      }
    }
  }

  // Display the entire leaderboard
  void printHeap() const {
    if (heap.empty()) {
      cout << "Leaderboard is empty.\n";
      return;
    }

    cout << YELLOW << "\nLEADERBOARD\n" << RESET;
    cout << BLUE << left << setw(15) << "Username" << setw(15) << "Rank"
         << "Power\n"
         << RESET;
    cout << GREEN << string(45, '-') << '\n' << RESET;

    for (const auto &user : heap) {
      cout << RED << left << setw(15) << user.username << RESET << GREEN
           << setw(15) << user.rank << RESET << YELLOW << user.power << '\n'
           << RESET;
    }
    cout << '\n';
  }

  // Find a user by username
  User *findUser(const std::string &username) {
    auto it =
        std::find_if(heap.begin(), heap.end(), [&username](const User &user) {
          return user.username == username;
        });

    return (it != heap.end()) ? &(*it) : nullptr;
  }

  // Get current leaderboard size
  int size() const { return heap.size(); }

  // Check if leaderboard is empty
  bool isEmpty() const { return heap.empty(); }
};

// Function to display the rank system
void displayRanks() {
  cout << YELLOW << "\n=========== LEAGUE OF LEGENDS RANK SYSTEM ===========\n"
       << RESET;

  // Rank structure
  struct RankInfo {
    string name;
    int minPower;
    string color;
    string level;
  };

  // Create a list of ranks, their power and description
  vector<RankInfo> ranks = {{"Bronze", 0, RED, "Beginner"},
                            {"Silver", 100, "\033[37m", "Beginner"},
                            {"Gold", 300, YELLOW, "Advanced"},
                            {"Platinum", 500, BLUE, "Advanced"},
                            {"Diamond", 700, "\033[35m", "Advanced"},
                            {"Master", 900, GREEN, "Pro"},
                            {"Grandmaster", 1100, "\033[36m", "Elite"}};

  cout << BLUE << left << setw(15) << "Rank" << setw(15) << "Min Power"
       << "Skill Level\n"
       << GREEN << string(45, '-') << RESET << '\n';

  for (const auto &rank : ranks) {
    cout << rank.color << left << setw(15) << rank.name << setw(15)
         << rank.minPower << rank.level << '\n'
         << RESET;
  }

  cout << YELLOW << "\n================ CLIMB THE RANKS! ==================\n\n"
       << RESET;
}
int main() {
  LeaderboardHeap maxUserHeap(true);

  int choice;

  // Welcome screen
  cout << RED
       << "=============== LEAGUE OF LEGENDS LEADERBOARD ===============\n"
       << "           Show off your Skills and Conquer the Rift!\n\n"
       << RESET;
  cout << BLUE
       << "Enter your name and power to see your rank and share it to your "
          "friends.\n";

  cout << "Example:\n";
  cout << "Input: [ian 300, faker 1200, chovi 1100]\n";
  cout << "Output: [faker Grandmaster 1200, chovi Master 1100, ian Gold 300\n";
  cout << "Explore the leaderboard operations to get started.\n\n" << RESET;
  // Main menu loop
  while (true) {

    cout << YELLOW << "\nLeaderboard Operations\n" << RESET;
    cout << "[1] Add User\n"
         << "[2] View Top User\n"
         << "[3] View Leaderboard\n"
         << "[4] Find User\n"
         << "[5] Remove Top User\n"
         << "[6] Load Sample Leaderboard\n"
         << "[7] Show the rank system\n"
         << "[0] Exit\n"
         << "Enter your choice: ";

    cin >> choice;
    if (cin.fail()) {
      cout << RED << "Invalid choice! Try again...\n" << RESET;
      return 1;
    }

    // Menu action handlers
    switch (choice) {
    case 1: { // Add User
      User newUser = LeaderboardHeap::getUserInput();
      maxUserHeap.insert(newUser);
      cout << GREEN << "User added successfully.\n" << RESET;
      break;
    }
    case 2: { // View Top User
      if (!maxUserHeap.isEmpty()) {
        User topUser = maxUserHeap.top();
        cout << YELLOW << "Top User: " << topUser.username
             << ", Rank: " << topUser.rank << ", Power: " << topUser.power
             << '\n'
             << RESET;
      } else {
        cout << RED << "Leaderboard is empty.\n" << RESET;
      }
      break;
    }
    case 3: { // View Leaderboard
      maxUserHeap.printHeap();
      break;
    }
    case 4: { // Find User
      string username;
      cout << "Enter username to find: ";
      cin >> username;
      User *foundUser = maxUserHeap.findUser(username);
      if (foundUser) {
        cout << BLUE << "Found username: " << foundUser->username
             << ", Rank: " << foundUser->rank << ", Power: " << foundUser->power
             << '\n'
             << RESET;
      } else {
        cout << RED << "User not found!\n" << RESET;
      }
      break;
    }
    case 5: { // Remove Top User
      if (!maxUserHeap.isEmpty()) {
        User removedUser = maxUserHeap.extract();
        cout << BLUE << "Successfully removed " << removedUser.username << '\n'
             << RESET;
      } else {
        cout << "Leaderboard is empty.\n";
      }
      break;
    }
    case 6: { // Load Sample Leaderboard
      maxUserHeap.loadExampleLeaderboard();
      maxUserHeap.printHeap();
      break;
    }
    case 7: { // Display the ranking system
      displayRanks();
      break;
    }
    case 0: { // Exit
      cout << "Exiting the program...\n";
      return 0;
    }
    default: {
      cout << RED << "Invalid choice. Please try again.\n" << RESET;
    }
    }
  }

  return 0;
}