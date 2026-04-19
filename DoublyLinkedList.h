#pragma once
#include <iostream>
#include <memory>
#include "Node.h"
#include <string>

template <typename T>

class DoublyLinkedList {
private:
    std::shared_ptr<DoublyNode<T>> head;
    std::shared_ptr<DoublyNode<T>> tail;
    int listSize;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), listSize(0) {}; 
    ~DoublyLinkedList() = default;


    void addFront(T data) {
        auto newNode = std::make_shared<DoublyNode<T>>(data);
        if (head == nullptr) { // якщо список порожній
            head = newNode; // то нова нода буде одночасно і першим, заодно і останнім елементом
            tail = newNode;
        } else {
            newNode->next = head; // робимо так щоб вказівник нового першого на наступний елемент був вказівником на колишній перший елемент
            head->previous = newNode; // робимо так щоб вказівник колишнього першого на попередній елемент був вказівником на нову ноду
            head = newNode; // тепер він вказватиме на новий перший
        }
        listSize++;
    }

};