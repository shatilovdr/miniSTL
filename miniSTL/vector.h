#pragma once

namespace ministl {

template<typename T>
class vector {
  static_assert(!std::is_same<bool, T>::value, 
      "vector<bool> is not supported yet");
 public:
  vector() : ptr_(nullptr), sz_(0), cap_(0) {}

  explicit vector(size_t count, const T& value = T())
      : ptr_(nullptr), sz_(count), cap_(count) {

    if (cap_ == 0) {
      return;
    }

    ptr_ = reinterpret_cast<T*>(new char[sizeof(T) * cap_]);

    size_t index = 0;
    try {
      for (; index < sz_; ++index) {
        new(ptr_ + index) T(value);
      }
    } catch (...) {
      for (size_t newindex = 0; newindex < index; ++newindex) {
        (ptr_ + newindex)->~T();
      }
      delete[] reinterpret_cast<char*>(ptr_);
      throw;
    }
  }

  vector(const vector& other)
      : ptr_(nullptr), sz_(other.sz_), cap_(other.cap_) {

    if (cap_ == 0)
      return;

    ptr_ = reinterpret_cast<T*>(new char[sizeof(T) * cap_]);

    size_t index = 0;
    try {
      for (; index < sz_; ++index) {
        new(ptr_ + index) T(other.ptr_[index]);
      }
    } catch (...) {
      for (size_t newindex = 0; newindex < index; ++newindex) {
        (ptr_ + newindex)->~T();
      }
      delete[] reinterpret_cast<char*>(ptr_);
      throw;
    }
  };

  vector& operator=(const vector& other) {
    if (this == &other) {
      return *this;
    }
    
    T* newptr = nullptr;
    if (other.cap_ > 0) {
      newptr = reinterpret_cast<T*>(new char[sizeof(T) * other.cap_]);
    }

    size_t index = 0;
    try {
      for (; index < other.sz_; ++index) {
        new(newptr + index) T(other.ptr_[index]);
      }
    } catch (...) {
      for (size_t newindex = 0; newindex < index; ++newindex) {
        (newptr + newindex)->~T();
      }
      delete[] reinterpret_cast<char*>(newptr);
      throw;
    }

    for (size_t index = 0; index < sz_; ++index) {
      (ptr_ + index)->~T();
    }

    delete[] reinterpret_cast<char*>(ptr_);

    ptr_ = newptr;
    cap_ = other.cap_;
    sz_ = other.sz_;

    return *this;
  }

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

    size_t index = 0;
    try {
      for (; index < sz_; ++index) {
        new(newptr + index) T(ptr_[index]);
      }
    } catch (...) {
      for (size_t newindex = 0; newindex < index; ++newindex) {
        (newptr + newindex)->~T();
      }
      delete[] reinterpret_cast<char*>(newptr);
      throw;
    }

    for (size_t index = 0; index < sz_; ++index) {
      (ptr_ + index)->~T();
    }

    delete[] reinterpret_cast<char*>(ptr_);
    ptr_ = newptr;
    cap_ = newcap;
  }

  void push_back(const T& value) {
    if (sz_ == cap_) {
      size_t newcap = sz_ > 0 ? sz_ * 2 : 1;
      T* newptr = reinterpret_cast<T*>(new char[sizeof(T) * newcap]);

      size_t index = 0;
      try {
        for (; index < sz_; ++index) {
          new(newptr + index) T(ptr_[index]);
        }
        new(newptr + index) T(value);
      } catch (...) {
        for (size_t newindex = 0; newindex < index; ++newindex) {
          (newptr + newindex)->~T();
        }
        delete[] reinterpret_cast<char*>(newptr);
        throw;
      }

      for (size_t index = 0; index < sz_; ++index) {
        (ptr_ + index)->~T();
      }

      delete[] reinterpret_cast<char*>(ptr_);
      ptr_ = newptr;
      cap_ = newcap;
    } else {
      new(ptr_ + sz_) T(value);
    }
      ++sz_;
  }

  void pop_back() {
    (ptr_ + sz_ - 1)->~T();
    --sz_;
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