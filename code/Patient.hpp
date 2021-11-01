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
        virtual void toStream(istream& input);
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
void Patient::toStream(istream& input){
    Person::toStream(input);
    do{
        cout<<"NOTE - input status: healthy=0, lightly=1, heavily =2"<<endl;
        cout<<"Status: ";
        input>>std::ws;
        input>>status;
        if(!check(status)) cout<<"Error, enter again!"<<endl;
    }while(!check(status));
    cout<<"NOTE - input infection: 'NO' or id of before patients"<<endl;
    cout<<"Infection: ";
    input>>infection;
    do{
        cout<<"Injection: ";
        input>>injection;
        if(!check(injection)) cout<<"Error, enter again!"<<endl;
    }while(!check(injection));
    cout<<"Quarantine place: ";
    input>>std::ws;
    getline(input,place);
    cout<<"Day need to quarantine: ";
    input>>std::ws;
    input>>q_day;
}
ostream& operator<<(ostream& output, Patient patient){
    output<<patient.getId()<<"\t|\t"<<patient.getName()<<"\t|\t"<<patient.getDay()<<"/"<<patient.getMonth()<<"/"<<patient.getYear()<<"\t|\t\t"<<patient.getAddress()
    <<"\t\t|\t"<<patient.status<<"\t|\t"<<patient.infection<<  "\t|\t"  << patient.injection <<"\t|\t"<<patient.place<<"\t|\t"<<patient.q_day<<"\t|"<<endl;
    output<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    return output;
}