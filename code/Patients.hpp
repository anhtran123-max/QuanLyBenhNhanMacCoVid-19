#include "Patient.hpp"
#include "Doubly.hpp"
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
        int size;
    public: 
        BST(){ //constructor
            root = NULL;
            size = 0;
        }
        bool existPatient(Node* root, string id); //kiểm tra trùng id
        bool validInfection(); //kiểm tra trùng Id F0 là “NO”, các id của F khác k đc trùng nhau
        Node* add(Node* root, Patient val);
        Node* search(Node* root, Patient val);//tìm kiếm
        bool leftOf(Patient val, Node* root );
        bool rightOf(Patient val, Node* root );
        Patient leftMostValue( const Node* root );
        void Free( Node* root );
        Node* erase(Node* root, Patient val);//xóa 
        void inOrder(Node* root);//duyệt giữa
        void edit(); //sửa bệnh nhân
        void sort(); //dùng hàm sort có sẵn kết hợp thêm 1 class Compare để so sánh và sắp xếp
        void statistics(); //thống kê theo nơi điều trị
        void F(); //thống kê các F (nếu có map thì dùng, k thì thoi)
        void maxQ_day(); //các bệnh nhân có số ngày cách ly lâu (>21 ngày)
        void exportPatients(); //xuất file
        void function(void); //hàm thực thi các thao tác
};
//TODO: viết 2 hàm bool
bool BST::existPatient(Node* root, string id){ //duyệt trước
   if(root != NULL)
    {
        if(root->data.getId()==id){
            return true;
        }
        existPatient(root->left, id);
        existPatient(root->right, id);
    }
    return false;
}
bool BST::validInfection(){ //duyệt sau
//hihi
}
Node* BST::add(Node* root, Patient val){
    if(root == NULL)
        return new Node(val);
    if(val.getId()<root->data.getId())
        root->left = add(root->left, val);
    else
        root->right = add(root->right, val);
    return root;
}
bool BST::leftOf(Patient val, Node* root )
{
    return val.getId() < root->data.getId(); 
}
 
bool BST::rightOf(Patient val, Node* root )
{
    return val.getId() > root->data.getId(); 
}
Patient BST::leftMostValue( const Node* root ){
    while (root->left != NULL)
        root = root->left;
    return root->data;
}
void BST::Free( Node* root )
{
    if (root){
        Free(root->left);
        Free(root->right);
        delete root;
    }
}
Node* BST::erase(Node* root, Patient val){
    if(root == NULL) return root;
    if(leftOf(val,root))
        root->left=erase(root->left,val);
    else if(rightOf(val,root))
       root->right=erase(root->right,val);
    else {
        if(root->left ==NULL){
            Node* newRoot=root->right;
            free(root);
            return newRoot;
        }
        if (root->right == NULL)
        {
            Node* newRoot = root->left;
            free(root);
            return newRoot;
        }
        root->data = leftMostValue(root->right);
        root->right = erase(root->right, root->data);
    }
    return root;
}
Node* BST::search(Node* root, Patient val){
    if (root == NULL)
        return NULL;
    if(root->data.getId() == val.getId()){
        return root;
    }else if (leftOf(val, root)){
        return search(root->left, val);
    }else if(rightOf(val, root)){
        return search(root->right, val);
    }
}
void BST::function(void){
    int n;
    cout<<"Enter amount of patients: "; cin>>n;
    for(int i=0; i<n; i++){
        Patient a;
        do{
        cin>>a;
        if(existPatient(root,a.getId())){
            cout<<"Same id, enter again!!"<<endl;
        }
        }while(existPatient(root, a.getId()));
        root = add(root,a);
        size++;
    }
    // Patient a,b,c,d,e,f,g;
    // cin>>a>>b>>c>>d>>e>>f>>g;
    // root = add(root,a); //id = 4
    // root = add(root,b); //id = 2
    // root = add(root,c); //id = 6
    // root = add(root,d); //id = 1
    // root = add(root,e); //id = 3
    // root = add(root,f); //id = 5
    // root = add(root,g); //id = 7
    // erase(root,a); //xóa cái 4
    // size--;
    Free(root);
}