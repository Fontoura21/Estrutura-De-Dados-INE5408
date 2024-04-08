// Copyright [2023] <Rafael Correa Bitencourt>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    size_ = 0;
    max_size_ = max;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        contents[size_] = data;
        size_++;
    }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        for (int i = size_; i > 0; i--) {
            contents[i] = contents[i-1];
        }
        contents[0] = data;
        size_++;
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full() || !(0 <= static_cast<int>(index) && index <= size_)) {
        throw std::out_of_range("Lista cheia");
    } else {
        for (int i = size_; i > static_cast<int>(index); i--) {
            contents[i] = contents[i-1];
        }
        contents[index] = data;
        size_++;
    }
}
template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista cheia");
    } else {
        int i = 0;
        while (i < static_cast<int>(size_) && contents[i] < data) {
            i++;
        }
        insert(data, i);
    }
}
template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty() || !(0 <= static_cast<int>(index) && index < size_)) {
        throw std::out_of_range("Lista vazia");
    } else {
        T aux = contents[index];
        for (int i = index + 1; i < static_cast<int>(size_); i++) {
            contents[i-1] = contents[i];
        }
        size_--;
        return aux;
    }
}
template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        size_--;
        return contents[size_];
    }
}
template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        T aux = contents[0];
        for (int i = 1; i < static_cast<int>(size_); i++) {
            contents[i-1] = contents[i];
        }
        size_--;
        return aux;
    }
}
template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        int i = 0;
        while (i < static_cast<int>(size_) && contents[i] != data) {
            i++;
        }
        if (i < static_cast<int>(size_)) {
            pop(i);
        }
    }
}
template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size_ == max_size_);
}
template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size_ == 0);
}
template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if (contents[i] == data) {
            return true;
        }
    }
    return false;
}
template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    int i = 0;
    while (i < static_cast<int>(size_) && contents[i] != data) {
        i++;
    }
    return i;
}
template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}
template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}
template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (static_cast<int>(index) >= 0 && index < size_) {
        return contents[index];
    } else {
        throw std::out_of_range("Elemento fora da lista");
    }
}
template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}
template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (static_cast<int>(index) >= 0 && index < size_) {
        return contents[index];
    } else {
        throw std::out_of_range("Elemento fora da lista");
    }
}
template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
