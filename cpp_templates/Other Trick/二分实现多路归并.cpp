#include<bits/stdc++.h>
using namespace std;
long long calc(const vector<long long>& a, const vector<long long>& b, long long mid) {
    int n = a.size();
    long long cnt = 0;
    int j = n - 1;
    for (int i = 0; i < n; ++i) {
        while (j >= 0 && a[i] + b[j] > mid) j--;
        cnt += j + 1;
    }
    return cnt;
}
int main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int n;cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    long long l = a[0] + b[0], r = a.back() + b.back();
    while (l < r) {
        long long mid = l + (r - l) / 2; 
        if (calc(a, b, mid) >= n) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    long long x = l;
    vector<long long> res;
    res.reserve(n);
    int j = n - 1;
    for (int i = 0; i < n; ++i) {
        while (j >= 0 && a[i] + b[j] >= x) j--;
        for (int k = 0; k <= j; ++k) {
            res.push_back(a[i] + b[k]);
        }
    }
    int need = n - res.size();
    j = n - 1;
    for (int i = 0; i < n && need > 0; ++i) {
        while (j >= 0 && a[i] + b[j] > x) j--;
        int k = j;
        while (k >= 0 && a[i] + b[k] == x && need > 0) {
            res.push_back(x);
            need--;
            k--;
        }
    }
    sort(res.begin(), res.end());
    for (int i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }
    return 0;
}
