// this solution comes from https://gist.github.com/charlierm/5691020
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>


class Node
{
public:
    Node* next;
    int data;
};

using namespace std;

class LinkedList
{
public:
    int length;
    Node* head;

    LinkedList();
    ~LinkedList();
    void add(int data);
    void print();
};

LinkedList::LinkedList(){
    this->length = 0;
    this->head = NULL;
}

LinkedList::~LinkedList(){
    Node* next = head;
    Node* cur = NULL;
    while (next != NULL) {
        cur = next;
        next = next->next;
        delete cur;
    }
}

void LinkedList::add(int data){
    Node* node = new Node();
    node->data = data;
    node->next = this->head;
    this->head = node;
    this->length++;
}

void LinkedList::print(){
    Node* head = this->head;
    int i = 1;
    while(head){
        std::cout << i << ": " << head->data << std::endl;
        head = head->next;
        i++;
    }
}

int main(int argc, char const *argv[])
{
    LinkedList* list = new LinkedList();
    for (int i = 0; i < 5; ++i)
        list->add(i*10);

    list->print();
    std::cout << "List Length: " << list->length << std::endl;
    delete list;

	system("pause");
    return 0;
}