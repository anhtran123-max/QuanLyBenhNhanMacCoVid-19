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
        void setId(string id);
        void setName(string name);
        void setAddress(string address);
        void setStatus(int status);
        void setInfect(string infection);
        void setPlace(string place);
        void setQ_day(int q_day);
        string getId();
        string getName();
        string getAddress();
        int getStatus();
        string getInfect();
        string getPlace();
        int getQ_day();
        friend istream& operator>>(istream &input, Patient &patient); // nhap
        friend ostream& operator<<(ostream &ouput, Patient patient); //xuat (Minh design)TODO:
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
bool checkStatus(int status){
    if(status == 0 || status == 1 || status == 2) return true;
    return false;
}
void Patient::setId(string id){
    this->id=id;
}
void Patient::setName(string name){
    this->name=name;
}
void Patient::setAddress(string address){
    this->address=address;
}
void Patient::setStatus(int status){
    this->status=status;
}
void Patient::setInfect(string infection){
    this->infection=infection;
}
void Patient::setPlace(string place){
    this->place=place;
}
void Patient::setQ_day(int q_day){
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
    fflush(stdin);
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
    fflush(stdin);
    getline(input,patient.address);
    do{
        cout<<"NOTE - input status: healthy=0, lightly=1, heavily =2";
        cout<<"Status: ";
        fflush(stdin);
        input>>patient.status;
        if(!checkStatus(status)) cout<<"Error, enter again!"<<endl;
    }while(!checkStatus(status));
    cout<<"Infection: ";
    input>>patient.infection;
    cout<<"Quarantine place: ";
    fflush(stdin);
    getline(input,patient.place);
    cout<<"Day need to quarantine: ";
    fflush(stdin);
    input>>patient.q_day;
    return input;
}
ostream& operator<<(ostream& output, Patient patient){
    output<<"Id: "<<patient.id<<", Name: "<<patient.name<<" ("<<patient.getDay()<<","<<patient.getMonth()<<","<<patient.getYear()<<")"<<", Address: "<<patient.address<<endl;
    output<<"Status: "<<patient.status<<", Infection: "<<patient.infection<<", Quarantine place: "<<patient.place<<", Day need to quarantine: "<<patient.q_day<<endl;
}