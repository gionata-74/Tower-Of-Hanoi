// Linked List implemntation

// Duplicate import gard.
#ifndef _SLL_H
#define _SLL_H



#include <iostream>

// Including user defined excptions.
#include "UserDefinedExceptions.h"

// Template for Generic Linked List.
template <typename T>

// Node class implementation
struct Node {
    private:
        T data;
    public:
        Node<T>* next;
        Node(const T& item) 
            : data(item), next(nullptr) {}
        Node(const T&& item) 
            : Node(item) {}

        T getData() { return data; }


    void printNode() { std::cout<<data; }
};


template <class T>
// Linked List class implementation
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        // NumberOfNodes to track the size of the linked list.
        int NumberOfNodes;

    public:
        // Default constructor
        LinkedList()
            : NumberOfNodes(0), head(nullptr), tail(nullptr) {}

        // Copy constractor for deep copying a linked list.
        LinkedList(const LinkedList& ls)
            : LinkedList() {
                Node<T>* temp = ls.head;

                while (temp != nullptr) {
                    Node<T>* newNode = new Node<T>(temp->getData());

                    if (isEmpty()) {
                        head = newNode;
                        tail = newNode;
                        temp = temp->next;
                        NumberOfNodes++;
                        continue;
                    }
                    tail->next = newNode;
                    tail = newNode;
                    temp = temp->next;
                    NumberOfNodes++;
                }
        }
        
        // parameter: by reference to increse the performance of the insertion operation
        void insertFirst(const T& item) {
            // Instanciating Node object and setting the data value to item
            Node<T>* newNode = new Node<T>(item);

            if (isEmpty()) {
                head = newNode;
                tail = newNode;
                NumberOfNodes++;
                return;
            }

            newNode->next = head;
            head = newNode;
            NumberOfNodes++;
        }
    
        void deleteFirst() {
            
            if (isEmpty()) {
                // Initiating an exception when linked list is empity
                throw StackUnderFlowException();
            }

            NumberOfNodes--;

            if (head->next == nullptr) {
                delete head;
                head = nullptr;
                tail = nullptr;
                return;
            }

            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }


        bool isEmpty(){
            return !NumberOfNodes;
        }

        int getSize() {
            return NumberOfNodes;
        }

        // Begin method to get a pointer to the head of the linked list
        Node<T>* begin() {
            return head;
        }

        // End method to get a pointer to the tail of the linked list
        Node<T>* end() {
            return tail;
        }

        // Destructor to release the memory resource used by the linked list
        ~LinkedList() {
            Node<T>* temp = head;
            while (temp != nullptr) {
                temp = head->next;
                delete head;
                head = temp;
            }
        }
};

#endif