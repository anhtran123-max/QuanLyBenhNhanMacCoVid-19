#include "Patients.hpp"
#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

int main(){
    BST list;
    char password[6];
    char check_password[6] = "12345";
    int i, time = 3;
    cout << "Please enter password (5 characters): ";
    while(1){
    for(i = 0; i < 5; i++){               
        password[i] = getch();
        cout << "*";
    }
    password[i] = '\0';
    if(strcmp(check_password,password) == 0){
        list.function();
        fflush(stdin);
        getchar();
    } else {
        cout << "\n----------------------------------------------------";
        cout << "\nYou still have " << time << " access" << endl;
        time--;
        if(time == -1){
            break;
        }
        cout << "Please enter password (5 characters): ";
            }
        }
    cout << "Good bye";
    return 0;
}
