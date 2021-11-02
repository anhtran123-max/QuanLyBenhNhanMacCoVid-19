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
void DList::SortByName(){
    Patient temp;
    for(DNode* p = head; p->next != NULL; p = p->next){
        for(DNode* q = tail; q != p; q = q->prev){
            if(in_name(p->data.getName())>in_name(q->data.getName())){
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
}
void DList::SortByPlace(){
    Patient temp;
    for(DNode* p = head; p->next != NULL; p = p->next){
        for(DNode* q = tail; q != p; q = q->prev){
            if(p->data.getPlace()<q->data.getPlace()){
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
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