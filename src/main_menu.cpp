#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "main_menu.h"
#include "user_menu.h"
#include "admin.h"
#include <cstring>
#include <ctime>
using namespace std;

int main_menu()
{
    int choice;
    do
    {
        cout << endl
             << "\n\t   \t\t\t\t\t\t\t\t----------------------------" << endl;
        cout << endl
             << "\n\t   \t\t\t\t\t\t\t\t     MAIN MENU   " << endl;
        time_t now = time(nullptr);
        string dt = ctime(&now);
        cout << "\n\t   \t\t\t\t\t\t\t\t     " << dt << endl;
        cout << endl
             << "\n\t   \t\t\t\t\t\t\t\t----------------------------" << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     1.  ADMIN   " << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     2.  USER   " << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     3.  EXIT   " << endl;

        cout << "\n\t   \t\t\t\t\t\t\t\t     ENTER YOUR CHOICE :    ";
        cin >> choice;

        if (choice == 1)
        {
            authentication();
            admin_menu();
        }
        else if (choice == 2)
            user_menu();
        else if (choice == 3)
            exit(0);
    } while (choice >= 3);
}
void authentication()
{
    string check;
    string text_read;
    string username, pass;

    while (loginAttempt <= 2)
    {
        cout << endl
             << "Please enter your username: ";
        cin >> username;
        cout << endl
             << "Please enter your user password: ";
        cin >> pass;

        if (auth_check(username, pass))
        {
            cout << endl
                 << "\n\t   \t\t\t\t\t\t\t\t\t\t ----------------------------" << endl;
            cout << endl
                 << "\n\t   \t\t\t\t\t\t\t\t\t  Logged in Successfully!"
                 << endl;
            admin_menu();
        }
        else
        {
            cout << endl
                 << "\n\t   \t\t\t\t\t\t\t ----------------------------" << endl;
            cout << endl
                 << "\n\t   \t\t\t\t\t\t\t\t\t  Log in detail Incorrect!"
                 << endl;
            loginAttempt++;
            authentication();
        }
        if (loginAttempt == 3)
        {
            cout << endl
                 << "Too many login attempts! The program will now terminate." << endl;
            exit(0);
        }
    }
    return;
}
bool auth_check(const string &username, const string &pass)
{
    ifstream file("authentication.txt");
    string fusername, fpassword;
    while (file)
    {
        getline(file, fusername, ',');
        getline(file, fpassword);

        if (fusername == username && fpassword == pass)
            return true;
    }
    return false;
}