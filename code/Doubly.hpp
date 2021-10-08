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
// DNode* DList::CreateNode(Patient val){
//     DNode *pDNode=new DNode;
//     if(pDNode != NULL){
//         pDNode->data=d;
//         pDNode->next=NULL;
//         pDNode->prev=NULL;
//     }
//     else cout<<" cap phat bo nho that bai";
//     return pDNode;
// }
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
// void DList::sortList(){
//     for(DNode *p = head;p!=NULL;p->next){
//         for(DNode *p2 = p->next;p2!=NULL;p2->next){
//             if(p->data > p2->data){
//                 DNode *tmp;
//                 tmp = p->data;
//                 p->data=p2->data;
//                 p2->data=tmp;
//             }
//         }
//     }
// }
void DList::print(){
    DNode* d = head;
    while(d != NULL){
        cout<<d->data;
        d = d->next;
    }
}