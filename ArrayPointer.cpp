#include <iostream>
using namespace std;

class Element{
private:
    int v;
    Element* next;
    Element* prev;
public:
    Element(); //tworzy pusty element
    Element(int x, Element* next, Element* prev);
    int getValue();
    void setValue(int v);
    Element* getNext();
    Element* getPrev();
    void setNext(Element* p);
    void setPrev(Element* p);
};

Element::Element(){
    next=nullptr;
    prev=nullptr;
}

Element::Element(int x, Element* next, Element* prev){
    this->v=x;
    this->next=next;
    this->prev=prev;
}

int Element::getValue(){
    return v;
}

void Element::setValue(int v){
    this->v=v;
}

Element* Element::getNext(){
    return next;
}

Element* Element::getPrev(){
    return prev;
}

void Element::setNext(Element* p){
    next=p;
}

void Element::setPrev(Element* p){
    prev=p;
}
class LinkedList{
private:
    Element *tail;
    Element *head;
    int size;
public:
    LinkedList();
    bool empty();
    int getSize();
    Element* getFirst();
    Element* getLast();
    Element* getNext(Element* p);
    Element* getPrev(Element *p);
    int retrive(Element* p);
    Element* locate(int x);//
    void append(int x);
    void prepend(int x);
    void insert(Element* p, int x);
    void del(Element* p);
    void clear();
    void sort(int x);
    friend ostream& operator<<(ostream& out, LinkedList* a);
    ~LinkedList();
};

LinkedList::LinkedList(){
    head=nullptr;
    tail=nullptr;
    size=0;
}

bool LinkedList::empty(){
    if(size==0){
        return true;
    }
    else{
        return false;
    }
}

void LinkedList::sort(int x){
    Element* h=head;
    if(x>getLast()->getValue())
    {
        prepend(x);
    }
    else{
    while(x >h->getNext()->getValue())
    {
        h=h->getNext();
    }
    insert(h,x);
    }
}
int LinkedList::getSize(){
    return size;
}

Element* LinkedList::getFirst(){
    return head;
}

Element* LinkedList::getLast(){
    return tail;
}

Element* LinkedList::getNext(Element* p){
    return p->getNext();
}

Element* LinkedList::getPrev(Element* p){
    return p->getPrev();
}

int LinkedList::retrive(Element *p){
    return p->getValue();
}

void LinkedList::append(int x){
    Element* e = new Element(x,nullptr,nullptr);//next,prev
    if(empty()){
        tail=e;
        head=e;
    }else{
        e->setNext(head);
        head=e;
    }
    size++;
}

void LinkedList::prepend(int x){
    Element* e = new Element(x,nullptr,nullptr);//next,prev
    if(empty()){
        tail=e;
        head=e;
    }else{
        tail->setNext(e);
        e->setPrev(tail);
        tail=e;
    }
    size++;
}

Element* LinkedList::locate(int x){
    Element* h=head;

    while(h!=nullptr){
        if(retrive(h)==x){
            return h;
        }
        else{
            h=h->getNext();
        }
    }

    return nullptr;
}
void LinkedList::insert(Element* p, int x){
    if(p==getFirst())
    {
        append(x);
    }
    else if(p==getLast())
    {
        prepend(x);
    }
    else{
        Element* e = new Element(x,p->getNext(),p);//next,prev
        p->getNext()->setPrev(e);
        p->setNext(e);
        size++;
    }
}

void LinkedList::del(Element* p){
    if(size==1){
        head=nullptr;
        tail=nullptr;
        delete p;
    }
    else if(p==getFirst()){
        head=p->getNext();
        head->setPrev(nullptr);
        delete p;
    }
    else if(p==getLast()){
        tail=p->getPrev();
        tail->setNext(nullptr);
        delete p;
    }
    else{
        p->getPrev()->setNext(p->getNext());
        p->getNext()->setPrev(p->getPrev());
        delete p;
    }

    size--;
}

void LinkedList::clear()
{
    while(size!=0){
        del(head);
    }

}
ostream& operator<<(ostream& out, LinkedList* a){
    Element* head = a->getFirst();

    if(a->empty()){
        out<<"Pusto"<<endl;
    }
    else{
    while(head!=nullptr){
        out<<head->getValue()<<" ";
        head=head->getNext();
    }
    }
}
int main(){
    //example
    LinkedList* a = new LinkedList();
    a->append(3);
    a->append(2);
    a->append(1);
    a->prepend(4);
    a->prepend(5);
    cout<<a;
    cout<<endl<<endl;
    cout<<" 4: "<<a->locate(5)<<endl;
    cout<<a->retrive(a->getFirst());

    cout<<endl<<endl;
    a->insert(a->locate(1),69);
    cout<<a;

    cout<<endl<<endl;
    a->del(a->locate(69));
    cout<<a;

    cout<<endl<<endl;
    a->sort(10);
    cout<<a;

    cout<<endl<<endl;
    a->clear();
    cout<<a;

}
