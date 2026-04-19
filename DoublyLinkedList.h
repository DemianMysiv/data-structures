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

    std::shared_ptr<DoublyNode<T>> current; // Використовуємо shared_ptr замість сирого вказівника

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
            current = current->prev.lock(); // .lock() конвертує weak_ptr у shared_ptr
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

void deletebyindex(int index) {
    // Для видалення індекс має бути строго меншим за listSize, бо елемента з індексом listSize не існує
    if (index < 0 || index >= listSize) {
        throw std::string("Неправильний індекс");
    }

    if (index == 0) {
        deleteFront();
        return;
    } 
    
    // Якщо це останній елемент
    if (index == listSize - 1) {
        deleteBack();
        return;
    }

    DoublyNode<T>* current;

    int targetIndex = index - 1; // йдемо до елемента, що стоїть ПЕРЕД тим, який ми хочемо видалити
    int distFromHead = targetIndex;
    int distFromTail = (listSize - 1) - targetIndex;

    if (distFromHead <= distFromTail) {
        current = head.get();
        for (int i = 0; i < distFromHead; i++) {
            current = current->next.get();
        }
    } else {
        current = tail; // Зберігаємо твій стиль (якщо tail це shared_ptr, можливо знадобиться tail.get())
        for (int i = 0; i < distFromTail; i++) {
            current = current->prev; // Якщо prev це weak_ptr (як у deleteBack), можливо знадобиться current->prev.lock().get()
        }
    }

    // До тепер current вказує на елемент ПЕРЕД тим, який ми хочемо видалити (позиція index - 1)
    // Зберігаємо shared_ptr на ноду, яку видаляємо, щоб вона не знищилась до того, як ми перекинемо зв'язки
    auto nodeToDelete = current->next;

    // Перекидаємо вказівник next поточної ноди на ноду ПІСЛЯ тієї, яку видаляємо
    current->next = nodeToDelete->next;

    // Перекидаємо вказівник prev наступної ноди на поточну.
    // Найпростіше взяти його з nodeToDelete->prev, адже він вже вказує куди треба (на current)
    (current->next)->prev = nodeToDelete->prev; 

    listSize--;
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
    DoublyNode<T>* current = head.get();
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

void printList() {
    DoublyNode<T>* current = head.get();
    std::cout << "List elements: ";
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next.get();
    }
    std::cout << std::endl;
}
};
