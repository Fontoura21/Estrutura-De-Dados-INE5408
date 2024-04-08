// Copyright [2023] <Rafael Correa Bitencourt>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST
#define STRUCTURES_DOUBLY_CIRCULAR_LIST

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Circular Doubly Linked List
class DoublyCircularList {
 public:
    //! Constructor
    DoublyCircularList() = default;

    //! Destructor
    ~DoublyCircularList() {
        clear();
    }

    //! Clears the list
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    //! Inserts at given position
    void insert(const T& data, std::size_t index) {
        if (index < 0 || index > size()) {
            throw std::out_of_range("Index out of range!");
        }

        if (empty() || index == 0) {
            return push_front(data);
        }

        if (index == size()) {
            return push_back(data);
        }

        auto previous_node = head;
        for (auto i = 0u; i < index-1; ++i) {
            previous_node = previous_node->next();
        }

        auto new_node = new Node{data, previous_node, previous_node->next()};
        previous_node->next()->prev(new_node);
        previous_node->next(new_node);
        ++size_;
    }

    //! Push front
    void push_front(const T& data) {
        auto new_node = new Node{data};
        new_node->next(head);
        new_node->prev(tail);
        if (empty()) {
            tail = new_node;
        } else {
            head->prev(new_node);
        }

        head = new_node;
        ++size_;
    }

    //! Push back
    void push_back(const T& data) {
        auto new_node = new Node{data, tail, nullptr};
        new_node->prev(tail);
        if (empty()) {
            head = new_node;
        } else {
            tail->next(new_node);
        }

        tail = new_node;
        ++size_;
    }

    //! Insert sorted
    void insert_sorted(const T& data) {
        if (empty()) {
            return push_front(data);
        }

        auto current_node = head;
        std::size_t index = 0;
        while (index < size() && data > current_node->data()) {
            current_node = current_node->next();
            ++index;
        }
        insert(data, index);
    }

    //! Pops at a given position
    T pop(std::size_t index) {
        if (empty() || index < 0 || index >= size()) {
            throw std::out_of_range("Out of range!");
        }

        auto previous_node = head;
        for (auto i = 0u; i < index-1; ++i) {
            previous_node = previous_node->next();
        }

        auto delete_node = previous_node->next();
        auto next_node = delete_node->next();

        auto delete_data = delete_node->data();

        previous_node->next(next_node);
        next_node->prev(previous_node);

        --size_;
        delete delete_node;
        return delete_data;
    }

    //! Pop at size()
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto old_tail = tail;
        auto old_data = tail->data();
        tail = tail->prev();

        --size_;
        delete old_tail;
        return old_data;
    }

    //! Pop at 0
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto old_data = head->data();
        auto next_node = head->next();
        delete head;
        head = next_node;
        if (size() > 1) {
            head->prev(tail);
            tail->next(head);
        }

        --size_;
        return old_data;
    }

    //! Removes element from the list
    void remove(const T& data) {
        auto index = find(data);
        pop(index);
    }

    //! Empty
    bool empty() const {
        return size_ == 0;
    }

    //! Contains a specific element
    bool contains(const T& data) const {
        auto current_node = head;

        for (auto i = 0u; i < size()-1; ++i) {
            if (current_node->data() == data) {
                return true;
            }
            current_node = current_node->next();
        }
        return false;
    }

    //! Acess the element at the given index
    T& at(std::size_t index) {
        if (index < 0 || index > size()) {
            throw std::out_of_range("Wrong index!");
        }

        auto current_node = head;
        for (auto i = 0u; i < index; i++) {
            current_node = current_node->next();
        }

        return current_node->data();
    }

    //! At
    const T& at(std::size_t index) const {
        if (index < 0 || index > size()) {
            throw std::out_of_range("Wrong index!");
        }

        auto current_node = head;
        for (auto i = 0u; i < index; i++) {
            current_node = current_node->next();
        }

        return current_node->data();
    }

    //! Returns specific element index
    std::size_t find(const T& data) const {
        auto current_node = head;

        for (auto i = 0u; i < size(); ++i) {
            if (current_node->data() == data) {
                return i;
            }
            current_node = current_node->next();
        }
        return 10;
    }

    //! Returns std::size_t size_
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
        //! Constructor
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        //! Return data w/o const
        T& data() {
            return data_;
        }

        //! Return data const
        const T& data() const {
            return data_;
        }

        //! Return prev
        Node* prev() {
            return prev_;
        }

        //! Return prev const
        const Node* prev() const {
            return prev_;
        }

        //! Prev setter
        void prev(Node* node) {
            prev_ = node;
        }

        //! Return next
        Node* next() {
            return next_;
        }

        //! Return next const
        const Node* next() const {
            return next_;
        }

        //! Next setter
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    Node* tail;
    std::size_t size_;
};

}  // namespace structures

#endif
