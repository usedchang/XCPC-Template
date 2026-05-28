//P4551 最长异或路径
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
struct ZTrie{
    vector<array<int,2>>son;
    vector<int>cnt;
    int idx=0;
    ZTrie(int n){
        son.resize(n+1);
        cnt.resize(n+1);
    }
    void insert(int x){
        int p=0;
        for(int i=31;i>=0;i--) {
            int bit=(x>>i&1);
            if(!son[p][bit]) son[p][bit]=(++idx);
            p=son[p][bit];
        }
    }
    int query(int x){
        int ans=0,p=0;
        for(int i=31;i>=0;i--){
            int bit=(x>>i&1);
            if(son[p][bit^1]) p=son[p][bit^1],ans|=(1<<i);
            else if(son[p][bit]) p=son[p][bit];
            else return ans;
        }
        return ans;
    }
}trie(2e6);
const int N=2e5+5;
struct node{
    int u,w;
};
vector<node>G[N];
int ans=0;
void dfs(int u,int fa,int sum){
    trie.insert(sum);
    ans=max(ans,trie.query(sum));
    for(auto &[v,w]:G[u]){
        if(v==fa) continue;
        dfs(v,u,sum^w);
    }
}
void solve(){
    int n;cin>>n;
    for(int i=1;i<n;i++){
        int x,y,w;cin>>x>>y>>w;
        G[x].push_back({y,w});
        G[y].push_back({x,w});
    }
    dfs(1,0,0);
    cout<<ans<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    solve();
    return 0;
}
