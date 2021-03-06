#pragma once
#include "DateTime.hpp"
#include <bits/stdc++.h>
using namespace std;
class Patient:public Datetime {
    private:
        string id;
        string name;
        string address;
        int status;//tinh trang: 0 neu khoe, 1 neu dang benh
        string infection; //nguon lay "NO" la F0 hoac id cua nguoi trươc do
        string place; //noi cach ly
        int q_day; // so ngay cach ly
    public:
        Patient(): Datetime(){
            this->id = "";
            this->name = "";
            this->address = "";
            this->status = 0;
            this->infection = "NO";
            this->place = "";
            this->q_day = 0;
        }
        ~Patient(){}
        Patient(string id, string  name, int day, int month, int year, string address, int status, string infection, string place, int q_day): Datetime(day, month, year){
            this->id = id;
            this->name = name;
            this->address = address;
            this->status = status;
            this->infection = infection;
            this->place = place;
            this->q_day = q_day;
        }
        void setId();
        void setName();
        void setAddress();
        void setStatus();
        void setInfect();
        void setPlace();
        void setQ_day();
        string getId();
        string getName();
        string getAddress();
        int getStatus();
        string getInfect();
        string getPlace();
        int getQ_day();
        friend istream& operator>>(istream &input, Patient &patient); // nhap
        void display();// xuat
};
bool timeTest(int day, int month, int year){
    if (year<0 || month<0 || month> 12 || day<0 || day> 31) return false;
    if(month==1 || month ==3 || month == 5 || month ==7 || month ==8 || month ==10 || month==12){
        if(day <= 31) return true;
    }
    if(month==4 || month ==6 || month == 9 || month ==11){
        if(day <= 30) return true;
    }  
    if(year %4 ==0 && year !=0){
        if(day <= 29) return true;
    }  
    else{
        if(day <= 28) return true;
    }
    return false;
}
void Patient::setId(){
    this->id=id;
}
void Patient::setName(){
    this->name=name;
}
void Patient::setAddress(){
    this->address=address;
}
void Patient::setStatus(){
    this->status=status;
}
void Patient::setInfect(){
    this->infection=infection;
}
void Patient::setPlace(){
    this->place=place;
}
void Patient::setQ_day(){
    this->q_day=q_day;
}
string Patient::getId(){
    return id;
}
string Patient::getName(){
    return name;
}
string Patient::getAddress(){
    return address;
}
int Patient::getStatus(){
    return status;
}
string Patient::getInfect(){
    return infection;
}
string Patient::getPlace(){
    return place;
}
int Patient::getQ_day(){
    return q_day;
}
istream& operator>>(istream &input, Patient &patient){
    int day, month, year;
    cout<<"id: ";
    input>>patient.id;
    cout<<"Name: ";
    cin.ignore();
    getline(input,patient.name);
    cout<<"-Birthday: "<<endl;
    do{
    cout<<"Day: ";
    input>>day;
    cout<<"Month: ";
    input>>month;
    cout<<"Year: ";
    input>>year;
    if(!timeTest(day, month, year)) cout<<"Error, enter again!"<<endl;
    }while(!timeTest(day,month,year));
    patient.setDay(day);
    patient.setMonth(month);
    patient.setYear(year);
    cout<<"Address: ";
    cin.ignore();
    getline(input,patient.address);
    cout<<"Status: ";
    cin.ignore();
    input>>patient.status;
    cout<<"Infection: ";
    input>>patient.infection;
    cout<<"Quarantine place: ";
    cin.ignore();
    getline(input,patient.place);
    cout<<"Day need to quarantine: ";
    cin.ignore();
    input>>patient.q_day;
    return input;
}