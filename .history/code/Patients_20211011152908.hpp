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
        void edit(Node* root); //sửa bệnh nhân
        void sortByName(Node* root); //dùng hàm sort có sẵn kết hợp thêm 1 class Compare để so sánh và sắp xếp
        void statistics(); //thống kê theo nơi điều trị
        void F(Node* root); //thống kê các F (nếu có map thì dùng, k thì thoi)
        void F0Status(Node* root);// thống kê F0
        void maxQ_day(); //các bệnh nhân có số ngày cách ly lâu (>21 ngày)
        void exportPatients(); //xuất file
        void function(void); //hàm thực thi các thao tác
};
DList change;
DList BST::preOrder(Node* root){
    if(root != NULL){
        change.Add(root->data);
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
bool compare(string str1, string str2){ //hàm ngoài
    int n=str1.length();
    int m=str2.length();
    if(n==m)
        return (str1<str2);
    
    return n<m;
}
Node* BST::add(Node* root, Patient val){
    if(root == NULL)
        return new Node(val);
    if(compare(val.getId(),root->data.getId()))
        root->left = add(root->left, val);
    else
        root->right = add(root->right, val);
    return root;
}
bool BST::leftOf(Patient val, Node* root ){
    return compare(val.getId(),root->data.getId()); 
}
bool BST::rightOf(Patient val, Node* root ){
    return compare(root->data.getId(),val.getId()); 
}
Patient BST::leftMostValue( const Node* root ){
    while(root->left != NULL)
        root = root->left;
    return root->data;
}
void BST::Free( Node* root ){
    if(root== NULL) return;

    Free(root->left);
    Free(root->right);
    delete root;
    size = 0;
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
    a.SortByName();
    a.print();
}

void BST::edit(Node* root){
    Patient find;
    string id_fix;
    cout<<"Enter id of patient need to edit: ";
    cin>>id_fix;
    find.setId(id_fix);
    if(search(root, find)==NULL){
        cout<<"No such patient has been found !!"<<endl;
        return;
    }else{
        erase(root,find);
        size--;
        do{
            cin>>find;
            if(existPatient(find.getId())){
                cout<<"Same id, enter again!!"<<endl;
            }
            if(!validInfection(find.getInfect())){
                cout<<"Invalid infection!!"<<endl;
            }
        }while((existPatient(find.getId())) || (!validInfection(find.getInfect())));
        root = add(root,find);
    }
    cout<<"Edit success!"<<endl;
}
// t them 2 sort 1 cai ben doubly vs 1 cai cho nay nha k bt m dung cai nao thi dung kk
void sort(int a[], int b[]){
    for(int i=0; i<size-1; i++){
        for(int j=i+1;j<size;j++){
            if(a[i] > b[j]){
                int tmp = a[i];
                a[i] = b[j];
                b[j] = tmp;
            }
        }
    }
}
void BST::F(Node* root){
    change.Delete();
    DList d = preOrder(root);
    int arr[size];
    int i = 0;
    DNode* p = d.getHead();
    while(p != NULL && i<size){
        if(p->data.getInfect() == "NO"){
        arr[i] = 0;
        }else{
            int j = 0;
            DNode* q = d.getHead();
            while(q != p && j<i){
                if(p->data.getInfect() == q->data.getId()){
                    arr[i] = arr[j] + 1;
                    break;
                }
                j++;
                q = q->next;
            }
        }
        i++;
        p = p->next;
    }
    i = 0;
    p = d.getHead();
    while(p!=NULL && i<size){
        cout<<"Id: "<<p->data.getId()<<" is F"<<arr[i]<<endl;
        i++;
        p = p->next;
    }
}
void BST::F0Status(Node* root){
    change.Delete();
    DList d = preOrder(root);
    DNode* p = d.getHead();
    while(p != NULL ){
        if(p->data.getStatus() == 0) cout<<"Id: "<<p->data.getId()<<"is FO"<<endl;
        p=p->next;
    }
        
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
    //edit(root);
    F(root);
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