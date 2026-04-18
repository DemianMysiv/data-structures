#pragma once
#include <memory>

template<typename T>


struct SinglyNode {
    T data;
    std::unique_ptr<SinglyNode<T>> next;
    SinglyNode(T value) : data(value), next(nullptr) {}
};

template<typename T>

struct DoublyNode {
    T data;
    std::shared_ptr<DoublyNode<T>> next;
    std::weak_ptr<DoublyNode<T>> previous;
    DoublyNode(T value) : data(value), next(nullptr) {}
};
