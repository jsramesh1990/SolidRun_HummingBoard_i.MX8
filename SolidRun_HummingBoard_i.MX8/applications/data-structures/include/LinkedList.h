#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDebug>

template<typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList() { clear(); }
    
    // Basic operations
    void pushFront(const T& value);
    void pushBack(const T& value);
    void insertAt(int index, const T& value);
    void insertBefore(const T& value, const T& before);
    void insertAfter(const T& value, const T& after);
    
    T popFront();
    T popBack();
    T removeAt(int index);
    bool removeValue(const T& value);
    
    // Utility operations
    void reverse();
    int find(const T& value) const;
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    void clear();
    
    // Access
    T getAt(int index) const;
    T getFirst() const { return head ? head->data : T(); }
    T getLast() const { return tail ? tail->data : T(); }
    
    // Display
    QString toString() const;
    QList<T> toList() const;
    
private:
    Node* head;
    Node* tail;
    int size;
    
    Node* getNodeAt(int index) const;
};

// Template implementations
#include "LinkedList.tpp"

#endif // LINKEDLIST_H
