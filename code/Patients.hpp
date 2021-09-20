#include<bits/stdc++.h>

class Patients {
    private:
        vector<Patient>list;
    public: 
        Patients(){
            list = vector<Patient>();
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