#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include "admin.h"
#include "main_menu.h"

int loginAttempt = 0;
using namespace std;

struct Vehicle
{
    int id;
    string type;
    string licensePlate;
    string model;
    int capacity;
    int rateperHr;
    string transmission;
    Vehicle *next;
};

/*function declaration*/
int add_vehicle();
void delete_vehicle();
void display();
void readDatafromFile(const string &filename, Vehicle *&head);
void displayLinkedList(const Vehicle *head);
void deleteNodeById(Vehicle *&head, int targetId);
Vehicle *searchItem(const Vehicle *head, int targetId);
void writeDataToFile(const std::string &filename, const Vehicle *head);
/*function declaration*/

void admin_menu()
{
    int choice;
     cout << endl
             << "\n\t   \t\t\t\t\t\t\t ----------------------------" << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     1. NEW ADMIN   " << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     2. ADD VEHICLE   " << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     3. DELETE VEHICLE  " << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     4. DISPLAY " << endl;
        cout << "\n\t   \t\t\t\t\t\t\t\t     5. MAIN MENU " << endl;

        cout << "\n\t   \t\t\t\t\t\t\t\t     ENTER YOUR CHOICE :    ";
        cin >> choice;
    if (choice == 1)
    {
        new_admin();
        admin_menu();
    }
    else if (choice == 2)
    {
        add_vehicle();
        admin_menu();
    }
    else if (choice == 3)
    {
        delete_vehicle();
        admin_menu();
    }
    else if (choice == 4)
    {
        display();
        admin_menu();
    }
    else if (choice == 5)
    {
        main_menu();
    }
}
void new_admin()
{
    string check_existing;
    fstream checkfile("authentication.txt", ios::in);
    if (!checkfile)
    {
        cout << "Failed to read";
    }
    checkfile >> check_existing;
    string new_username, new_password;
    cout << "Enter the new admin username: ";
    cin >> new_username;
    bool is_admin_existing = check_existing.find(new_username) != string::npos;
    checkfile.close();
    if (is_admin_existing)
    {
        cout << "The username already exists..";
        cout << endl
             << "Please use another username";
        new_admin();
    }
    else
    {
        cout << endl
             << "Enter the new admin password: ";
        cin >> new_password;
        ofstream input("authentication.txt", ios::app);
        if (!input.is_open())
        {
            cout << "Failed to read";
        }

        input << endl
              << new_username << "," << new_password;
        input.close();
    }
}
int add_vehicle()
{
    fstream out("vehicle_data.txt", ios::out | ios::app);
    char type[20], trans[5], model[20], cap[20], fare[20], number[20];
    int id;
    cout << "Vehicle ID:";
    cin >> id;
    cin.ignore(1, '\n');
    cout << "Vehicle type:";
    cin.getline(type, 20);
    cin.ignore(0, '\n');
    cout << "Vehicle Number:";
    cin.getline(number, 20);
    cin.ignore(0, '\n');
    cout << "Model No:";
    cin.getline(model, 20);
    cin.ignore(0, '\n');
    cout << "Capacity:";
    cin.getline(cap, 20);
    cin.ignore(0, '\n');
    cout << "Fare:";
    cin.getline(fare, 20);
    cin.ignore(0, '\n');
    cout << "Tansmission:";
    cin.getline(trans, 5);
    cin.ignore(0, '\n');
    out << id << "\t\t" << type << "\t\t" << number << "\t\t" << model << "\t\t" << cap << "\t\t" << fare << "\t\t"
        << trans << endl;
    out.close();
}
void display()
{
    int dis;
    string read;
    //cout << "\n1.Display Data \n";
    //cout << "Enter your choice:";
    //cin >> dis;
    //if (dis == 1)
    //{
        cout << "\nVehicle Id"
             << "\t"
             << "Vehicle Type"
             << "\t"
             << "Vehicle Number"
             << "\t"
             << "Model Number"
             << "\t"
             << "Capacity"
             << "\t"
             << "Fare"
             << "\t"
             << "Transmission" << endl;
        fstream in("vehicle_data.txt", ios::in);
        while (in.eof() == 0)
        {
            getline(in, read);
            cout << "\n"
                 << read << endl;
        }
        in.close();
   // } // incomplete display func
    //else
    //    printf("Wrong Choice!!!!");
}

void delete_vehicle()
{
    Vehicle *head = nullptr;

    // Replace "your_filename.txt" with the actual filename containing your data
    readDatafromFile("vehicle_data.txt", head);

    // Display the linked list before deletion

    displayLinkedList(head);

    // Delete a node by ID
    int targetId;
    std::cout << "\nEnter the ID to delete: ";
    std::cin >> targetId;

    deleteNodeById(head, targetId);

    // Display the linked list after deletion

    displayLinkedList(head);

    // Update the file after deletion
    writeDataToFile("vehicle_data.txt", head);

    // Clean up memory
    while (head != nullptr)
    {
        Vehicle *temp = head;
        head = head->next;
        delete temp;
    }
}
void readDatafromFile(const string &filename, Vehicle *&head)
{
    ifstream inputFile("vehicle_data.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        Vehicle *newNode = new Vehicle;
        istringstream my_stream(line);

        my_stream >> newNode->id >> newNode->type >> newNode->licensePlate >> newNode->model >> newNode->capacity >> newNode->rateperHr >> newNode->transmission;

        newNode->next = head;
        head = newNode;
    }

    inputFile.close();
}
void displayLinkedList(const Vehicle *head)
{
    const Vehicle *current = head;

    while (current != nullptr)
    {
        std::cout << current->id << "\t" << current->type << "\t"
                  << current->licensePlate << "\t" << current->model << "\t"
                  << current->capacity << "\t" << current->rateperHr << "\t"
                  << current->transmission << "\n";
        current = current->next;
    }
}
void deleteNodeById(Vehicle *&head, int targetId)
{
    Vehicle *current = head;
    Vehicle *prev = nullptr;

    // Traverse the list to find the node with the target ID
    while (current != nullptr && current->id != targetId)
    {
        prev = current;
        current = current->next;
    }

    // If the node with the target ID is found
    if (current != nullptr)
    {
        // Update the linked list
        if (prev == nullptr)
        {
            // If the target node is the first node
            head = current->next;
        }
        else
        {
            prev->next = current->next;
        }

        // Delete the node
        delete current;
    }
}
Vehicle *searchItem(const Vehicle *head, int targetId)
{
    const Vehicle *current = head;

    while (current != nullptr)
    {
        if (current->id == targetId)
        {
            return const_cast<Vehicle *>(current); // Casting away const for demonstration purposes
        }
        current = current->next;
    }

    return nullptr; // Item not found
}
void writeDataToFile(const std::string &filename, const Vehicle *head)
{
    std::ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    const Vehicle *current = head;

    while (current != nullptr)
    {
        outputFile << current->id << "\t" << current->type << "\t"
                   << current->licensePlate << "\t" << current->model << "\t"
                   << current->capacity << "\t" << current->rateperHr << "\t"
                   << current->transmission << "\n";

        current = current->next;
    }

    outputFile.close();
}