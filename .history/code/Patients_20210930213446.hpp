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
        Patient leftOf( const Patient val, const Node* root );
        Patient rightOf( const Patient val, const Node* root );
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
<<<<<<< HEAD
void LinkedList::add(Patient val){
    Node *node = new Node(val);
    if(head == NULL){
        head = node;
    }
    else{
        Node *cur = head;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = node;
    }
}
=======
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
>>>>>>> ba76e69e465e4b37ba98181261b6444bf90d66bb
Patient BST::leftOf( const Patient val, const Node* root )
{
    return val < root->data; 
}
 
Patient BST::rightOf( const Patient val, const Node* root )
{
    return val > root->data;
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
            free(root);
            return newRoot;
        }
        if ( root->right == NULL )
        {
            Node* newRoot = root->left;
            free(root);
            return newRoot;
        }
        root->data = LeftMostValue( root->right );
        root->right = Delete( root->right, root->data );
    }
    return root;
}
