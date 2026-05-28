//P7972 Self Permutation
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll mod=1e9+7;
void solve(){
    int n;cin>>n;
    vector<int>L(n+1),R(n+1),st,a(n+1);
    vector<ll>dp(n+1);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        int lc=0;
        while(!st.empty()&&a[st.back()]>=a[i]){
            lc=st.back();
            st.pop_back();
        }
        L[i]=lc;
        if(!st.empty()) R[st.back()]=i;
        st.emplace_back(i); 
    }
    auto dfs=[&](auto &&dfs,int u,int l,int r) ->void {
        if(L[u]) dfs(dfs,L[u],l,u-1);
        if(R[u]) dfs(dfs,R[u],u+1,r);
        (dp[u]+=(dp[L[u]]+1)*(dp[R[u]]+1)%mod)%=mod;
        if(l>1) (dp[u]+=dp[R[u]])%=mod;
        if(r<n) (dp[u]+=dp[L[u]])%=mod;   
    };
    dfs(dfs,st.front(),1,n);
    cout<<dp[st.front()]<<endl;
}
