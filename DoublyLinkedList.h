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

void addBack(T data) {
        auto newNode = std::make_shared<DoublyNode<T>>(data);
        if (head == nullptr) { // якщо список порожній
            head = newNode; // то нова нода буде одночасно і першим, заодно і останнім елементом
            tail = newNode;
        } else {
            newNode->previous = tail; // робимо так щоб вказівник нового останнього на попередній елемент був вказівником на колишній останній елемент
            tail->next = newNode; // робимо так щоб вказівник колишнього останнього на наступний елемент був вказівником на нову ноду
            tail = newNode; // тепер він вказватиме на новий останній
        }
        listSize++;

}

void deleteFront() {
        if (head == nullptr) {
            throw std::string("List is empty, there is nothing to delete");
        } else { // якщо список не порожній
            head = head->next; // тепер другий елемент списку буде першим, а колишній перший елемент буде видалений бо на нього ніхто не буде вказувати
            if (head != nullptr) { // якщо після видалення список не став порожнім
                head->previous.reset(); // робимо так щоб вказівник нового першого на попередній елемент був nullptr, а колишній перший елемент буде видалений бо на нього ніхто не буде вказувати
            } else { // якщо після видалення список став порожнім
                tail = nullptr; // то останній елемент також буде nullptr
            }
            listSize--;
        }
    }

void deleteBack() {
        if (head == nullptr) {
            throw std::string("List is empty, there is nothing to delete");
        } else {
            tail = tail->previous.lock(); // тепер передостанній елемент списку буде останнім, а колишній останній елемент будет видалений бо на нього ніхто не буде вказувати
            if (tail != nullptr) { // якщо після видалення список не став порожнім
                tail->next.reset(); // робимо так щоб вказівник нового останнього на наступний елемент був nullptr, а колишній останній елемент будет видалений бо на нього ніхто не буде вказувати
            } else { // якщо після видалення список став порожнім
                head = nullptr; // то перший елемент також будет nullptr
            }
        }
            listSize--;
    }   
};

