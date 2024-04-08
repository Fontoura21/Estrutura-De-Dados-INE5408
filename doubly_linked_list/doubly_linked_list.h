// Copyright [2023] Rafael Correa Bitencourt

namespace structures {

#include <cstdint>
#include <stdexcept>  // C++ Exceptions

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* position(std::size_t index) {
        if (index < 0 || index >= size_) {
            return nullptr;
        }

        Node *p;
        if (index < size()/2) {
            p = head;
            for (std::size_t i = 0; i < index; ++i) {
                p = p->next();
            }
        } else {
            p = tail;
            for (std::size_t i = size() - 1; i > index; --i) {
                p = p->prev();
            }
        }

        return p;
    }

    Node* head;  // primeiro da lista
    Node* tail;  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    auto p = head;

    while (p != nullptr) {
        auto cur_node = p;
        p = p->next();
        delete cur_node;
    }

    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    insert(data, 0);
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("Índice fora de faixa");
    }

    auto new_node = new Node(data);

    auto predec = position(index - 1);
    auto suc = predec != nullptr ? predec->next() : head;

    new_node->prev(predec);
    new_node->next(suc);

    if (predec != nullptr) {
        predec->next(new_node);
    } else {
        head = new_node;
    }

    if (suc != nullptr) {
        suc->prev(new_node);
    } else {
        tail = new_node;
    }

    ++size_;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    auto i = 0;
    for (auto it = head; it != nullptr && data > it->data(); it = it->next()) {
        ++i;
    }

    insert(data, i);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Índice fora de faixa");
    }

    auto cur = position(index);
    auto predec = cur->prev();
    auto suc = cur->next();

    if (predec != nullptr) {
        predec->next(suc);
    } else {
        head = suc;
    }

    if (suc != nullptr) {
        suc->prev(predec);
    } else {
        tail = predec;
    }

    auto retval = cur->data();

    delete cur;
    --size_;

    return retval;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    return pop(0);
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    auto pos = find(data);

    if (pos != size_) {
        pop(pos);
    }
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    return find(data) != size_;
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (index < 0 || index >= size_) {
        throw std::out_of_range("Índice fora de faixa");
    }

    return position(index)->data();
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    auto i = 0;
    for (auto it = head; it != nullptr && data != it->data(); it = it->next()) {
        ++i;
    }

    return i;
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}
