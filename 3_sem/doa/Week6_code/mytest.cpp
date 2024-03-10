#include "sort.h"
#include <iostream>
#include <vector>
#pragma GCC diagnostic ignored "-Wc++11-extensions"

#define NUM_ELEMENTS 30 // number of elements in array
#define RANGE 25        // random numbers up to RANGE

int main() {
  vector<int> a;
  srand(time(0));
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    a.push_back(rand() % RANGE + 1);
  }

  std::cout << "vector before sorting:\n{";
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    if (i == NUM_ELEMENTS - 1) {
      cout << a[i] << flush;
    } else
      cout << a[i] << ", " << flush;
  }
  std::cout << "}\n";

  countingSort(a);

  std::cout << "vector after sorting:\n{";
  for (int i = 0; i < NUM_ELEMENTS; i++) {
    if (i == NUM_ELEMENTS - 1) {
      cout << a[i] << flush;
    } else
      cout << a[i] << ", " << flush;
  }
  std::cout << "}\n";

  return 0;
}
