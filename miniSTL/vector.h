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

  ~vector() {}

 private:
  T*      ptr_;
  size_t  sz_;
  size_t  cap_;
};

}