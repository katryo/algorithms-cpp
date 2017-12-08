#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Searcher {
  vector<vector<int>> grid;
  vector<vector<int>> explored;

  explicit Searcher(vector<vector<int>> givenGrid);
  stack<pair<int, int>> path;
  bool search(int row, int col);
};

Searcher::Searcher(vector<vector<int>> givenGrid) {
  grid = givenGrid;
  explored.resize(grid.size());
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      explored[i].push_back(0);
    }
  }
}

bool Searcher::search(int row, int col) {
  if (row == -1 || row == grid.size() || col == -1 || col == grid[0].size()) {
    return false;
  }
  if (explored[row][col] == 1) {
    return false;
  }
  if (grid[row][col] == 0) {
    return false;
  }

  explored[row][col] = 1;

  pair<int, int> location = make_pair(row, col);

  if (grid[row][col] == 2) {
    path.push(location);
    return true;
  }

  if (row > 0 && search(row-1, col)) {
    path.push(location);
    return true;
  }

  if (row < grid.size() && search(row+1, col)) {
    path.push(location);
    return true;
  }

  if (col > 0 && search(row, col-1)) {
    path.push(location);
    return true;
  }

  if (row < grid[0].size() && search(row, col+1)) {
    path.push(location);
    return true;
  }
  return false;
}


int main() {
  // 1 is a walkable path
  // 2 is the goal;
  vector<vector<int>> grid(10);

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 20; ++j) {
      grid[i].push_back(0);
    }
  }

  for (int k = 0; k < 8; ++k) {
    grid[5][k] = 1;
  }

  for (int l = 5; l < 9; ++l) {
    grid[l][7] = 1;
  }

  grid[5][0] = 2;

  Searcher searcher(grid);

  searcher.search(8, 7);

  stack<pair<int, int>> path = searcher.path;

  for (int m = 0; m < grid.size(); ++m) {
    for (int i = 0; i < grid[0].size(); ++i) {
      cout << grid[m][i];
    }
    cout << endl;
  }

  while (!path.empty()) {
    pair<int, int> point = path.top();
    cout << "(" << point.first << ", " << point.second << ")" << endl;
    path.pop();
  }

  return 0;
}