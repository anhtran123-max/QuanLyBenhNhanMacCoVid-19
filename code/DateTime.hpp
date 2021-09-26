#include<bits/stdc++.h>
using namespace std;
class DateTime{
    private:
        int day;
        int month;
        int year;
    public:
        DateTime();
        ~DateTime();
        DateTime(int day, int month, int year);
        int setDay();
        int satMonth();
        int setYear();
        int getDay();
        int getMonth();
        int getYear();
};
DateTime::DateTime(){
    this->day = 0;
    this->month = 0;
    this->year = 0;
}
DateTime::DateTime(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}