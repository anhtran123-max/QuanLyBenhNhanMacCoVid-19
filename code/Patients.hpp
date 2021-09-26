#include "Patient.hpp"
#include<bits/stdc++.h>

class Node {
    public:
        Patient data;
        Node *next;
        Node();//constructor
};
class LinkedList {
    private:
        Node *head;
        Node *tail;
    public: 
        LinkedList(){ //constructor
            head = NULL;
            tail = NULL;
        }
        bool existPatient(); //kiểm tra trùng id
        bool validInfection(); //kiểm tra trùng Id F0 là “NO”, các id của F khác k đc trùng nhau
        void add(); //thêm vào cuối (dùng hàm có sẵn push_back)
        void erase(); //xóa bệnh nhân(dùng hàm find và erase có sẵn)
        void edit(); //sửa bệnh nhân
        void findPatient(); //dùng hàm find có sẵn
        void sort(); //dùng hàm sort có sẵn kết hợp thêm 1 class Compare để so sánh và sắp xếp
        void statistics(); //thống kê theo nơi điều trị
        void F(); //thống kê các F (nếu có map thì dùng, k thì thoi)
        void maxQ_day(); //các bệnh nhân có số ngày cách ly lâu (>21 ngày)
        void exportPatients(); //xuất file

};