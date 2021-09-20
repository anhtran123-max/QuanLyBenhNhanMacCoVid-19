#include<bits/stdc++.h>

class DateTime{
    private:
        int day;
        int month;
        int year;
    public:
        DateTime();
        DateTime(int day, int month, int year);
        int setDay();
        int satMonth();
        int setYear();
        int getDay();
        int getMonth();
        int getYear();
};
