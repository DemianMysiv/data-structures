#pragma once
#include <iostream>
#include <memory>
#include "Node.h"

template <typename T>
class SinglyLinkedList {
private:
    std::unique_ptr<SinglyNode<T>> head;
    int listSize;

public:
    SinglyLinkedList() : head(nullptr), listSize(0) {};
    ~SinglyLinkedList() = default;

    void addFront(T data){
        auto newNode = std::make_unique<SinglyNode<T>>(data);
        newNode->next = std::move(head); //робимо так щоб вказівник нового першого на наступний елемент був вказівником на колишній перший елемент
        head = std::move(newNode); //Але після муву вказівник на перший елемент у списку обнулився тож тпер він вказватиме на новий перший
        listSize++;
    }
};