#include "Patient.hpp"
#include <bits/stdc++.h>
using namespace std;
Patient::Patient(): DateTime(){
    this->id = 0;
    this->name = "";
    this->address = "";
    this->status = 0;
    this->infection = "NO";
    this->place = "";
    this->q_day = 0;
}
Patient::Patient(string id, string  name, int day, int month, int year, string address, int status, string infection, string place, int q_day): DateTime(day, month, year){
    this->id = id;
    this->name = name;
    this->address = address;
    this->status = status;
    this->infection = infection;
    this->place = place;
    this->q_day = q_day;
}