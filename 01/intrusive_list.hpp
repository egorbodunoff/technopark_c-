#ifndef INTRUSIVE_LIST_HPP
#define INTRUSIVE_LIST_HPP

#include <cstddef>
#include <iostream>
#include <iterator>

template <typename T>
struct IntrusiveListHook {
    T* prev = nullptr;
    T* next = nullptr;
};

template <typename T, IntrusiveListHook<T> T::*Hook>
class IntrusiveList {
   public:
    struct Iterator {
        T* node;
        Iterator() : node(nullptr) {}
        Iterator(T* node) : node(node) {}
        T& operator*() const { return *node; }
        T* operator->() const { return node; }
        Iterator& operator++() {
            node = (node->*Hook).next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const Iterator& other) const { return node == other.node; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }
    };

    struct ConstIterator {
        const T* node;
        ConstIterator(const T* node) : node(node) {}
        const T& operator*() const { return *node; }
        const T* operator->() const { return node; }
        ConstIterator& operator++() {
            node = (node->*Hook).next;
            return *this;
        }
        ConstIterator operator++(int) {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const ConstIterator& other) const { return node == other.node; }
        bool operator!=(const ConstIterator& other) const { return !(*this == other); }
    };

    IntrusiveList() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~IntrusiveList() { clear(); }

    void push_back(T& element) {
        auto& hook = element.*Hook;
        hook.prev = tail_;
        hook.next = nullptr;
        if (tail_) {
            (tail_->*Hook).next = &element;
        } else {
            head_ = &element;
        }
        tail_ = &element;
        ++size_;
    }

    void push_front(T& element) {
        auto& hook = element.*Hook;
        hook.prev = nullptr;
        hook.next = head_;
        if (head_) {
            (head_->*Hook).prev = &element;
        } else {
            tail_ = &element;
        }
        head_ = &element;
        ++size_;
    }

    void pop_back() {
        if (tail_) {
            erase(*tail_);
        }
    }

    void pop_front() {
        if (head_) {
            erase(*head_);
        }
    }

    T& back() { return *tail_; }

    const T& back() const { return *tail_; }

    void erase(T& element) {
        auto& hook = element.*Hook;
        if (hook.prev) {
            (hook.prev->*Hook).next = hook.next;
        } else {
            head_ = hook.next;
        }
        if (hook.next) {
            (hook.next->*Hook).prev = hook.prev;
        } else {
            tail_ = hook.prev;
        }
        hook.prev = hook.next = nullptr;
        --size_;
    }

    void insert(Iterator pos, T& element) {
        auto& hook = element.*Hook;

        if (pos.node) {
            hook.next = pos.node;
            hook.prev = (pos.node->*Hook).prev;
            if (hook.prev) {
                (hook.prev->*Hook).next = &element;
            } else {
                head_ = &element;
            }
            (pos.node->*Hook).prev = &element;
            ++size_;
        } else {
            push_back(element);
        }
    }

    void splice(Iterator pos, IntrusiveList& other) {
        if (other.empty()) return;

        auto* first = other.head_;
        auto* last = other.tail_;

        if (pos.node) {
            (first->*Hook).prev = (pos.node->*Hook).prev;
            (pos.node->*Hook).prev = last;
            (last->*Hook).next = pos.node;
            if ((first->*Hook).prev) {
                ((first->*Hook).prev->*Hook).next = first;
            } else {
                head_ = first;
            }
        } else {
            (first->*Hook).prev = tail_;
            if (tail_) {
                (tail_->*Hook).next = first;
            } else {
                head_ = first;
            }
            tail_ = last;
        }

        size_ += other.size_;

        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    void clear() {
        while (head_) {
            erase(*head_);
        }
    }

    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

   private:
    T* head_;
    T* tail_;
    size_t size_;
};

#endif
