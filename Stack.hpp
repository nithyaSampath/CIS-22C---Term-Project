// Specification of Stack class
// Written By: Camila Picanco Mesquita, Dixon Dai, Nithyasree Sampath and Natalia Mendonca
#ifndef Stack_hpp
#define Stack_hpp

#include <iostream>
#include <string>
#include "Room.hpp"

using namespace std;

template <typename T>

struct StackNode {
    
    T data;
    StackNode *next;
};

template <typename T>
class Stack {
private:
    StackNode <T> *head;
public:
    Stack() {
        head = NULL;
    }
    
    // Insert entry into  head
    // Last In First out
    
    void insert(T link) {
        StackNode<T> *newNode = new StackNode<T>;
        newNode->data = link;
        
        if(head == NULL) {
            newNode->next = NULL;
            head = newNode;
        }
        else {
            newNode->next = head;           // take the current head and put it in new node->next
            head = newNode;
        }
    }
    
    bool isEmpty()
    {
        if(head == NULL) {
            return true;
        }
        return false;
    }
    
    // remove from head
    T remove()
    {
        StackNode <T> *temp = head;
        
        if(head == NULL) {
            
            return NULL;
        }
        else {
            head = head->next;
        }
        
        return temp->data;
    }
    
    void printNodes()
    {
        StackNode<T> *temp = head;
        while(temp->next != NULL) {
            
            cout << "Link Data " << temp->data <<endl;
            temp = temp->next;
            
        }
    }
    
};


#endif
