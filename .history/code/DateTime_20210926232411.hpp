#pragma once
#include<bits/stdc++.h>
using namespace std;
class Datetime{
    private:
        int day;
        int month;
        int year;
    public:
        Datetime();
        ~Datetime(){}
        Datetime(int day, int month, int year);
        void setDay(int day);
        void setMonth(int month);
        void setYear(int year);
        int getDay();
        int getMonth();
        int getYear();
};
Datetime::Datetime(){
    this->day = 0;
    this->month = 0;
    this->year = 0;
}
Datetime::Datetime(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}
void Datetime::setDay(int day) {
    this->day = day;
}
void Datetime::setMonth(int month) {
    this->month = month;
}
void Datetime::setYear(int year) {
    this->year = year;
}
int Datetime::getDay(){
    return day;
}
int Datetime::getMonth(){
    return month;
}
int Datetime::getYear(){
    return year;
}
