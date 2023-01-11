#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include<windows.h>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <stack>
#include <time.h>
using namespace std;

const string ACCOUNTS_FILE = "accounts.txt";
struct Account {
    string username;
    string password;
    int score;
};
unordered_map<string, Account> accounts;
int N = 3;
string signIn();
string signUp() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;

    bool passwordValid = false;
    while (!passwordValid) {
        cout << "Enter a new password: ";
        cin >> password;

        regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#\\$%\\^&\\*]).{8,}$");
        if (!regex_match(password, passwordRegex)) {
            cout << "Error: password is not strong enough. It must be at least 8 characters long and contain at least one lowercase letter, one uppercase letter, one digit, and one special character." << endl;
        }
        else {
            passwordValid = true;
        }
    }

    Account account = { username, password, 0 };
    accounts[username] = account;

    ofstream accountsFile(ACCOUNTS_FILE, ios::app);
    accountsFile << username << " " << password << " " << 0 << endl;
    accountsFile.close();
    return username;
}
string username_acount(string user = "") {
    while (user == "")
    {
        cout << "Would you like to sign up (1) or sign in (2) or play as an guest (3)? ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            user = signUp();
        }
        else if (choice == 2) {
            user = signIn();
        }
        else if (choice == 3) {
            user = "Guest6957624";
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
    return user;
}
string ADMIN() {
    cout << "Enter the size of the puzzle (e.g. 4 for a 4x4 puzzle): ";
    cin >> N;

    string user = username_acount();
    return user;
}

string signIn() {
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    if (username == "Anorak")
    {
        if (password == "Anor@k10")
            ADMIN();
    }
    else
    {
        if (accounts.count(username) && accounts[username].password == password) {
            cout << "Welcome back, " << username << "!" << endl;
            return username;
        }
        else {
            cout << "Invalid username or password." << endl;
            return "";
        }
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

    cout << "LEADERBOARD" << endl;
    cout << "Username\tScore" << endl;
    for (const Account& account : accountList) {
        cout << account.username << "\t" << account.score << endl;
    }
}

vector<vector<int>> puzzle;

void printPuzzle()
{
    system("cls");
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (puzzle[i][j] == 0)
                cout << "    ";
            else if (puzzle[i][j] / 10 > 0)
                cout << puzzle[i][j] << "  ";
            else
                cout << puzzle[i][j] << "   ";
        }
        cout << endl;
    }
}

bool isSolved()
{
    int count = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (puzzle[i][j] != count)
            {
                if (puzzle[i][j] == 0 && i == N - 1 && j == N - 1)
                    return true;
                return false;
            }
            count++;
        }
    }
    return true;
}

void shufflePuzzle()
{
    for (int i = 0; i < N * N; i++)
    {
        int r = rand() % (N * N);
        int x1 = i / N;
        int y1 = i % N;
        int x2 = r / N;
        int y2 = r % N;
        swap(puzzle[x1][y1], puzzle[x2][y2]);
    }
}

void findEmptyTile(int& x, int& y)
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

bool moveTile(int dx, int dy)
{
    int x, y;
    findEmptyTile(x, y);
    if (x + dx < 0 || x + dx >= N || y + dy < 0 || y + dy >= N)
    {
        return false;
    }
    swap(puzzle[x][y], puzzle[x + dx][y + dy]);
    return true;
}

void incrementScore(const string& username) {
    if (accounts.count(username)) {
        ++accounts[username].score;

        ofstream accountsFile(ACCOUNTS_FILE);
        for (const auto& [username, account] : accounts) {
            accountsFile << username << " " << account.password << " " << account.score << endl;
        }
        accountsFile.close();
    }
}

int main()
{
    string user;
    srand(time(0));

    ifstream accountsFile(ACCOUNTS_FILE);
    string username, password;
    int score;
    while (accountsFile >> username >> password >> score) {
        Account account = { username, password, score };
        accounts[username] = account;
    }
    accountsFile.close();

    user = username_acount();

    puzzle = vector<vector<int>>(N, vector<int>(N));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            puzzle[i][j] = i * N + j + 1;
        }
    }
    puzzle[N - 1][N - 1] = 0;

    shufflePuzzle();

    printPuzzle();
    int redu = 0;
    while (!isSolved())
    {
        cout << endl;
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
            if (success);
        }
        else if (ch == 'A' || ch == 'a')
        {
            success = moveTile(0, -1);
            if (success);
        }
        else if (ch == 'S' || ch == 's')
        {
            success = moveTile(1, 0);
            if (success);
        }
        else if (ch == 'D' || ch == 'd')
        {
            success = moveTile(0, 1);
            if (success);
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
        incrementScore(user);
        showLeaderboard();
    }

    return 0;
}

