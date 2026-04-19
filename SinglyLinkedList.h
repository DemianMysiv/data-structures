#pragma once
#include <iostream>
#include <memory>
#include "Node.h"
#include <string>

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
    
    
    void addBack(T data){
        auto newNode = std::make_unique<SinglyNode<T>>(data);
        if (head==nullptr) { // то список не має навіть першої нodи
            head = std::move(newNode); //тоді нова нoda буде одночасно і першим, заодно і останнім елементом
        } else {
            SinglyNode<T>* current = head.get(); //get дозволяє отримати вказівник на нodу, яка управляється unique_ptr адже його не можна копіювати
            while (current->next!=nullptr) {  // в цьому цийклі ми доберемося до останнього елемента списку в якого вказівник next буде nullptr
                current = current->next.get();
            }
            current->next = std::move(newNode); // тепер вказівник на наступний елемент після останнього елемента буде вказівником на нову ноду, яка стане новим останнім елементом
        }
        listSize++;
    }


    void deleteFront() {
            if (head == nullptr) {
            throw std::string("List is empty, there is nothing to delete");
        } else { // якщо список не порожній
            head = std::move(head->next); // тепер другий елемент списку буде першим, а колишній перший елемент буде видалений бо на нього ніхто не буде вказувати
            listSize--;
        }
    }

    void deleteBack() {
        if (head == nullptr) {
            throw std::string("List is empty, there is nothing to delete");

        } else {
            if (head->next == nullptr) { // якщо в списку лише один елемент
                head = nullptr; // то після видалення список буде порожнім
            } else {
                SinglyNode<T>* current = head.get();
                while (current->next->next != nullptr) { // в цьому циклі ми доберемося до передостаннього елемента списку, у якого вказівник на наступний елемент буде вказівником на останній елемент, а вказівник на наступний елемент останнього елемента буде nullptr
                    current = current->next.get();
                }
                current->next = nullptr; // тепер вказівник на наступний елемент після передостаннього елемента буде nullptr, а колишній останній елемент буде видалений бо на нього ніхто не буде вказувати
            
        }
            listSize--;
        }
    }

    void accessbyindex(int index) {
        if (index < 0 || index >= listSize) {
            throw std::string("Неправильний індекс");

        } else {
            SinglyNode<T>* current = head.get();
            for (int i = 0; i < index; i++) {
                current = current->next.get();
            }

            std::cout << "Element at index " << index << ": " << current->data << std::endl;
        }
    }


void addbyindex(int index, T data) {
    if (index < 0 || index > listSize) { 
        throw std::string("Неправильний індекс");
    } else if (index == 0) {
        addFront(data);
    } else if (index == listSize) {
        addBack(data);
    } else {
        auto newNode = std::make_unique<SinglyNode<T>>(data); // створюємо нову ноду з даними, які ми хочемо додати
        SinglyNode<T>* current = head.get(); // отримуємо вказівник на перший елемент списку
        for (int i = 0; i < index - 1; i++) {
            current = current->next.get();
        } // в цьому циклі ми доберемося до елемента, який знаходиться перед позицією, на яку ми хочемо додати нову ноду
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
        listSize++;
    }
}

void deletebyindex(int index) {
    if (index < 0 || index >= listSize) {
        throw std::string("Неправильний індекс");
    } else if (index == 0) {
        deleteFront();
    } else if (index == listSize - 1) {
        deleteBack();
    } else {
        SinglyNode<T>* current = head.get();
        for (int i = 0; i < index - 1; i++) {
            current = current->next.get();
        }
        current->next = std::move(current->next->next);
        listSize--;
    }

}

void size() {
    std::cout << "Size of the list: " << listSize << std::endl;
}


void isEmpty() {
    if (listSize == 0) {
        std::cout << "The list is empty." << std::endl;
    } else {
        std::cout << "The list is not empty." << std::endl;
    }
}

void find(T data) {
    SinglyNode<T>* current = head.get();
    int index = 0;
    while (current != nullptr) {
        if (current->data == data) {
            std::cout << "Element " << data << " found at index: " << index << std::endl;
            return;
        }
        current = current->next.get();
        index++;
    }
    std::cout << "Element " << data << " not found in the list." << std::endl;
}
};
