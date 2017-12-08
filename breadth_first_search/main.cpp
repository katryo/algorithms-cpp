#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

struct Node {
  int row;
  int col;
  Node *parent;
  Node(int row, int col, Node *parent);
};

Node::Node(int row_given, int col_given, Node *parent_given) {
  parent = parent_given;
  row = row_given;
  col = col_given;
}

struct Searcher {
  vector<vector<int>> grid;
  vector<vector<int>> explored;

  explicit Searcher(vector<vector<int>> givenGrid);
  stack<pair<int, int>> path;
  vector<vector<pair<int, int>>> layers;
  Node *search(int row, int col);
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

Node *Searcher::search(int row_start, int col_start) {

  Node *root = new Node(row_start, col_start, nullptr);
  queue<Node*> candidates;

  candidates.push(root);

  while(!candidates.empty()) {
    Node *candidate = candidates.front();
    candidates.pop();
    int col = candidate->col;
    int row = candidate->row;

    if (row == -1 || row == grid.size() || col == -1 || col == grid[0].size()) {
      continue;
    }
    if (explored[row][col] == 1) {
      continue;
    }
    if (grid[row][col] == 0) {
      continue;
    }

    explored[row][col] = 1;


    if (grid[row][col] == 2) {
      return candidate;
    }

    if (row > 0) {
      Node *upper = new Node(row-1, col, candidate);
      candidates.push(upper);
    }

    if (row < grid.size()-1) {
      Node *lower = new Node(row+1, col, candidate);
      candidates.push(lower);
    }

    if (col > 0) {
      Node *lefter = new Node(row, col-1, candidate);
      candidates.push(lefter);
    }

    if (col < grid[0].size()-1) {
      Node *righter = new Node(row, col+1, candidate);
      candidates.push(righter);
    }
  }
  return nullptr;
}

void print_path(Node *goal_node) {
  Node *p = goal_node;
  while (p != nullptr) {
    cout << "(" << p->row << ", " << p->col << ")" << endl;
    p = p->parent;
  }
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

  Node *goal_node = searcher.search(8, 7);

  for (int m = 0; m < grid.size(); ++m) {
    for (int i = 0; i < grid[0].size(); ++i) {
      cout << grid[m][i];
    }
    cout << endl;
  }

  print_path(goal_node);

  return 0;
}