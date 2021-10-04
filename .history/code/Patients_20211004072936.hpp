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
    public: 
        BST(){ //constructor
            root = NULL;
        }
        bool existPatient(); //kiểm tra trùng id
        bool validInfection(); //kiểm tra trùng Id F0 là “NO”, các id của F khác k đc trùng nhau
        Node* add(Node* root, Patient val);
        Node* search(Node* root, Patient val);//tìm kiếm
        bool leftOf(Patient val, Node* root );
        bool rightOf(Patient val, Node* root );
        Patient leftMostValue( const Node* root );
        void Free( Node* root );
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
bool BST::existPatient(){
   Patient val;
   if(root->data.getId() == val.getId()) return false;
   return true;  
}
bool BST::validInfection(){
//hihi
}
<<<<<<< HEAD
Node* BST::add(Node* root, Patient val) {
    if(root == NULL) return new Node(val);
=======
Node* BST::add(Node* root, Patient val){
    if(root == NULL)
        return new Node(val);
>>>>>>> d9957489dd8924f2cdb4190c966c442ef9305221
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
    while ( root->left != NULL )
        root = root->left;
    return root->data;
}
void BST::Free( Node* root )
{
    if ( root == NULL )
        return;
    Free( root->left );
    Free( root->right );
    free( root );
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
            Free(root);
            return newRoot;
        }
        if ( root->right == NULL )
        {
            Node* newRoot = root->left;
            Free(root);
            return newRoot;
        }
        root->data = leftMostValue(root->right);
        root->right = erase( root->right, root->data );
    }
    return root;
}
void BST::function(void){
    Patient a,b,c;
    cin>>a>>b>>c;
    root = add(root,a); //id = 2
    root = add(root,b); //id = 1
    root = add(root,c); //id = 3
    erase(root,a); //xóa cái 2
}