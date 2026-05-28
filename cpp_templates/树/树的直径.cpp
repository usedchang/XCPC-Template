const int N=2e5+10;
vector<int>G[N];
bool vis[N];
ll d[N],s=1;
void dfs(int u,int f){
    for(auto &v:G[u]){
        if(v==f) continue;
        d[v]=d[u]+1;
        dfs(v,u);
    }
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int n;cin>>n;
    for(int i=1,x,y;i<n;i++){
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    d[s]=0;dfs(s,0);
    for(int i=1;i<=n;i++) if(d[i]>d[s]) s=i;
    d[s]=0;dfs(s,0);
    ll ans=0;
    for(int i=1;i<=n;i++) ans=max(ans,d[i]);
    cout<<ans<<endl;
    return 0;
}
