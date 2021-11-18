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
    int pos = 0;
    string name = ' ' + fullName;
    string merge;
    for (int i = name.length()-1; i >= 0; i--){
        ++pos;
        if (name[i] == ' '){
            merge += name.substr(i+1, pos-1);
            pos = 0;
        }
    }
    return merge;
}
DNode* partition(DNode* left, DNode* right){//hàm ngoài
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
void quicksort(DNode* left, DNode* right){//hàm ngoài
    if(right != NULL && left != right && left != right->next){
        DNode* p = partition(left, right);
        quicksort(left, p->prev);
        quicksort(p->next, right);
    }
}
void DList::SortByName(){
    quicksort(head, tail);
}
DNode* split(DNode* head){//hàm ngoài (tách list thành 2 nửa)
    DNode *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    DNode *temp = slow->next;
    slow->next = NULL;
    return temp;
}
DNode* merge(DNode* first, DNode* second){//hàm ngoài (trộn 2 list)
    //Nếu list thứ nhất empty
    if (!first)
        return second;
    //Nếu list thứ 2 empty
    if (!second)
        return first;
    //Lấy giá trị nhỏ nhất
    if (first->data.getPlace() < second->data.getPlace()){
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else{
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}
DNode* mergeSort(DNode *head){//hàm ngoài (thực hiện merge sort)
    if (!head || !head->next)
        return head;
    DNode *second = split(head);
    //đệ quy cho 2 nửa
    head = mergeSort(head);
    second = mergeSort(second);
    //trộn lại
    return merge(head,second);
}
void DList::SortByPlace(){
    head = mergeSort(head);
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