#include "Patient.hpp"
#include<bits/stdc++.h>

class Node {
    public:
        Patient data;
        Node *left;
        Node *right;
        Node(Patient data){
            this->data = data;
            left = NULL;
            right = NULL;
        }
};
class BST {
    private:
        Node *root;
    public: 
        BST(){ //constructor
            root = NULL;
        }
        bool existPatient(); //kiểm tra trùng id
        bool validInfection(); //kiểm tra trùng Id F0 là “NO”, các id của F khác k đc trùng nhau
        Node* add(Node* root, Patient val);
        Node* search(Node* root, Patient val);//tìm kiếm
        Node* erase(Node* root, Patient val);//xóa 
        void edit(); //sửa bệnh nhân
        void sort(); //dùng hàm sort có sẵn kết hợp thêm 1 class Compare để so sánh và sắp xếp
        void statistics(); //thống kê theo nơi điều trị
        void F(); //thống kê các F (nếu có map thì dùng, k thì thoi)
        void maxQ_day(); //các bệnh nhân có số ngày cách ly lâu (>21 ngày)
        void exportPatients(); //xuất file
        void function(void); //hàm thực thi các thao tác
};
//TODO: viết 2 hàm bool
Node* BST::add(Node* root, Patient val) {
    if(root == NULL) return new Node(val);
    if(val.getId()<root->data.getId())
        root->left = add(root->left, val);
    else
        root->right = add(root->right, val);
    return root;
}
void BST::function(void){
    Patient a,b,c;
    cin>>a>>b>>c;
    root = add(root,a);
    root = add(root,b);
    root = add(root,c);
}