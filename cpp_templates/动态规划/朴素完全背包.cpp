#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int n,w;cin>>w>>n;
    vector<ll>a(n+1),b(n+1),f(w+1);
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(int i=1;i<=n;i++){
        for(int j=a[i];j<=w;j++){
            f[j]=max(f[j-a[i]]+b[i],f[j]);
        }
    }
    cout<<f[w]<<endl;
    return 0;
}
