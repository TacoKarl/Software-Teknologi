#pragma once
#include <iostream>

class Array {
public:
  Array(int size) {
    size_ = size;
    search = 0;
    a_ = new int[size_];
    max_ = -2147483647; // min int
    min_ = 2147483647;  // max int
    for (int i = 0; i < size_; i++) {
      a_[i] = 0;
    }
  }
  ~Array() { delete[] a_; }
  void insert(int num) {
    a_[pos] = num;
    pos++;
    if (pos == size_)
      pos = 0;
  }
  bool contains(int x) {

    if (search == size_) {
      search = 0;
      return false;
    }

    else if (a_[search] == x) {
      search = 0;
      return true;
    }

    search++;
    return contains(x);
  }
  void minMax(int index = 0) {
    // Base case: if index reaches size_, print min and max and return
    if (index == size_) {
      std::cout << "Min: " << min_ << "\nMax: " << max_ << std::endl;
      return;
    }

    // Update min and max if necessary
    if (a_[index] < min_) {
      min_ = a_[index];
    }
    if (a_[index] > max_) {
      max_ = a_[index];
    }

    // Recursive call with next index
    minMax(index + 1);
  }

private:
  int *a_;
  int pos = 0;
  int size_, min_, max_;
  int search = 0;
};
