#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "research_project.h"

template<typename T>
class Node {
public:
    T data;
    Node<T>* next;
    
    Node(T value) : data(value), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    void add(T value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (!head) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }

    bool remove(const std::string& id) {
        if (!head) return false;

        // Special case: head node
        if (static_cast<ResearchProject*>(head->data)->getId() == id) {
            Node<T>* temp = head;
            head = head->next;
            delete temp->data; // Delete the actual object
            delete temp;
            size--;
            return true;
        }

        // Search for node to remove
        Node<T>* current = head;
        while (current->next) {
            if (static_cast<ResearchProject*>(current->next->data)->getId() == id) {
                Node<T>* temp = current->next;
                current->next = temp->next;
                delete temp->data; // Delete the actual object
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    T find(const std::string& id) const {
        Node<T>* current = head;
        while (current) {
            if (static_cast<ResearchProject*>(current->data)->getId() == id) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    void displayAll() const {
        if (!head) {
            std::cout << "No projects found.\n";
            return;
        }

        Node<T>* current = head;
        int count = 1;
        while (current) {
            std::cout << "Project " << count++ << ":\n";
            static_cast<ResearchProject*>(current->data)->display();
            current = current->next;
        }
    }

    int getSize() const {
        return size;
    }

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp->data; // Delete the actual object
            delete temp;
        }
        size = 0;
    }

    // Iterator support for advanced operations
    class Iterator {
    private:
        Node<T>* current;
    public:
        Iterator(Node<T>* node) : current(node) {}
        
        T operator*() { return current->data; }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) { return current != other.current; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

#endif