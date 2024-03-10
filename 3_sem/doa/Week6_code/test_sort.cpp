#include "insertion_sort.h"
#include "sort.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

void checkSort(const vector<int> &a) {
  for (int i = 0; i < a.size() - 1; ++i) {
    if (a[i] > a[i + 1]) {
      cout << "Error at " << i << endl;
    }
  }
  cout << "Finished checksort" << endl;
}

template <typename AnyType> void permute(vector<AnyType> &a) {
  for (int j = 1; j < a.size(); ++j) {
    swap(a[j], a[rand() % j]);
  }
}

int main() {
  const int NUM_ITEMS = 1000;

  vector<int> a(NUM_ITEMS);
  for (int i = 1; i < a.size(); ++i) {
    a[i] = a[i - 1] + 'a';
  }

  for (int theSeed = 0; theSeed < 10; ++theSeed) {
    srand(time(0) + theSeed);
    cout << "Insertion sort(a):\n";
    permute(a);
    insertionSort(a);
    checkSort(a);
    cout << endl;
    cout << "Insertion sort (begin(a), end(a));" << endl;
    permute(a);
    insertionSort(begin(a), end(a));
    checkSort(a);
    cout << endl;
    cout << "mergeSort(a)\n";
    permute(a);
    mergeSort(a);
    checkSort(a);
    cout << endl;
    cout << "quickSort(a)\n";
    permute(a);
    quickSort(a);
    checkSort(a);
    cout << endl;
    cout << "CountingSort(a)\n";
    permute(a);
    countingSort(a);
    checkSort(a);
    cout << endl;
    cout << "SelectionSort(a)\n";
    permute(a);
    selectionSort(a);
    checkSort(a);
    cout << endl;
  }

  return 0;
}
