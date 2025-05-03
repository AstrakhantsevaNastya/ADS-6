// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>
#include <utility>

template<typename T>
class TPQueue {
 private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& data, Node* next = nullptr)
            : data(data), next(next) {}
    };

    Node* head;

 public:
    TPQueue() noexcept : head(nullptr) {}

    ~TPQueue() {
        clear();
    }

    void push(const T& item) {
        if (head == nullptr || item.prior > head->data.prior) {
            head = new Node(item, head);
            return;
        }

        Node* current = head;
        while (current->next != nullptr &&
               current->next->data.prior >= item.prior) {
            current = current->next;
        }

        current->next = new Node(item, current->next);
    }

    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Cannot pop from empty queue");
        }

        Node* toRemove = head;
        T result = std::move(head->data);
        head = head->next;
        delete toRemove;
        return result;
    }

    bool isEmpty() const noexcept {
        return head == nullptr;
    }

    void clear() noexcept {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    TPQueue(const TPQueue&) = delete;
    TPQueue& operator=(const TPQueue&) = delete;
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
