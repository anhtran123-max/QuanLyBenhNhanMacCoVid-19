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
        Patient leftMostValue(const Node* root);
        void Free( Node* root );
        Node* erase(Node* root, Patient val);//xóa 
        DList preOrder(Node* root);//duyệt trước
        DList inOrder(Node* root);//duyệt giữa
        DList posOrder(Node* root);//duyệt sau
        void edit(Node* root); //sửa bệnh nhân
        void add(Node* root);//thêm bệnh nhân TODO:
        void remove(Node* root);//xóa bệnh nhân TODO:
        void find(Node* root);//tìm kiếm bệnh nhân TODO:
        void sortByName(Node* root); //sắp xếp theo tên
        int countPlace(Node *root, string q_place);
        void statistics(Node *root); //thống kê theo nơi điều trị
        void F(Node* root); //thống kê các F
        void F0Status(Node* root); // thống kê F0
        void maxQ_day(Node *root); //các bệnh nhân có số ngày cách ly lâu (>21 ngày)
        void checkHealth(Node *root); //thống kê sức khỏe bệnh nhân TODO:
        void exportPatients(ofstream &file, Node *root); //xuất file
        void display(); //xuất ra màn hình TODO:
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
DList BST::posOrder(Node* root){
    if(root != NULL){
        posOrder(root->left);
        posOrder(root->right);
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
    DList d = posOrder(root);
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
            delete root;
            return newRoot;
        }
        if(root->right == NULL){
            Node* newRoot = root->left;
            delete root;
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
void sortId(DList &d, int a[]){//hàm ngoài
    Patient temp;
    int k;
    int i = 0;
    DNode* p = d.getHead();
    while(p->next != NULL && i<d.getSize()-1){
        int j = i+1;
        DNode* q = p->next;
        while(q != NULL && j<d.getSize()){
            if(a[i]>a[j]){
                temp = p->data;
                p->data = q->data;
                q->data = temp;
                k = a[i];
                a[i] = a[j];
                a[j] = k;
            }
            q = q->next;
            j++;
        }
        p = p->next;
        i++;
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
    sortId(d,arr);
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
    DList d = inOrder(root);
    DNode* p = d.getTail();
    cout<<"---Status of F0 patient---"<<endl;
    while(p != NULL){
        if(p->data.getInfect() == "NO"){
            cout<<p->data.getId()<<": ";
            switch(p->data.getStatus()){
                case 0:
                cout<<"Healthy"<<endl;
                break;
                case 1:
                cout<<"Lightly"<<endl;
                break;
                default:
                cout<<"Heavily"<<endl;
                break;
            }
        }
        p = p->prev;
    }
}
// thong ke noi cach ly
int BST::countPlace(Node *root, string q_place){
    change.Delete();
    DList d = posOrder(root);
    DNode *p = d.getHead();
    int count = 0;
    while(p != NULL){
        if(p->data.getPlace().compare(q_place) == 0){
            count++;
        }
        p= p->next;    
    }   
    return count;
}
void BST::checkHealth(Node *root){
    change.Delete();
    DList d = inOrder(root);
    DNode *p = d.getTail();
    while(p != NULL){
        if((p->data.getInJect == 1 || p->data.getInJect == 2) && p->data.getQ_day < 21 && (p->data.getStatus() ==0 ||p->data.getStatus() ==1)) cout<<p->data.getId()<<" is Safe"<<endl;  
        else cout<<p->data.getId()<<" is not safe"<<endl;
        p = p->prev;
    }
}
void BST::statistics(Node* root){
    change.Delete();    
    int count = 0;
    DList d = inOrder(root);
    DNode *p = d.getTail();
    cout<<"Place: "<<p->data.getPlace()<<endl;
    while(p != NULL){
        cout<<p->data;
        count++;
        if(p->prev == NULL){
            cout<<"Place "<<p->data.getPlace()<<" has "<<count<<" patients"<<endl;
            break;
        }
        if(p->prev->data.getPlace() != p->data.getPlace()){
            cout<<"Place "<<p->data.getPlace()<<" has "<<count<<" patients"<<endl;
            count = 0;
            if(p->prev != NULL){
                cout<<"Place: "<<p->prev->data.getPlace()<<endl;
            }
        }
        p = p->prev;
    }
}
void BST::maxQ_day(Node *root){
    change.Delete();
    int count = 0;
    DList d = preOrder(root);
    DNode *p = d.getHead();
    p = d.getHead();
    while(p != NULL){
        if(p->data.getQ_day() > 21){
            cout<<p->data;
            count++;
        }
        p = p->next;
    }
    cout << "-->The number of people have quarantine day > 21: " << count <<endl;
}
void BST::exportPatients(ofstream &file, Node *root){
    change.Delete();
    DList d = inOrder(root);
    DNode *p = d.getTail();
    int count = 1;
    while(p != NULL){
        file<<"STT: "<<count<<" ";
        file<<p->data<<endl;
        count++;
        p = p->prev;
    }
    file.close();
}
void BST::function(void){
    int n;
    ofstream file("data.txt");
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
    //F(root);
    //F0Status(root);
    //sortByName(root);
    //cout << "\nThe number of patients in quarantine place: \n";
    statistics(root);
    maxQ_day(root);
    exportPatients(file,root);
    Free(root);
}
//hihi