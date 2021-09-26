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
        friend istream& operator>>(istream &input, Patient &patient); // nhap
        void display();// xuat
};
//TODO: viết các hàm setter và getter
//TODO: thêm hàm kiểm tra ngày tháng năm
istream& operator>>(istream &input, Patient &patient){
    int day, month, year;
    cout<<"id: ";
    input>>patient.id;
    cout<<"Name: ";
    fflush(stdin);
    getline(input,patient.name);
    cout<<"Birthday: "<<endl;
    cout<<"Day: ";
    input>>day;
    patient.setDay(day);
    cout<<"Month: ";
    input>>month;
    patient.setMonth(month);
    cout<<"Year: ";
    input>>year;
    patient.setYear(year);
    cout<<"Address: ";
    fflush(stdin);
    getline(input,patient.address);
    cout<<"Status: ";
    fflush(stdin);
    input>>patient.status;
    cout<<"Infection: ";
    input>>patient.infection;
    cout<<"Quarantine place: ";
    fflush(stdin);
    getline(input,patient.place);
    cout<<"Day need to quarantine: ";
    fflush(stdin);
    input>>patient.q_day;
}