#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "admin.h"
#include "user_menu.h"
#include "main_menu.h"
#include "new_user.h"
#include "existing_user.h"
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

struct vehicle_search
{
    int id;
    string type;
    string licensePlate;
    string model;
    int capacity;
    int rateperHr;
    string transmission;
    vehicle_search *next;
};

void billGeneration(int ,int,int);
void readDatafromFile(const string &filename, vehicle_search *&head);
void cost(int,int);
vehicle_search *searchItem(const vehicle_search *head, int targetId);
void displayLinkedList(const vehicle_search *head);
void readDatafromFile(const string &filename, vehicle_search *&head);
void vehicle_detail(string file2);


int existing_user()
{
    string phone_number;
    cout << "\nEnter phone number:" ;
    getline(cin, phone_number);
    checking_user("user_data.txt", "vehicle_data.txt", phone_number);
}
void checking_user(string filename, string file2, string phone_number)
{
    string line, extract;
    int count = 0;
    ifstream file(filename, ios::in | ios::app);
    while (getline(file, line))
    {
        verification(line, phone_number, &count);
    }
    file.close();
    if (count == 0)
    {
        cout << "\nUser not registered!!!";
        return;
    }
    if (count != 0)
    {
        vehicle_detail(file2);
        return;
    }
}
void verification(string line, string phone_number, int *count)
{
    stringstream ss(line);
    string word;
    // extracting each deatil liike name,phone number and addrress
    while (ss >> word)
    {
        if (word == phone_number)
        {
            ++(*count);
            cout << "\n User found....." << endl;
        }
    }
}
void vehicle_detail(string file2)
{
    string  line_d, confirmation_detail, detail;
    int vehicle_id,time_for_rent;
    cout << "\n Select Vehicle For Rent....." << endl;
    ifstream file(file2, ios::out | ios::in);
    while (file.good())
    {
        getline(file, line_d);
        cout << line_d << endl;
    }
    file.close();
    cout << "\n Fill detail for vehicle rent:" << endl;
    cout << "\n Enter vehicle ID:";
    cin >> vehicle_id;

    cout << "\n Enter time for rent in (hours) :";
    cin >> time_for_rent;

    cout << "\n Confirm your Details:" << endl;
    cout << "\n Vehicle ID " << vehicle_id << endl;
    cout << "\n Time for rent:" << time_for_rent << endl;

    cout << "\n Enter YES/NO:";
    cin >> confirmation_detail;
    if (confirmation_detail == "NO" || confirmation_detail == "no")
    {
        cout << "\n Login again" << endl;
        return;
    }
    cout << "\n Do you want to Generate your Bill \n";
    cout << "\n Enter Yes or No:";
    cin >> detail;
    if (confirmation_detail == "NO" || confirmation_detail == "no")
    {
        cout << "\n Login again" << endl;
        return;
    }
    cost(vehicle_id,time_for_rent);

    cout << "\n Thank you" << endl;
}

void readDatafromFile(const string &filename, vehicle_search *&head)
{
    ifstream inputFile("vehicle_data.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    string line;
    while (std::getline(inputFile, line))
    {
        vehicle_search *newNode = new vehicle_search;
        istringstream iss(line);

        iss >> newNode->id >> newNode->type >> newNode->licensePlate >> newNode->model >> newNode->capacity >> newNode->rateperHr >> newNode->transmission;

        newNode->next = head;
        head = newNode;
    }

    inputFile.close();
}
void displayLinkedList(const vehicle_search *head)
{
    const vehicle_search *current = head;

    while (current != nullptr)
    {
        std::cout << current->id << "\t" << current->type << "\t"
                  << current->licensePlate << "\t" << current->model << "\t"
                  << current->capacity << "\t" << current->rateperHr << "\t"
                  << current->transmission << "\n";
        current = current->next;
    }
}
vehicle_search *searchItem(const vehicle_search *head, int targetId)
{
    const vehicle_search *current = head;

    while (current != nullptr)
    {
        if (current->id == targetId)
        {
            return const_cast<vehicle_search *>(current); // Casting away const for demonstration purposes
        }
        current = current->next;
    }

    return nullptr; // Item not found
}

void cost(int vehicle_id,int time_for_rent)
{
    vehicle_search *head = nullptr;

    // Replace "your_filename.txt" with the actual filename containing your data
    readDatafromFile("vehicle_data.txt", head);

    // Display the linked list
   // std::cout << "\nLinked List:\n";
   // displayLinkedList(head);

    // Search for an item
    int targetId;
    std::cout << "\n Enter the ID to search: ";
    std::cin >> targetId;

    vehicle_search *foundItem = searchItem(head, targetId);

    if (foundItem != nullptr)
    {
        //std::cout << "Item found:\n";
        std::cout << foundItem->id << "\t" << foundItem->type << "\t"
                  << foundItem->licensePlate << "\t" << foundItem->model << "\t"
                  << foundItem->capacity << "\t" << foundItem->rateperHr << "\t"
                  << foundItem->transmission << "\n";
    }
    else
    {
        std::cout << " Item not found.\n";
    }

    cout << "The Rate per Hr for vehicle \t" << foundItem->type << "\tis\t" << foundItem->rateperHr;

    int farePrice = foundItem->rateperHr;

    // Clean up memory
    while (head != nullptr)
    {
        vehicle_search *temp = head;
        head = head->next;
        delete temp;
    }

    billGeneration(farePrice,vehicle_id,time_for_rent);
    return;
}
void billGeneration(int farePrice,int vehicle_id,int time_for_rent)
{
    float bill, time, disPer, rateOfInterest, discount, ratePer;
    time =  time_for_rent;

    cout << "\nYour total time rented is (hrs):";
    cout<< time;

    cout << "\nEnter the discount(%) (if applicable):";
    cin >> disPer;

    cout << "\nEnter the rate of interest(%) (if Exceeded time Limit ):";
    cin >> ratePer;

    discount = ((disPer * farePrice) / 100);
    cout << "\n in discountt \n";
    cout << discount << endl;

    rateOfInterest = ((ratePer * farePrice) / 100);

    bill = (farePrice * time) - discount + rateOfInterest;
    bill = round(bill);

    // cout<<"\n\n  Your Bill is: ";

    cout << setfill('-') << setw(48) << "" << setfill(' ') << endl;

    cout << "|\t\t YOUR  BILL\t\t\t|" << endl;
    cout << setfill('-') << setw(48) << "" << setfill(' ') << endl;

    // Fare Price (Per Hour)
    cout << "| Fare Price (Per Hour)    " << setw(5) << right << " | " << setw(10) << farePrice << setw(5) << right << " |" << endl;

    // Total Time rented
    cout << "| Total Time rented        " << setw(5) << right << " | " << setw(10) << time << setw(5) << " |" << endl;

    // Discount
    cout << "| Discount                 " << setw(5) << right << " | " << setw(10) << discount << setw(5) << " |" << endl;

    // Rate of Interest
    cout << "| Rate of Interest         " << setw(5) << right << " | " << setw(10) << rateOfInterest << setw(5) << " |" << endl;

    // Total Bill
    cout << setfill('-') << setw(48) << "" << setfill(' ') << endl;
    cout << "| Total Bill               " << setw(5) << right << " | " << setw(10) << bill << setw(5) << " |" << endl;
    cout << setfill('-') << setw(48) << "" << setfill(' ') << endl;
    return;
}