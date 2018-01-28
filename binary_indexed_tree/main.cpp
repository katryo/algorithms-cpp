#include <iostream>
#include <vector>

using namespace std;

int n;
int binary_indexed_tree[1000010];

void add(int a, int w) {
    for (int x = a; x <= n; x += x & -x) {
        binary_indexed_tree[x] += w;
    }
}

// v[a] += w
void add_zero_origin(int a, int w) {
    for (int x = a; x < n; x |= x + 1) {
        binary_indexed_tree[x] += w;
    }
}

// v[0] + ... + v[a - 1]
int sum_zero_origin(int a) {
    int ret = 0;
    for (int x = a; x >= 0; x = (x & (x + 1)) - 1) {
        ret += binary_indexed_tree[x];
    }
    return ret;
}

int sum(int a) {
    int ret = 0;
    for (int x = a; x > 0; x -= x & -x) {
        ret += binary_indexed_tree[x];
    }
    return ret;
}

int main() {
    freopen("input0.txt", "r", stdin);
    cin >> n;


    int ai;
    for (int i = 1; i < n + 1; ++i) {
        cin >> ai;
        add(i, ai);
    }

    cout << sum(1) << endl;
    cout << sum_zero_origin(1) << endl;

    return 0;
}