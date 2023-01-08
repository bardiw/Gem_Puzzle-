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
const string ACCOUNTS_FILE = "accounts.txt";

struct Account {
    string username;
    string password;
    int score;
};

unordered_map<string, Account> accounts;

string signUp() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;

    bool passwordValid = false;
    while (!passwordValid) {
        cout << "Enter a new password: ";
        cin >> password;

        // Check if the password is strong enough.
        regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#\\$%\\^&\\*]).{8,}$");
        if (!regex_match(password, passwordRegex)) {
            cout << "Error: password is not strong enough. It must be at least 8 characters long and contain at least one lowercase letter, one uppercase letter, one digit, and one special character." << endl;
        } else {
            passwordValid = true;
        }
    }

    // Create a new account and add it to the map of accounts.
    Account account = {username, password, 0};
    accounts[username] = account;

    // Open the accounts file in append mode.
    ofstream accountsFile(ACCOUNTS_FILE, ios::app);
    // Write the new account to the file.
    accountsFile << username << " " << password << " " << 0 << endl;
    // Close the file.
    accountsFile.close();
    return username ;
}

string signIn() {

    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (accounts.count(username) && accounts[username].password == password) {
        cout << "Welcome back, " << username << "!" << endl;
        return username ;
    } else {
        cout << "Invalid username or password." << endl;
        return "" ;
    }
}

void showLeaderboard() {
    vector<Account> accountList;
    for (const auto& [username, account] : accounts) {
        accountList.push_back(account);
    }

    sort(accountList.begin(), accountList.end(), [](const Account& a, const Account& b) {
        return a.score > b.score;
    });

    // Print the leaderboard.
    cout << "LEADERBOARD" << endl;
    cout << "Username\tScore" << endl;
    for (const Account& account : accountList) {
        cout << account.username << "\t" << account.score << endl;
    }
}

string username_acount(string user= ""){
    while(user=="")
    {
        cout << "Would you like to sign up (1) or sign in (2)? ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            user = signUp();
        } else if (choice == 2) {
            user = signIn();
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    return user;
}

int main()
{
    string user;
    // seed the random number generator
    srand(time(0));
    // A map to store the user accounts.

    // Open the accounts file in read mode.
    ifstream accountsFile(ACCOUNTS_FILE);
    // Read the account information from the file and add it to the map.
    string username, password;
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
    cout << "Enter the size of the puzzle (e.g. 4 for a 4x4 puzzle): ";
    cin >> N;

    // create the puzzle
    puzzle = vector<vector<int>>(N, vector<int>(N));

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
        cout << "Enter your move (WASD or Q to quit): ";

        char ch;
        cin >> ch;

        if (ch == 'Q' || ch == 'q')
        {
            break;
        }

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

        printPuzzle();
        if (!success)
        {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h, 0x4);
            cout << "Invalid move" << endl;
            SetConsoleTextAttribute(h, 0xf);
        }
    }

    if (isSolved())
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 0xA);
        cout << "Congratulations, you solved the puzzle!" << endl;
        SetConsoleTextAttribute(h, 0xf);
        incrementScore(user) ;
        showLeaderboard();
    }

    return 0;
}

