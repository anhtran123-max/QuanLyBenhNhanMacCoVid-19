#include<bits/stdc++.h>

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
        Patient();
        Patient(string id, string  name, int day, int month, int year, string address, int status, string infection, string place, int q_day): DateTime(day, month, year);
        string setId() const;
        string setName() const;
        string setAddress() const;
        int setStatus() const;
        string setInfect() const;
        string setPlace() const;
        int setQ_day() const;
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