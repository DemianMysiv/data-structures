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
            head->prev = newNode; // робимо так щоб вказівник колишнього першого на попередній елемент був вказівником на нову ноду
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
            newNode->prev = tail; // робимо так щоб вказівник нового останнього на попередній елемент був вказівником на колишній останній елемент
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
                head->prev.reset(); // робимо так щоб вказівник нового першого на попередній елемент був nullptr, а колишній перший елемент буде видалений бо на нього ніхто не буде вказувати
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
            tail = tail->prev.lock(); // тепер передостанній елемент списку буде останнім, а колишній останній елемент будет видалений бо на нього ніхто не буде вказувати
            if (tail != nullptr) { // якщо після видалення список не став порожнім
                tail->next.reset(); // робимо так щоб вказівник нового останнього на наступний елемент був nullptr, а колишній останній елемент будет видалений бо на нього ніхто не буде вказувати
            } else { // якщо після видалення список став порожнім
                head = nullptr; // то перший елемент також будет nullptr
            }
        }
            listSize--;
    }
    
void accessbyindex(int index) {
    if (index < 0 || index >= listSize) {
        throw std::string("Неправильний індекс");
    }

    DoublyNode<T>* current;

    int distFromHead = index;
    int distFromTail = (listSize - 1) - index;

    if (distFromHead <= distFromTail) {
        current = head;
        for (int i = 0; i < distFromHead; i++) {
            current = current->next;
        }
    } else {
        current = tail;
        for (int i = 0; i < distFromTail; i++) {
            current = current->prev;
        }
    }

    std::cout << "Element at index " << index << ": " << current->data << std::endl;
}

void addbyindex(int index, T data) {
    if (index < 0 || index > listSize) {
        throw std::string("Неправильний індекс");
    }

    if (index == 0) {
        addFront(data);
        return;
    } 
    
    if (index == listSize) {
        addBack(data);
        return;
    }

    auto newNode = std::make_shared<DoublyNode<T>>(data);
    DoublyNode<T>* current;

    int targetIndex = index - 1;// йдмемо до елемента що перед позицію на яку ми хочемо щось поставити
    int distFromHead = targetIndex;
    int distFromTail = (listSize - 1) - targetIndex;

    if (distFromHead <= distFromTail) {
        current = head.get();
        for (int i = 0; i < distFromHead; i++) {
            current = current->next.get();
        }
    } else {
        current = tail;
        for (int i = 0; i < distFromTail; i++) {
            current = current->prev;
        }
    }


// До тепер ми пов'язали вказівники prev на 2 та next на 3 нової ноди 99 з сусіами.Ми поставили ноду 99 між ними
//але треба ще 99 зробити наступною для два і попердньою для 3
    newNode->prev = current;
    newNode->next = current->next;

    (newNode->next)->prev = newNode.get();
    current->next = newNode;

    listSize++;
}
};
