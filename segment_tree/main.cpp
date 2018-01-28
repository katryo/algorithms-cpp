#include <iostream>
#include <vector>

// https://www.slideshare.net/iwiwi/ss-3578491

using namespace std;

const int MAX_N = 131072;

struct SegmentTree {
    vector<int> data;
    int n;

    explicit SegmentTree(int n_input) {
        for (int j = 0; j < n_input * 2 - 1; ++j) {
            data.push_back(INT_MAX);
        }
        n = n_input;
    }

    void update(int i, int x) {
        i += n - 1;
        data[i] = x;

        while (i > 0) {
            i = (i - 1) / 2;
            data[i] = min(data[i * 2 + 1], data[i * 2 + 2]);
        }
    }

    int at(int i) {
        return data[n - 1 + i];
    }

    /**
     * Returns the minimum number in [a, b).
     * @param a
     * @param b
     * @param node
     * @param node_left_idx
     * @param node_right_idx
     * @return
     */
    int min_in_half_open_interval(int a, int b, int node, int node_left_idx, int node_right_idx) {
        if (node_right_idx <= a || b <= node_left_idx) return INT_MAX;
        if (a <= node_left_idx && node_right_idx <= b) return data[node];
        else {
            int vl = min_in_half_open_interval(a, b, node * 2 + 1, node_left_idx, (node_left_idx + node_right_idx) / 2);
            int vr = min_in_half_open_interval(a, b, node * 2 + 2, (node_left_idx + node_right_idx) / 2, node_right_idx);
            return min(vl, vr);
        }
    }

};

int main() {
    freopen("input0.txt", "r", stdin);
    int n, ii, x;
    cin >> n;
    SegmentTree tree(n);

    vector<int> a;
    int ai;
    for (int i = 0; i < n; ++i) {
        cin >> ai;
        a.push_back(ai);
    }
    cin >> ii >> x;

    for (int j = 0; j < n; ++j) {
        tree.update(j + 1, a[j]);
    }

    for (int k = 0; k < n; ++k) {
        cout << tree.at(k + 1) << " ";
    }
    cout << endl;

    tree.update(ii, x);

    for (int k = 0; k < n; ++k) {
        cout << tree.at(k + 1) << " ";
    }
    cout << endl;

    cout << tree.min_in_half_open_interval(4, 6, 0, 0, n) << endl;
    cout << tree.min_in_half_open_interval(9, 11, 0, 0, n) << endl;

    return 0;
}