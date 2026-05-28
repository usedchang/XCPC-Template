#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
void solve(){
    int w, n; cin >> w >> n;
    bitset<10001> dp;
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        int a; cin >> a;
        dp |= dp << a;
    }
    for(int j = w; j >= 0; j--) {
        if(dp[j]) {
            cout << j << endl;
            return;
        }
    }
}
