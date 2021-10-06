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
        void push(Patient val);
        void Delete();
        void SortByName();
        void print();
};
DNode* DList::getHead(){
    return head;
}
DNode* DList::getTail(){
    return tail;
}
void DList::push(Patient val){
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
void DList::Delete(){
    DNode* k = NULL;
    while(head != NULL){
        k = head;
        head = head->next;
        delete k;
    } 
    size = 0;
}
void DList::SortByName(){
    Patient temp;
    for(DNode* p = head; p->next != NULL; p = p->next){
        for(DNode* q = tail; q != p; q = q->prev){
            if(p->data.getName()>q->data.getName()){
                temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
        }
    }
}
void DList::print(){
    DNode* d = head;
    while(d != NULL){
        cout<<d->data;
        d = d->next;
    }
}