#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<windows.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
using namespace std;
const std::string ACCOUNTS_FILE = "accounts.txt";
// This struct represents a user account.
struct Account {
    std::string username;
    std::string password;
    int score;
};
std::unordered_map<std::string, Account> accounts;

// This function creates a new account for a user.
// It prompts the user for a username and password and stores them in a map and a file.
string signUp() {
    std::string username, password;
    std::cout << "Enter a new username: ";
    std::cin >> username;

    bool passwordValid = false;
    while (!passwordValid) {
        std::cout << "Enter a new password: ";
        std::cin >> password;

        // Check if the password is strong enough.
        std::regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#\\$%\\^&\\*]).{8,}$");
        if (!std::regex_match(password, passwordRegex)) {
            std::cout << "Error: password is not strong enough. It must be at least 8 characters long and contain at least one lowercase letter, one uppercase letter, one digit, and one special character." << std::endl;
        } else {
            passwordValid = true;
        }
    }

    // Create a new account and add it to the map of accounts.
    Account account = {username, password, 0};
    accounts[username] = account;

    // Open the accounts file in append mode.
    std::ofstream accountsFile(ACCOUNTS_FILE, std::ios::app);
    // Write the new account to the file.
    accountsFile << username << " " << password << " " << 0 << std::endl;
    // Close the file.
    accountsFile.close();
    return username ;
}

// This function logs a user in.
// It prompts the user for a username and password and checks if they match a user in the map.
string signIn() {
    std::string username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    // Check if the username and password match an account in the map.
    if (accounts.count(username) && accounts[username].password == password) {
        std::cout << "Welcome back, " << username << "!" << std::endl;
        return username ;
    } else {
        std::cout << "Invalid username or password." << std::endl;
        return "" ;
    }
}
void showLeaderboard() {
    // Get a vector of all the accounts.
    std::vector<Account> accountList;
    for (const auto& [username, account] : accounts) {
        accountList.push_back(account);
    }

    // Sort the accounts by score in descending order.
    std::sort(accountList.begin(), accountList.end(), [](const Account& a, const Account& b) {
        return a.score > b.score;
    });

    // Print the leaderboard.
    std::cout << "LEADERBOARD" << std::endl;
    std::cout << "Username\tScore" << std::endl;
    for (const Account& account : accountList) {
        std::cout << account.username << "\t" << account.score << std::endl;
    }
}
// size of puzzle (number of rows and columns)
int N;

// 2D vector to represent the puzzle
std::vector<std::vector<int>> puzzle;

// utility function to print the puzzle
void printPuzzle()
{
    system("cls");
    std::cout << std::endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(puzzle[i][j] == 0)
                std::cout << "    ";
            else if(puzzle[i][j]/10 > 0)
                std::cout << puzzle[i][j] << "  ";
            else
                std::cout << puzzle[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}

// utility function to check if the puzzle is solved
bool isSolved()
{
    int count = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (puzzle[i][j] != count)
            {
                if(puzzle[i][j]==0 && i==N-1 && j==N-1)
                    return true ;
                return false;
            }
            count++;
        }
    }
    return true;
}

// utility function to shuffle the puzzle
void shufflePuzzle()
{
    // generate a random permutation of the puzzle
    for (int i = 0; i < N * N; i++)
    {
        int r = rand() % (N * N);
        int x1 = i / N;
        int y1 = i % N;
        int x2 = r / N;
        int y2 = r % N;
        std::swap(puzzle[x1][y1], puzzle[x2][y2]);
    }
}

// utility function to find the position of the empty tile (0)
void findEmptyTile(int &x, int &y)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (puzzle[i][j] == 0)
            {
                x = i;
                y = j;
                return;
            }
        }
    }
}

// utility function to move the empty tile (0) in the puzzle
bool moveTile(int dx, int dy)
{
    int x, y;
    findEmptyTile(x, y);
    if (x + dx < 0 || x + dx >= N || y + dy < 0 || y + dy >= N)
    {
        return false;
    }
    std::swap(puzzle[x][y], puzzle[x + dx][y + dy]);
    return true;
}
string username_acount(string user= ""){
    while(user=="")
    {
        std::cout << "Would you like to sign up (1) or sign in (2)? ";
        int choice;
        std::cin >> choice;
        if (choice == 1) {
            user = signUp();
        } else if (choice == 2) {
            user = signIn();
        } else {
            std::cout << "Invalid choice." << std::endl;
        }
    }
    return user;
}
void incrementScore(const std::string& username) {
  // Check if the username exists in the map.
  if (accounts.count(username)) {
    // Increment the score.
    ++accounts[username].score;

    // Open the accounts file in write mode.
    std::ofstream accountsFile(ACCOUNTS_FILE);
    // Overwrite the file with the updated scores.
    for (const auto& [username, account] : accounts) {
      accountsFile << username << " " << account.password << " " << account.score << std::endl;
    }
    // Close the file.
    accountsFile.close();
  } else {
    std::cout << "Error: username not found." << std::endl;
  }
}
// main function
int main()
{
    string user;
    // seed the random number generator
    srand(time(0));
    // A map to store the user accounts.

    // Open the accounts file in read mode.
    std::ifstream accountsFile(ACCOUNTS_FILE);
    // Read the account information from the file and add it to the map.
    std::string username, password;
    int score;
    while (accountsFile >> username >> password >> score) {
        Account account = {username, password, score};
        accounts[username] = account;
    }
    // Close the file.
    accountsFile.close();

    // Prompt the user to sign up or sign in.
    user = username_acount() ;
    // get the size of the puzzle from the user
    std::cout << "Enter the size of the puzzle (e.g. 4 for a 4x4 puzzle): ";
    std::cin >> N;

    // create the puzzle
    puzzle = std::vector<std::vector<int>>(N, std::vector<int>(N));

    // initialize the puzzle
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            puzzle[i][j] = i * N + j + 1;
        }
    }
    puzzle[N - 1][N - 1] = 0;

    // shuffle the puzzle
    shufflePuzzle();

    // print the puzzle
    printPuzzle();

    // loop until the puzzle is solved
    while (!isSolved())
    {
        // print the instructions
        std::cout << "Enter your move (WASD or Q to quit): ";

        // get the user's move
        char ch;
        std::cin >> ch;

        // check if the user wants to quit
        if (ch == 'Q' || ch == 'q')
        {
            break;
        }

        // move the tile based on the user's input
        bool success = false;
        if (ch == 'W' || ch == 'w')
        {
            success = moveTile(-1, 0);
        }
        else if (ch == 'A' || ch == 'a')
        {
            success = moveTile(0, -1);
        }
        else if (ch == 'S' || ch == 's')
        {
            success = moveTile(1, 0);
        }
        else if (ch == 'D' || ch == 'd')
        {
            success = moveTile(0, 1);
        }

        // check if the move was successful

        // print the puzzle
        printPuzzle();
        if (!success)
        {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 0x4);
            std::cout << "Invalid move" << std::endl;
            SetConsoleTextAttribute(h, 0xf);
        }
    }

    // print a message if the puzzle is solved
    if (isSolved())
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 0xA);
        std::cout << "Congratulations, you solved the puzzle!" << std::endl;
        SetConsoleTextAttribute(h, 0xf);
        incrementScore(user) ;
        showLeaderboard();
    }

    return 0;
}

