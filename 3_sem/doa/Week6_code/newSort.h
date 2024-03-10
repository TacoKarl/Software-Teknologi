#include <vector>

using namespace std;

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
