
// Duplicate import gard.
#ifndef __STK_H_
#define __STK_H_

// importing the linked list class.
#include "LinkedList.h"

template <class T>

// Stack class implementation using the linked list class as composition.
class Stack {
    private:
        LinkedList<T> linkedList;
        Node<T>* top;

        // Node pointer to traverse through the stack elements.
        Node<T>* iter;

        // Reseting the iter pointer to the top of the stack
        void reset() {
            iter = top;
        }

    public:
        // Constructor for the stack class.
        Stack() : top(nullptr), iter(nullptr) {}

        // Copy constructor for deep copy.
        Stack(const Stack& stk) 
        : linkedList(stk.linkedList), 
          top(linkedList.begin()), 
          iter(linkedList.begin()) {}


        void push(T item) {
            linkedList.insertFirst(item);
            top = linkedList.begin();
            reset();
        }


        T pop() {
            Node<T>* temp = top;
            T data;
            if (temp != nullptr)
                data = temp->getData();

            linkedList.deleteFirst();
            top = linkedList.begin();
            reset();
            return data;
        }


        void clear() {
            while (!isEmpty())
                pop();
        }


        T peek() {
            if (isEmpty())
                throw StackIsEmpityException();
            return top->getData();
        }


        bool isEmpty() {
            return linkedList.isEmpty();
        }

        int getSize() {
            return linkedList.getSize();
        }

        // next method to get the next element of the stack
        Node<T>* next() {
            Node<T>* currentNode = iter;
            if (iter->next != nullptr) {
                iter = iter->next;
                return currentNode;
            }
            
            reset();
            return currentNode;
        }
};


#endif