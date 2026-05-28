#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, pair<int, int>> P;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;cin >> N;
    vector<ll> A(N), B(N);
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) cin >> B[i];
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({A[0] + B[0], {0, 0}});
    for (int k = 0; k < N; ++k) {
        P top = pq.top();
        pq.pop();
        ll sum = top.first;
        int i = top.second.first;
        int j = top.second.second;
        if (k > 0) cout << ' ';
        cout << sum;
        if (j + 1 < N) {
            pq.push({A[i] + B[j+1], {i, j+1}});
        }
        if (j == 0 && i + 1 < N) {
            pq.push({A[i+1] + B[j], {i+1, j}});
        }
    }
    cout << endl;
    return 0;
}
