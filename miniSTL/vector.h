#pragma once

namespace ministl {

template<typename T>
class vector {
 public:
  vector();
  vector(const vector& other);
  vector& operator=(const vector& other);

  ~vector();

 private:
  T*      data_;
  size_t  size_;
  size_t  capacity_;
};

}