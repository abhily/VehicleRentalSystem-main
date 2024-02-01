#include <iostream>
#include<stdlib.h>
#include<fstream>
#include"user_menu.h"
#include"main_menu.h"
#include"new_user.h"
#include"existing_user.h"

using namespace std;

void user_menu()
{
    
    int choice;
    while(1)
    {
         cout << endl
             << "\n\t   \t\t\t\t\t\t\t\t----------------------------" << endl;
        cout << endl
             << "\n\t   \t\t\t\t\t\t\t\t     USER MENU   " << endl;
        cout << endl
             << "\n\t   \t\t\t\t\t\t\t\t----------------------------" << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     1.  NEW USER   " << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     2.  EXISTING USER   " << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     3.  MAIN MENU   " << endl;
        
        cout << "\n\t   \t\t\t\t\t\t\t\t     ENTER YOUR CHOICE :    ";
        cin>>choice;
        cin.ignore();
        switch(choice)
        {
            case 1: new_user();
                    break;
            case 2:existing_user();
                        break;
            case 3:main_menu();
                   break;
            default:cout<<"wrong choice!";
        }
    }
    return ;
}
