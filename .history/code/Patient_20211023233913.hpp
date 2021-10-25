#pragma once
#include "Person.hpp"
#include <bits/stdc++.h>
using namespace std;
class Patient:public Person {
    private:
        int status;//tinh trang: 0 neu khoe, 1 benh nhe, 2 benh nang
        string infection; //nguon lay "NO" la F0 hoac id cua nguoi trươc do
        int injection;//so mui tiem: 0, 1 hoac 2
        string place; //noi cach ly
        int q_day; // so ngay cach ly
    public:
        Patient(): Person(){
            this->status = 0;
            this->infection = "NO";
            this->place = "";
            this->q_day = 0;
        }
        ~Patient(){}
        Patient(string id, string  name, int day, int month, int year, string address, int status, string infection, string place, int q_day): Person(id, name, address, day, month, year){
            this->status = status;
            this->infection = infection;
            this->place = place;
            this->q_day = q_day;
        }
        Patient(const Patient &other){
            *this = other;
        }
        void setStatus(int status);
        void setInfect(string infection);
        void setPlace(string place);
        void setQ_day(int q_day);
        int getStatus();
        string getInfect();
        int getInJect();
        string getPlace();
        int getQ_day();
        friend istream& operator>>(istream &input, Patient &patient); // nhap
        friend ostream& operator<<(ostream &ouput, Patient patient); //xuat (Minh design)TODO:
};
bool check(int status){
    return (status == 0 || status == 1 || status == 2);
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
int Patient::getStatus(){
    return status;
}
string Patient::getInfect(){
    return infection;
}
int Patient::getInJect(){
    return injection;
}
string Patient::getPlace(){
    return place;
}
int Patient::getQ_day(){
    return q_day;
}
istream& operator>>(istream &input, Patient &patient){
    Person *p = static_cast<Person *>(&patient);
    input>> *p;
    do{
        cout<<"NOTE - input status: healthy=0, lightly=1, heavily =2"<<endl;
        cout<<"Status: ";
        fflush(stdin);
        input>>patient.status;
        if(!check(patient.status)) cout<<"Error, enter again!"<<endl;
    }while(!check(patient.status));
    cout<<"NOTE - input infection: 'NO' or id of before patients"<<endl;
    cout<<"Infection: ";
    input>>patient.infection;
    do{
        cout<<"Injection: ";
        input>>patient.injection;
        if(!check(patient.injection)) cout<<"Error, enter again!"<<endl;
    }while(!check(patient.injection));
    cout<<"NOTE - input quarantine place: 1.TK-PLAZA, 2.TD, 3.Q9"<<endl;
    cout<<"Quarantine place: ";
    fflush(stdin);
    getline(input,patient.place);
    cout<<"Day need to quarantine: ";
    fflush(stdin);
    input>>patient.q_day;
    return input;
}
ostream& operator<<(ostream& output, Patient patient){
    output<<"Id: "<<patient.getId()<<", Name: "<<patient.getName()<<" ("<<patient.getDay()<<","<<patient.getMonth()<<","<<patient.getYear()<<")"<<", Address: "<<patient.getAddress()<<endl;
    output<<"Status: "<<patient.status<<", Infection: "<<patient.infection<<", Quarantine place: "<<patient.place<<", Day need to quarantine: "<<patient.q_day<<endl;
    return output;
}