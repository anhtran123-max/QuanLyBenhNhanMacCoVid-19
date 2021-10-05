#include "Patient.hpp"
#include "Doubly.hpp"
#include<bits/stdc++.h>

class Node{
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
        bool existPatient(string id); //kiểm tra trùng id
        bool validInfection(string infection); //kiểm tra trùng Id F0 là “NO”, các id của F khác k đc trùng nhau
        Node* add(Node* root, Patient val);
        Node* search(Node* root, Patient val);//tìm kiếm
        bool leftOf(Patient val, Node* root );
        bool rightOf(Patient val, Node* root );
        Patient leftMostValue( const Node* root );
        void Free( Node* root );
        Node* erase(Node* root, Patient val);//xóa 
        DList preOrder(Node* root);//duyệt trước
        DList inOrder(Node* root);//duyệt giữa
        DList postOrder(Node* root);//duyệt sau
        void edit(); //sửa bệnh nhân
        void sortByName(Node* root); //dùng hàm sort có sẵn kết hợp thêm 1 class Compare để so sánh và sắp xếp
        void statistics(); //thống kê theo nơi điều trị
        void F(); //thống kê các F (nếu có map thì dùng, k thì thoi)
        void maxQ_day(); //các bệnh nhân có số ngày cách ly lâu (>21 ngày)
        void exportPatients(); //xuất file
        void function(void); //hàm thực thi các thao tác
};
DList change;
DList BST::preOrder(Node* root){
    if(root != NULL){
        change.push(root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
    return change;
}
DList BST::inOrder(Node* root){
    if(root != NULL){
        inOrder(root->left);
        change.push(root->data);
        inOrder(root->right);
    }
    return change;
}
DList BST::postOrder(Node* root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        change.push(root->data);
    }
    return change;
}
bool BST::existPatient(string id){ //duyệt trước
    change.Delete();
    DList d = preOrder(root);
    DNode* p = d.getHead();
    while(p != NULL){
        if(p->data.getId() == id) return true;
        p = p->next;
    }
    return false;
}
bool BST::validInfection(string infection){ //duyệt sau
    if(infection == "NO") return true;
    change.Delete();
    DList d = postOrder(root);
    DNode* p = d.getHead();
    while(p != NULL){
        if(p->data.getId() == infection) return true;
        p = p->next;
    }
    return false;
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
bool BST::leftOf(Patient val, Node* root ){
    return val.getId() < root->data.getId(); 
}
bool BST::rightOf(Patient val, Node* root ){
    return val.getId() > root->data.getId(); 
}
Patient BST::leftMostValue( const Node* root ){
    while(root->left != NULL)
        root = root->left;
    return root->data;
}
void BST::Free( Node* root ){
    if(root){
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
        if(root->right == NULL){
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
    }
    else if (leftOf(val, root)){
        return search(root->left, val);
    }
    else if(rightOf(val, root)){
        return search(root->right, val);
    }
}

void BST::sortByName(Node* root){
    change.Delete();
    DList a = inOrder(root);
    Patient temp;
    for(DNode* p = a.getHead(); p->next != NULL; p = p->next){
        for(DNode* q = a.getTail(); q != p; q = q->prev){
            if(p->data.getName()>q->data.getName()){
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
}
bool checkSubString(string str1, string str2){
    if(str2.size() > str1.size()) return false;
    for(int i = 0; i < str1.size(); i++){
        int j = 0;
        if(str1[i] == str2[j]){
            int tmp = i;
            while (str1[i] == str2[j] && j < str2.size()){
                j++;
                i++;
            }
            if (j == str2.size()) return true;
            else i = tmp;
        }   
    }
    return false;
}

void BST::function(void){
    int n;
    cout<<"Enter amount of patients: "; cin>>n;
    for(int i=0; i<n; i++){
        cout<<"-->Enter infomation of Patent "<<i+1<<endl;
        Patient a;
        do{
        cin>>a;
        if(existPatient(a.getId())){
            cout<<"Same id, enter again!!"<<endl;
        }
        if(!validInfection(a.getInfect())){
            cout<<"Invalid infection!!"<<endl;
        }
        }while((existPatient(a.getId())) || (!validInfection(a.getInfect())));
        root = add(root,a);
        size++;
    }
    sortByName(root);
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
//hihi