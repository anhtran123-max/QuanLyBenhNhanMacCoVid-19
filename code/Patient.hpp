#include "DateTime.hpp"
#include<bits/stdc++.h>
using namespace std;
class Patient : public DateTime{
    private:
        string id;
        string name;
        string address;
        int status;//tinh trang: 0 neu khoe, 1 neu dang benh
        string infection; //nguon lay "NO" la F0 hoac id cua nguoi trươc do
        string place; //noi cach ly
        int q_day; // so ngay cach ly
    public:
        Patient(): DateTime();
        Patient(string id, string  name, int day, int month, int year, string address, int status, string infection, string place, int q_day): DateTime(day, month, year);
        string setId();
        string setName();
        string setAddress();
        int setStatus();
        string setInfect();
        string setPlace();
        int setQ_day();
        string getId() const;
        string getName() const;
        string getAddress() const;
        int getStatus() const;
        string getInfect() const;
        string getPlace() const;
        int getQ_day() const;
        friend istream(); // nhap
        display();// xuat
};
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