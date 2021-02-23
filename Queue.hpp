// Specification of Queue class
// Written By: Camila Picanco Mesquita, Dixon Dai, Nithyasree Sampath and Natalia Mendonca
#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
#include <string>
#include "Room.hpp"

using namespace std;

template <typename T>

struct ListNode {
    
    T data;
    ListNode *next;
};

template <typename T>
class Queue {
private:
    ListNode <T> *head;
    ListNode <T> *tail;
public:
    Queue() {
        head = tail = NULL;
    }
    void insert(T link) {
        ListNode<T> *newNode = new ListNode<T>;
        newNode->data = link;
        newNode->next = NULL;
        if(head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    bool isEmpty()
    {
        if(head == NULL) {
            return true;
        }
        return false;
    }
    T remove()
    {
        ListNode <T> *temp = head;
        
        if(head == NULL)
            return NULL;
        
        if(head == tail) {
            
            head = tail = NULL;
        }
        else {
            head = head->next;
        }
        
        return temp->data;
    }
    void printNodes()
    {
        ListNode<T> *temp = head;
        while(temp->next != NULL) {
            
            cout << "Link Data " << temp->data <<endl;
            temp = temp->next;
        }
    }
    
};

#endif
