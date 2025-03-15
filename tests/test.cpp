#include <iostream>
#include "vector.h"

int main() {
  // std::cout << "Hello world!\n";
  ministl::vector<int> test;
  std::cout << "Size: " << test.size() << ", Capacity: " 
            << test.capacity() << '\n';
  test.reserve(10);
  std::cout << "Size: " << test.size() << ", Capacity: " 
            << test.capacity() << '\n';

  return 0;
}