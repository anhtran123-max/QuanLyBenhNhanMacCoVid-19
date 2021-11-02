#include "Patient.hpp"
#include <bits/stdc++.h>
using namespace std;
class DNode {
    public:
        Patient data;
        DNode* prev;
        DNode* next;
        DNode(Patient data){
            this->data = data;
            prev = NULL;
            next = NULL;
        }
};
class DList{
    private:
        DNode* head;
        DNode* tail;
        int size;
    public:
        DList(){
            head = tail = NULL;
            size = 0;
        }
        ~DList(){}
        DNode* getHead();
        DNode* getTail();
        int getSize();
        void setSize(int size);
        DNode* CreateNode(Patient val);
        void push(Patient val);
        void Add(Patient val);
        void Delete();
        void SortByName();
        void SortByPlace();
        void sortList();
        void print();
};
DNode* DList::getHead(){
    return head;
}
DNode* DList::getTail(){
    return tail;
}
int DList::getSize(){
    return size;
}
void DList::setSize(int size){
    this->size = size;
}
void DList::push(Patient val){//thêm đầu
    DNode* p = new DNode(val);
    if(size == 0){
        head = tail = p;
    }
    else{
        head->prev = p;
        p->next = head;
        head = p;
    }
    size++;
}
void DList::Add(Patient val){//thêm cuối
    DNode* p = new DNode(val);
    if(size == 0) {
        head = tail = p;
    }else{
        tail->next = p;
        p->prev = tail;
        tail = p;
    }
    size++;
}
void swap(DNode* a, DNode* b){//hàm ngoài
    Patient temp;
    temp = a->data;
    a->data = b->data;
    b->data = temp;
}
void DList::Delete(){
    DNode* k = NULL;
    while(head != NULL){
        k = head;
        head = head->next;
        delete k;
    } 
    setSize(0);
}
string in_name(string fullName){//hàm ngoài
    string name;
    int i;
    for(i = fullName.length()-1; i>=0; i--){
        if(fullName[i] == ' ') break;
    }
    for(int j = i+1; j<fullName.length(); j++){
        name += fullName[j];
    }
    return name;
}
DNode* partitionByName(DNode* left, DNode* right){//hàm ngoài
    Patient x = right->data;//pivot ở đuôi
    DNode* i = left->prev;
    DNode* j = left;
    while(j != right){
        if(in_name(j->data.getName()) <= in_name(x.getName())){
            i = (i == NULL)? left : i->next;//i++
            swap(i, j);
        }
        j = j->next;
    }
    i = (i == NULL)? left : i->next;//i++
    swap(i, right);//pivot ở giữa (phía trước < pivot và sau > pivot)
    return i;//trả về pivot
}
void quicksortByName(DNode* left, DNode* right){//hàm ngoài
    if(right != NULL && left != right && left != right->next){
        DNode* p = partitionByName(left, right);
        quicksortByName(left, p->prev);
        quicksortByName(p->next, right);
    }
}
void DList::SortByName(){
    quicksortByName(head, tail);
}
DNode* partitionByPlace(DNode* left, DNode* right){//hàm ngoài
    Patient x = right->data;//pivot ở đuôi
    DNode* i = left->prev;
    DNode* j = left;
    while(j != right){
        if(j->data.getPlace() <= x.getPlace()){
            i = (i == NULL)? left : i->next;//i++
            swap(i, j);
        }
        j = j->next;
    }
    i = (i == NULL)? left : i->next;//i++
    swap(i, right);//pivot ở giữa (phía trước < pivot và sau > pivot)
    return i;//trả về pivot
}
void quicksortByPlace(DNode* left, DNode* right){//hàm ngoài
    if(right != NULL && left != right && left != right->next){
        DNode* p = partitionByPlace(left, right);
        quicksortByPlace(left, p->prev);
        quicksortByPlace(p->next, right);
    }
}
void DList::SortByPlace(){
    quicksortByPlace(head, tail);
}
void DList::print(){
    DNode* d = head;
    int stt = 1;
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout<< "|STT"<< "|\t" << "ID" << "\t|\t" << "Full Name" << "\t|\t" << "Birth" << "\t\t|\t" << "Addrress" << "\t|\t" << "Status" << "\t|\t" <<
    "Infect" << "\t|\t" << "Inject" << "\t|\t" << "Q_Place" << "\t|\t" << "Q_Day\t|" << endl;
    cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while(d != NULL){
        cout <<"| "<< stt << " |\t";
        cout<<d->data;
        stt++;
        d = d->next;
    }
}