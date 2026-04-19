#include <iostream>
#include <string>
#include <windows.h>
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

int main() {

    SetConsoleOutputCP(CP_UTF8);
    
    // ========================================================================
    // ДЕМОНСТРАЦІЯ 1: ОДНОЗВ'ЯЗНИЙ СПИСОК (SinglyLinkedList)
    // Тип даних: int
    // ========================================================================
    std::cout << "========== Singly Linked List (int) ==========\n";
    SinglyLinkedList<int> sList;

    sList.isEmpty();

    std::cout << "\n--- Додавання елементів ---\n";
    std::cout << "Додаємо 10 на початок, 20 на кінець, 5 на початок:\n";
    sList.addFront(10);
    sList.addBack(20);
    sList.addFront(5);
    sList.printList();

    sList.size();

    std::cout << "Додаємо 15 за індексом 2:\n";
    sList.addbyindex(2, 15);
    sList.printList();

    std::cout << "\n--- Пошук та доступ ---\n";
    std::cout << "Доступ за індексом 2: ";
    sList.accessbyindex(2);

    std::cout << "Пошук 15: ";
    sList.find(15);
    
    std::cout << "Пошук 99: ";
    sList.find(99);

    std::cout << "\n--- Видалення елементів ---\n";
    std::cout << "Вилучаємо елемент за індексом 2:\n";
    sList.deletebyindex(2);
    sList.printList();

    std::cout << "Вилучаємо перший елемент:\n";
    sList.deleteFront();
    sList.printList();

    std::cout << "Вилучаємо останній елемент:\n";
    sList.deleteBack();
    sList.printList();

    std::cout << "\n\n";

    // ========================================================================
    // ДЕМОНСТРАЦІЯ 2: ДВОЗВ'ЯЗНИЙ СПИСОК (DoublyLinkedList)
    // Тип даних: std::string
    // ========================================================================
    std::cout << "========== Doubly Linked List (std::string) ==========\n";
    DoublyLinkedList<std::string> dList;

    dList.isEmpty();

    std::cout << "\n--- Додавання елементів ---\n";
    std::cout << "Додаємо 'Banana' на початок, 'Cherry' на кінець, 'Apple' на початок:\n";
    dList.addFront("Banana");
    dList.addBack("Cherry");
    dList.addFront("Apple");
    dList.printList();

    dList.size();

    std::cout << "Додаємо 'Blueberry' за індексом 2:\n";
    dList.addbyindex(2, "Blueberry");
    dList.printList();

    std::cout << "\n--- Пошук та доступ ---\n";
    std::cout << "Доступ за індексом 2: ";
    dList.accessbyindex(2);

    std::cout << "Пошук 'Cherry': ";
    dList.find("Cherry");

    std::cout << "\n--- Видалення елементів ---\n";
    std::cout << "Вилучаємо елемент за індексом 1:\n";
    dList.deletebyindex(1);
    dList.printList();

    std::cout << "Вилучаємо перший елемент:\n";
    dList.deleteFront();
    dList.printList();

    std::cout << "Вилучаємо останній елемент:\n";
    dList.deleteBack();
    dList.printList();

    return 0;
}