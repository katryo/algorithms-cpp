#include <iostream>

// https://www.slideshare.net/iwiwi/ss-3578511

int N, dist[30][30];
int memo[30][1 << 30];
// Let dp[v][b] denotes the minimum cost of completing the travel from vertex v, state b.
int dp[30][1 << 4];
int brute_force_counter = 0;
int memo_counter = 0;

using namespace std;

int brute_force(int v, int bit_mask) {
    brute_force_counter++;
    if (bit_mask == (1 << N) - 1) return dist[v][0];

    int res = INT_MAX;

    for (int i = 0; i < N; ++i) {
        if (bit_mask & (1 << i)) continue;
        int new_bit_mask = bit_mask | (1 << i);
        int candidate = dist[v][i] + brute_force(i, new_bit_mask);
        res = min(res, candidate);
    }
    return res;
}

int memo_tsp(int v, int bit_mask) {
    if (memo[v][bit_mask] != 0) {
        return memo[v][bit_mask];
    }
    memo_counter++;
    if (bit_mask == (1 << N) - 1) return dist[v][0];

    int res = INT_MAX;

    for (int i = 0; i < N; ++i) {
        if (bit_mask & (1 << i)) continue;
        int new_bit_mask = bit_mask | (1 << i);
        int candidate = dist[v][i] + memo_tsp(i, new_bit_mask);
        res = min(res, candidate);
    }
    memo[v][bit_mask] = res;
    return res;
}

int loop_tsp(int v, int bit_mask) {
    for (int state = (1 << N) - 2; state > 0 ; --state) {
        for (int current = 0; current < N; ++current) {
            int candidate = INT_MAX;
            for (int future = 0; future < N; ++future) {
                int future_state = 1 << future;
                if (future_state & state) continue;
                int new_candidate = dp[future][state + future_state] + dist[current][future];
                candidate = min(candidate, new_candidate);
            }
            dp[current][state] = candidate;
        }
    }

    return dp[v][bit_mask];
}

int main() {
    freopen("input0.txt", "r", stdin);
    int m;
    int from, to, cost;

    cin >> N >> m;

    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> cost;
        dist[from][to] = cost;
        dist[to][from] = cost;
    }

    cout << brute_force(3, 1) << " " << brute_force_counter << endl;
    cout << memo_tsp(3, 1) << " " << memo_counter << endl;
    cout << loop_tsp(3, 1) << endl;

    return 0;
}