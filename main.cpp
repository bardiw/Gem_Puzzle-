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

        regex passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#\\$%\\^&\\*]).{8,}$");
        if (!regex_match(password, passwordRegex)) {
            cout << "Error: password is not strong enough. It must be at least 8 characters long and contain at least one lowercase letter, one uppercase letter, one digit, and one special character." << endl;
        } else {
            passwordValid = true;
        }
    }

    Account account = {username, password, 0};
    accounts[username] = account;

    ofstream accountsFile(ACCOUNTS_FILE, ios::app);
    accountsFile << username << " " << password << " " << 0 << endl;
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
    srand(time(0));

    ifstream accountsFile(ACCOUNTS_FILE);
    string username, password;
    int score;
    while (accountsFile >> username >> password >> score) {
        Account account = {username, password, score};
        accounts[username] = account;
    }
    accountsFile.close();

    user = username_acount() ;
        return 0;
}

