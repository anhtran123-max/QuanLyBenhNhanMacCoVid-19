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
    this->id = other.id;
    this->name = other.name;
    this->address = other.address;
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
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
