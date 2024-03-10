#ifndef _INSERTION_SORT_H_
#define _INSERTION_SORT_H_
#include <functional>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <vector>

using namespace std;

/**
 * Simple insertion sort.
 */
template <typename Comparable> void insertionSort(vector<Comparable> &a) {
  for (int p = 1; p < a.size(); ++p) {
    Comparable tmp = std::move(a[p]);

    int j;
    for (j = p; j > 0 && tmp < a[j - 1]; --j) {
      a[j] = std::move(a[j - 1]);
    }
    a[j] = std::move(tmp);
  }
}

/*
 * This is the more public version of insertion sort.
 * It requires a pair of iterators and a comparison
 * function object.
 */
template <typename Iterator, typename Comparator>
void insertionSort(const Iterator &begin, const Iterator &end,
                   Comparator less) {
  if (begin == end)
    return;

  for (Iterator j, p = begin + 1; p != end; ++p) {
    auto tmp = std::move(*p);
    for (j = p; j != begin && less(tmp, *(j - 1)); --j)
      *j = std::move(*(j - 1));
    *j = std::move(tmp);
  }
}

/*
 * The two-parameter version calls the three parameter version, using C++11.
 */
template <typename Iterator>
void insertionSort(const Iterator &begin, const Iterator &end) {
  insertionSort(begin, end, less<decltype(*begin)>());
}

// own function
template <typename Comparable> void selectionSort(vector<Comparable> &a) {
  // what the fuck?
  for (int i = 0; i < a.size(); i++) {

    for (int j = i + 1; j < a.size(); j++) {
      if (a[j] < a[i]) {
        std::swap(a[i], a[j]);
      }
    }
  }
}
// own function
template <typename T> void countingSort(vector<T> &a) {
  if (a.empty()) {
    cout << "Array empty\n";
    return;
  }
  // find max element
  int max = *max_element(a.begin(), a.end());

  vector<T> count(max + 1, 0);
  // tæl op hvor mange gange der er af hvert tal i original array
  // gem hvor mange gange der er et tal på deres respektive pladser i count
  // vector
  for (int num : a) {
    count[num]++;
  }
  // // Print vores count array
  // std::cout << "Count Array: ";
  // for (int i = 0; i <= max; ++i) {
  //   std::cout << static_cast<int>(count[i]) << " ";
  // }
  // std::cout << endl;
  // erstat index i original værdi med de laveste tal
  int index = 0;
  // cout << "{";
  for (int i = 0; i <= max; ++i) {
    while (count[i] > 0) {
      a[index++] = i;
      count[i]--;
      // if (i == max) {
      //   cout << a[index - 1] << flush;
      // } else
      //   cout << a[index - 1] << ", " << flush;
      // usleep(250000);
    }
  }
  // cout << "}\n";
}

#endif
