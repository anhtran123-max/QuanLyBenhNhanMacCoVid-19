#pragma once
#include<bits/stdc++.h>
using namespace std;
class Person{
    private:
        string id;
        string name;
        string address;
        int day;
        int month;
        int year;
    public:
        Person();
        ~Person(){}
        Person(string id, string name, string address, int day, int month, int year);
        Person(const Person& other);
        void setId(string id);
        void setName(string name);
        void setAddress(string address);
        void setDay(int day);
        void setMonth(int month);
        void setYear(int year);
        string getId();
        string getName();
        string getAddress();
        int getDay();
        int getMonth();
        int getYear();
        friend istream& operator>>(istream& input, Person &person);
};
Person::Person(){
    this->id = "";
    this->name = "";
    this->address = "";
    this->day = 0;
    this->month = 0;
    this->year = 0;
}
Person::Person(string id, string name, string address, int day, int month, int year){
    this->id = id;
    this->name = name;
    this->address = address;
    this->day = day;
    this->month = month;
    this->year = year;
}
Person::Person(const Person& other){
    *this = other;
}
void Person::setId(string id){
    this->id = id;
}
void Person::setName(string name){
    this->name = name;
}
void Person::setAddress(string address){
    this->address = address;
}
void Person::setDay(int day) {
    this->day = day;
}
void Person::setMonth(int month) {
    this->month = month;
}
void Person::setYear(int year) {
    this->year = year;
}
string Person::getId(){
    return id;
}
string Person::getName(){
    return name;
}
string Person::getAddress(){
    return address;
}
int Person::getDay(){
    return day;
}
int Person::getMonth(){
    return month;
}
int Person::getYear(){
    return year;
}
bool timeTest(int day, int month, int year){//hàm ngoài
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
istream& operator>>(istream &input, Person& person){
    cout<<"id: ";
    input>>std::ws;//skip whitespace
    input>>person.id;
    cout<<"Name: ";
    input>>std::ws;
    getline(input,person.name);
    cout<<"-Birthday: "<<endl;
    do{
        cout<<"Day: ";
        input>>person.day;
        cout<<"Month: ";
        input>>person.month;
        cout<<"Year: ";
        input>>person.year;
        if(!timeTest(person.day, person.month, person.year)) cout<<"Error, enter again!"<<endl;
    }while(!timeTest(person.day, person.month, person.year));
    cout<<"Address: ";
    input>>std::ws;
    getline(input, person.address);
    return input;
}