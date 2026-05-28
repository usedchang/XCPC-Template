#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int N=1e6+5;
vector<ll>G[N];
vector<ll>ans,siz;
void add(int x,int y){
    G[x].emplace_back(y);
    G[y].emplace_back(x);
}
void dfs(int u,int f){
    siz[u]=1;
    for(auto &v:G[u]){
        if(v==f) continue;
        dfs(v,u);
        siz[u]+=siz[v];
    }
}
void __dfs(int u,int f){
    for(auto &v:G[u]){
        if(v==f) continue;
        ans[v]=(ans[u]+siz[1]-siz[v]*2);
        __dfs(v,u);
    }
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int n;cin>>n;
    ans.resize(n+1);
    siz.resize(n+1);
    for(int i=1;i<n;i++){
        int x,y;cin>>x>>y;
        add(x,y);
    }
    dfs(1,0);
    ans[1]=siz[1];
    __dfs(1,0);
    cout<<max_element(ans.begin()+1,ans.begin()+1+n)-ans.begin()<<endl;
    return 0;
}
