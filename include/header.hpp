// Copyright 2019 Plotnikov Aleksey <alex280201@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <utility>
#include <exception>
#include <type_traits>

template <typename T>
class Stack {
 private:
  T* data;
  size_t size;

 public:
  Stack() {
    data = nullptr;
    size = 0;
  }

  Stack(const Stack&) = delete;

  Stack(Stack&& st) {
    size = st.size;
    data = st.data;
    st.size = 0;
    st.data = nullptr;
  }

  Stack& operator=(const Stack&) = delete;

  Stack& operator=(Stack&& st) {
    if (&st == this) return *this;
    delete[] data;
    size = st.size;
    data = st.data;
    st.size = 0;
    st.data = nullptr;
    return *this;
  }

  ~Stack() {
    if (data != nullptr) {
      delete[] data;
      size = 0;
    }
  }

  void push(T&& value) {
    size++;
    T* temp = new T[size];
    for (size_t i = 0; i < size - 1; i++) temp[i] = data[i];
    if (std::is_move_assignable<T>())
      temp[size - 1] = std::move(value);
    else
      temp[size - 1] = value;
    delete[] data;
    data = temp;
  }

  void push(const T& value) {
    size++;
    T* temp = new T[size];
    for (size_t i = 0; i < size - 1; i++) temp[i] = data[i];
    temp[size - 1] = value;
    delete[] data;
    data = temp;
  }

  void pop() {
    size--;
    T* temp = new T[size];
    for (size_t i = 0; i < size; i++) temp[i] = data[i];
    delete[] data;
    data = temp;
  }

  T pop(int) {
    size--;
    T res = data[size];
    T* temp = new T[size];
    for (size_t i = 0; i < size; i++) temp[i] = data[i];
    delete[] data;
    data = temp;
    return res;
  }

  const T& head() const {
    if (size == 0) throw std::logic_error("Stack is empty");
    return data[size - 1];
  }

  template <typename... Args>
  void push_emplace(Args&&... value) {
    size++;
    T* temp = new T[size];
    for (size_t i = 0; i < size - 1; i++) temp[i] = data[i];
    if (std::is_move_assignable<T>())
      temp[size - 1] = std::move(T(value...));
    else
      temp[size - 1] = T(value...);
    delete[] data;
    data = temp;
  }
};

#endif // INCLUDE_HEADER_HPP_
