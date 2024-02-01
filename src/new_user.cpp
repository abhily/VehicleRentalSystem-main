#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "admin.h"
#include "user_menu.h"
#include "main_menu.h"
#include "new_user.h"
using namespace std;
using namespace std;

struct node
{
    string name;
    string address;
    string ph_no; // ph_no: Phone number
    struct node *link;
};
typedef struct node *NODE;
NODE first = NULL;

/* declartion of functions used*/
NODE get_node();
void put_intofile(string filename, NODE temp);
string confirmation(NODE temp);
/* declartion of functions used*/


int new_user()
{   
   
    first = get_node();
    put_intofile("user_data.txt", first);
    cout << "\nUSER ADDED SUCCESSFULLY";
}
NODE get_node()
{
    NODE temp;
    string choice;
    temp = new struct node;
    cout << "Enter name: ";
    getline(cin, temp->name);
    cout << "Enter phone number:";
    getline(cin, temp->ph_no);
    cout << "Enter address: ";
    getline(cin, temp->address);
    choice = confirmation(temp);
    if (choice == "NO" || choice  == "no" || choice == "N" || choice == "n")
    {
        delete temp;
        cout << "Re-enter details\n";
        return get_node();
    }
    else
    {
        return temp;
    }
}

void put_intofile(string filename, NODE temp)
{
    ofstream file(filename, ios::out | ios::app);
    file << temp->name << "\t";
    file << temp->ph_no << "\t";
    file << temp->address << "\t" << endl;
    file.close();
}
string confirmation(NODE temp)
{
    string choice;
    cout << "\nConfirm your details\n";
    cout << "Name:" << temp->name <<"\n";
    cout << "Phone number: " << temp->ph_no <<"\n";
    cout << "Address: " << temp->address;
    cout << "\nYES or NO\n";
    cin >> choice;
    cin.ignore();
    return choice;
}