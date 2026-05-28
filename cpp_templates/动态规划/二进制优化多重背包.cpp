const ll INF=1e15;
void solve(){
    int n,w;
    cin>>n>>w;
    vector<ll>dp(w+1,INF);
    dp[0]=0;
    for(int i=1;i<=n;i++){
        int l,c;cin>>l>>c;
        for(int k=1;c>0;k*=2){
            ll cur=min(c,k);
            for(int j=w;j>=1LL*cur*l;j--){
                dp[j]=min(dp[j],dp[j-1LL*cur*l]+cur);
            }
            c-=cur;
        }
    }
    if(dp[w]>=INF) cout<<-1<<endl;
    else cout<<dp[w]<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    solve();
    return 0;
}
