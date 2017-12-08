#include <iostream>
#include <vector>
using namespace std;

struct DSU {
  vector<int> parent;
  vector<int> lengths;

  DSU(int size);
  int find(int x);
  bool union_elements(int x, int y);
};

DSU::DSU(int size) {
  for (int i = 0; i < size; ++i) {
    parent.push_back(i);
  }
  lengths.resize(size);
}

int DSU::find(int x) {
  if (parent[x] != x) {
    parent[x] = find(parent[x]);
  }
  return parent[x];
}

/**
 * Iff x and y has the common top parent returns false.
 * Otherwize, union a and b, then returns true.
 * @param x the index for the target
 * @param y the index for the target
 * @return true if x and w were disjoint and now united successfully
 */
bool DSU::union_elements(int x, int y){
  int y_parent = find(y);
  int x_parent = find(x);
  if (y_parent == x_parent) {
    return false;
  }

  if (lengths[y_parent] > lengths[x_parent]) {
    parent[x_parent] = y_parent;
    lengths[x_parent]++;
  } else {
    parent[y_parent] = x_parent;
    lengths[x_parent]++;
  }
  return false;
}

int main() {
  DSU dsu(10);
  dsu.union_elements(0, 1);
  dsu.union_elements(1, 2);
  dsu.union_elements(1, 3);

  dsu.union_elements(9, 8);
  dsu.union_elements(7, 9);
  for (int i = 0; i < 10; ++i) {
    cout << "find(" << i << "): " << dsu.find(i) << endl;
  }
  return 0;
}