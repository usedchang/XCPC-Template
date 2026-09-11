//Stop learning useless algorithms, go and solve some problems, learn how to use binary search.
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
vector<int> zf(string s) {
  int n = (int)s.size();
  vector<int> z(n);
  z[0]=n;
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r && z[i - l] < r - i + 1) {
      z[i] = z[i - l];
    } else {
      z[i] = max(0, r - i + 1);
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}
void solve(){
    string s,t;
    cin>>t>>s;
    vector<int>p=zf(s);
    ll ans=0;
    for(int i=0;i<s.size();i++) {
        ans^=1LL*(i+1)*(p[i]+1);
    }
    cout<<ans<<endl;
    p=zf(s+'#'+t);
    ans^=ans;
    for(int i=s.size()+1;i<p.size();i++){
        ans^=1LL*(i-s.size())*(p[i]+1);
    }
    cout<<ans<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int T=1;//cin>>T;
    while(T--) solve();
    return 0;
}