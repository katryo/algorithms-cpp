#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

const int INF = 100000;

struct Edge {
  int from;
  int to;
  int cost;
  Edge(int from, int to, int cost) {
    this->from = from;
    this->to = to;
    this->cost = cost;
  }
};

struct Node {
  int cost;
  int number;
  int best_prev_node_number;
  vector<Edge> edges;
  Node(int num) {
    number = num;
    cost = INF;
    edges = vector<Edge>();
    best_prev_node_number = -1;
  };

  void add_edge(Edge e) {
    edges.push_back(e);
  }

  bool operator<(const Node& another_node) const {
    return cost < another_node.cost;
  }

};

int main() {
  freopen("input0.txt","r",stdin);
  int n, m;
  cin >> n >> m;

  vector<Node> nodes;
  for (int i = 1; i < n+1; ++i) {
    Node node(i);
    nodes.push_back(node);
  }

  int from, to, cost;
  for (int j = 0; j < m; ++j) {
    cin >> from >> to >> cost;
    Edge e(from, to, cost);
    nodes[from - 1].add_edge(e);
  }
  int start;
  cin >> start;

  Node start_node = nodes[start-1];
  nodes[start-1].cost = 0;
  vector<Edge> es = start_node.edges;

  priority_queue<Node> pq;

  for (auto edge : start_node.edges) {
    nodes[edge.to - 1].cost = edge.cost;
    nodes[edge.to - 1].best_prev_node_number = start_node.number;
    pq.push(nodes[edge.to - 1]);
  }

  set<int> explored_node_numbers;
  explored_node_numbers.insert(start);

  int max_cost = 0;
  while (!pq.empty()) {
    Node min_node = pq.top();
    pq.pop();
    max_cost = max(max_cost, min_node.cost);
    if (explored_node_numbers.find(min_node.number) != explored_node_numbers.end()) {
      continue;
    }
    explored_node_numbers.insert(min_node.number);

    for (auto edge : min_node.edges) {
      Node changeable_node = nodes[edge.to - 1];
      if (nodes[edge.to - 1].cost > min_node.cost + edge.cost) {
        nodes[edge.to - 1].cost = min_node.cost + edge.cost;
        nodes[edge.to - 1].best_prev_node_number = edge.from;
        pq.push(changeable_node);
      }
    }
  }

  for (auto node : nodes) {
    cout << "node #" << node.number << " cost:" << node.cost << " best_prev: " << node.best_prev_node_number << endl;
  }

  Node cur = nodes[3];
  while (cur.number != 1) {
    cout << "to node #" << cur.number << endl;
    cur = nodes[cur.best_prev_node_number-1];
  }
  cout << "from node #" << cur.number << endl;

  return 0;
}