#include "Patient.hpp"
#include "Doubly.hpp"
#include<bits/stdc++.h>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
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
        void Add(Node* root);//thêm bệnh nhân 
        void remove(Node* root);//xóa bệnh nhân 
        void find(Node* root);//tìm kiếm bệnh nhân 
        void sortByName(Node* root); //sắp xếp theo tên
        int countPlace(Node *root, string q_place);
        void statistics(Node *root); //thống kê theo nơi điều trị
        void F(Node* root); //thống kê các F
        void F0Status(Node* root); // thống kê F0
        void maxQ_day(Node *root); //các bệnh nhân có số ngày cách ly lâu (>21 ngày)
        void checkHealth(Node *root); //thống kê sức khỏe bệnh nhân
        void exportPatients(ofstream &file, Node *root); //xuất file
        void display(Node *root); //xuất ra màn hình 
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
    DList a = preOrder(root);
    DNode *p = a.getHead();
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
void BST::Add(Node* root){
    Patient val;
    do{
        cout<<"Enter information of patient need to add: " << endl;
        cin>>val;
        if(existPatient(val.getId())){
                cout<<"Same id, enter again!!"<<endl;
            }
        if(!validInfection(val.getInfect())){
            cout<<"Invalid infection!!"<<endl;
        }
    }while(existPatient(val.getId()) ||(!validInfection(val.getInfect())));
    add(root,val);
    size++;
    cout<<"Add success!"<<endl;
}
void BST::remove(Node* root){
    Patient find;
    string id_remove;
    cout<<"Enter id of patient need to remove: ";
    cin>>id_remove;
    find.setId(id_remove);
    if(search(root, find)==NULL){
        cout<<"No such patient has been found !!"<<endl;
        return;
    }else{
        erase(root,find);
        size--;
        cout <<"Remove success!" << endl;
    }
}
void BST::find(Node* root){
    Patient find;
    string id_find;
    bool flag = true;
    while(flag){
        cout<<"Enter id of patient need to find: ";
        cin>>id_find;
        find.setId(id_find);
        Node* p = search(root, find);
        if(p == NULL){
            cout<<"No such patient has been found !!"<<endl;
        } else {
            cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout<< "|STT"<< "|\t" << "ID" << "\t|\t" << "Full Name" << "\t|\t" << "Birth" << "\t\t|\t" << "Addrress" << "\t|\t" << "Status" << "\t|\t" <<
            "Infect" << "\t|\t" << "Inject" << "\t|\t" << "Q_Place" << "\t|\t" << "Q_Day\t|" << endl;
            cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout <<"| "<< 1 << " |\t";
            cout <<p->data<< endl;
            flag = false;
        }
    }
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
    int i = 0, stt = 1;
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
    cout << setw(125) << "<-------- THE LIST OF F-PATIENTS BY ID -------->" << endl;
    cout << setw(117) << "---------------------------------" << endl;
    cout<<setw(88)<<"|STT"<< "|" << "IDs" << "|\t" << "Full Name" << "\t| " << "F |" << endl;
    cout << setw(117) << "---------------------------------" << endl;
    while(p!=NULL && i<size){
        cout<<setw(86)<<"| "<< stt << " | "<<p->data.getId()<<" |\t"<<p->data.getName()<<
        "\t| "<<arr[i]<<" |"<<endl;
        cout << setw(117) << "---------------------------------" << endl;
        i++;
        stt++;
        p = p->next;
    }
}
void BST::F0Status(Node* root){
    change.Delete();
    DList d = inOrder(root);
    DNode* p = d.getTail();
    int stt = 1;
    cout << setw(125) << "<------ STATUS OF F0 PATIENT ------>"<<endl;
    cout << setw(129) << "----------------------------------------------" << endl;
    cout << setw(87)  <<"|STT"<< "|" << "IDs" << "|\t" << "Full Name" << "\t|\t" << "Status\t|" << endl;
    cout << setw(129) << "----------------------------------------------" << endl;
    while(p != NULL){
        if(p->data.getInfect() == "NO"){
            cout<<setw(85)<<"| "<< stt << " | "<<p->data.getId()<<" |\t"<<p->data.getName()<<
            "\t|\t";
            switch(p->data.getStatus()){
                case 0:
                cout<<"Healthy\t|"<<endl;
                break;
                case 1:
                cout<<"Lightly\t|"<<endl;
                break;
                default:
                cout<<"Heavily\t|"<<endl;
                break;
            }
            stt++;
            cout << setw(129) << "----------------------------------------------" << endl;
        }
        p = p->prev;
    }
}
void BST::checkHealth(Node *root){
    change.Delete();
    DList d = inOrder(root);
    DNode *p = d.getTail();
    int stt = 1;
    cout << setw(125) << "<------ PATIENT HEALTHY LIST NOW ------>"<<endl;
    cout << setw(129) << "----------------------------------------------" << endl;
    cout << setw(87)  <<"|STT"<< "|" << "IDs" << "|\t" << "Full Name" << "\t|\t" << "Health\t|" << endl;
    cout << setw(129) << "----------------------------------------------" << endl;
    while(p != NULL){
        if((p->data.getInJect() == 1 || (p->data.getInJect() == 2) && p->data.getQ_day() < 21 )
        && (p->data.getStatus() ==0 ||p->data.getStatus() ==1))
        {
            cout<<setw(85)<<"| "<< stt << " | "<<p->data.getId()<<" |\t"<<p->data.getName()<<"\t|\t"<<"Well\t|"<<endl;
            cout << setw(129) << "----------------------------------------------" << endl;
        }
        else{
            cout<<setw(85)<<"| "<< stt << " | "<<p->data.getId()<<" |\t"<<p->data.getName()<<"\t|\t"<<"Bad \t|"<<endl;
            cout <<setw(129) << "----------------------------------------------" << endl;
        }
        p = p->prev;
        stt++;
    }
}
void BST::statistics(Node* root){
    change.Delete();    
    int count = 0, stt = 1;
    DList d = inOrder(root);
    d.SortByPlace();
    DNode *p = d.getHead();
    cout<<"Place: "<<p->data.getPlace()<<endl;
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout<< "|STT"<< "|\t" << "ID" << "\t|\t" << "Full Name" << "\t|\t" << "Birth" << "\t\t|\t" << "Addrress" << "\t|\t" << "Status" << "\t|\t" <<
    "Infect" << "\t|\t" << "Inject" << "\t|\t" << "Q_Place" << "\t|\t" << "Q_Day\t|" << endl;
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while(p != NULL){
        cout <<"| "<< stt << " |\t";
        cout<<p->data;
        count++;
        stt++;
        if(p->next == NULL){
            cout<<"Place "<<p->data.getPlace()<<" has "<<count<<" patients"<<endl;
            break;
        }
        if(p->next->data.getPlace() != p->data.getPlace()){
            cout<<"Place "<<p->data.getPlace()<<" has "<<count<<" patients"<<endl;
            count = 0;
            stt = 1;
            if(p->next != NULL){
                cout<<"Place: "<<p->next->data.getPlace()<<endl;
                cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                cout<< "|STT"<< "|\t" << "ID" << "\t|\t" << "Full Name" << "\t|\t" << "Birth" << "\t\t|\t" << "Addrress" << "\t|\t" << "Status" << "\t|\t" <<
                "Infect" << "\t|\t" << "Inject" << "\t|\t" << "Q_Place" << "\t|\t" << "Q_Day\t|" << endl;
                cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
            }
        }
        p = p->next;
    }
}
void BST::maxQ_day(Node *root){
    change.Delete();
    int count = 0, stt = 1;
    DList d = preOrder(root);
    DNode *p = d.getHead();
    p = d.getHead();
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout<< "|STT"<< "|\t" << "ID" << "\t|\t" << "Full Name" << "\t|\t" << "Birth" << "\t\t|\t" << "Addrress" << "\t|\t" << "Status" << "\t|\t" <<
    "Infect" << "\t|\t" << "Inject" << "\t|\t" << "Q_Place" << "\t|\t" << "Q_Day\t|" << endl;
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while(p != NULL){
        if(p->data.getQ_day() > 21){
            cout <<"| "<< stt << " |\t";
            cout<<p->data;
            count++;
            stt++;
        }
        p = p->next;
    }
    cout << "-->The number of people have quarantine day > 21: " << count <<endl;
}
void BST::display(Node * root){
    change.Delete();
    int stt = 1;
    DList d = inOrder(root);
    DNode *p = d.getTail();
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout<< "|STT"<< "|\t" << "ID" << "\t|\t" << "Full Name" << "\t|\t" << "Birth" << "\t\t|\t" << "Addrress" << "\t|\t" << "Status" << "\t|\t" <<
    "Infect" << "\t|\t" << "Inject" << "\t|\t" << "Q_Place" << "\t|\t" << "Q_Day\t|" << endl;
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while(p != NULL){
        cout <<"| "<< stt << " |\t";
        cout<<p->data;
        stt++;
        p = p->prev;
    }
}
void BST::exportPatients(ofstream &file, Node *root){
    change.Delete();
    DList d = inOrder(root);
    DNode *p = d.getTail();
    int count = 1;
    file<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    file<< "|STT"<< "|\t" << "ID" << "\t|\t" << "Full Name" << "\t|\t" << "Birth" << "\t\t|\t" << "Addrress" << "\t|\t" << "Status" << "\t|\t" <<
    "Infect" << "\t|\t" << "Inject" << "\t|\t" << "Q_Place" << "\t|\t" << "Q_Day\t|" << endl;
    file<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while(p != NULL){
        file<<"| "<< count << " |\t";
        file<<p->data<<endl;
        count++;
        p = p->prev;
    }
    file.close();
}
void BST::function(void){
    int n, choice_admin;
    system("color b0");
    ifstream file_in("D:/BTL/code/input.in");
    ofstream file("D:/BTL/code/data.txt");
    file_in>>n;
    for(int i=0; i<n; i++){
        Patient a;
        file_in>>a;
        root = add(root,a);
        size++;
    }
    do {
        system("cls");
        cout << setw(135) <<"####################### MANAGEMENT PATIENTS ######################" << endl;
        cout << setw(135) <<"#================================================================#" << endl;
        cout << setw(135) <<"######    Class: CNTT K61  BM CNTT - DH GTVT PH.TPHCM       ######" << endl;
        cout << setw(135) <<"#================================================================#" << endl;
        cout << setw(135) <<"#================================================================#" << endl;
        cout << setw(135) <<"# 1-Find Patient                               7-Check healthy   #" << endl;
        cout << setw(135) <<"# 2-Statistics F by id                         8-Print file      #" << endl;                           
        cout << setw(135) <<"# 3-Status statistic F0                        9-Print Patient   #" << endl; 
        cout << setw(135) <<"# 4-Sort by name                               10-Remove Patient #" << endl;
        cout << setw(135) <<"# 5-Patients have Q-Day > 21                   11-Add Patinet    #" << endl;
        cout << setw(135) <<"# 6-Patients at Q-Place                        12-Edit Patinet   #" << endl;
        cout << setw(135) <<"######                    0-Exit program                    ######" << endl;    
        cout << setw(135) <<"#================================================================#" << endl;
        cout << setw(135) <<"##################################################################" << endl;
        cout << setw(90)  <<"What is your choice: ";
        fflush(stdin);
        cin >> choice_admin;
        cout << endl;
        switch(choice_admin){
            case 1:
            {
                find(root);
                system("pause");
                break;
            }
            case 2:
            {
                F(root);
                system("pause");
                break;
            }
            case 3:
            {
                F0Status(root);
                system("pause");
                break;
            }
            case 4:
            {
                sortByName(root);
                system("pause");
                break;
            }
            case 5:
            {
                maxQ_day(root);
                system("pause");
                break;
            }
            case 6:
            {
                statistics(root);
                system("pause");
                break;
            }
            case 7:
            {
                checkHealth(root);
                system("pause");
                break;
            }
            case 8:
            {
                exportPatients(file,root);
                system("pause");
                break;
            }
            case 9:
            {
                display(root);
                system("pause");
                break;
            }
            case 10:
            {
                remove(root);
                display(root);
                system("pause");
                break;
            }
            case 11:
            {
                Add(root);
                display(root);
                system("pause");
                break;
            }
            case 12:
            {
                edit(root);
                display(root);
                system("pause");
                break;
            }
            default:
            {
                cout <<"Choice is non-valid." << endl;
                break;
            }
            case 0:
            {
                cout <<endl<<setw(105)<<"GOOD BYE";
                Sleep(1000);
                break;
            }
        }
    } while(choice_admin != 0);
    Free(root);
}