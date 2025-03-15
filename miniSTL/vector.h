#pragma once

namespace ministl {

template<typename T>
class vector {
 public:
  vector() : ptr_(nullptr), sz_(0), cap_(0) {}
  vector(const vector& other);
  vector& operator=(const vector& other);

  size_t size() const {
    return sz_;
  }

  size_t capacity() const {
    return cap_;
  }

  void reserve(size_t newcap) {
    if (newcap <= cap_) {
      return;
    }
    T* newptr = reinterpret_cast<T*>(new char[sizeof(T) * newcap]);
    for (size_t index = 0; index < sz_; ++index) {
      new(newptr + index) T(ptr_[index]);
    }
    for (size_t index = 0; index < sz_; ++index) {
      (ptr_ + index)->~T();
    }
    delete[] ptr_;
    ptr_ = newptr;
    cap_ = newcap;
  }


  ~vector() {
    for (size_t index = 0; index < sz_; ++index) {
      (ptr_ + index)->~T();
    }
    delete[] ptr_;
  }

 private:
  T*      ptr_;
  size_t  sz_;
  size_t  cap_;
};

}