#include <iostream>
#include<stdlib.h>
#include<fstream>
#include"user_menu.h"
#include"main_menu.h"
using namespace std;

int existing_user();
void checking_user(string filename,string file2,string phone_number);
void verification(string line,string phone_number,int *count);
void vehicle_detail(string file2);