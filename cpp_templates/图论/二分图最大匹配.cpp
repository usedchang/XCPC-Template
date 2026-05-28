const int N=505;
vector<int>G[N];
int match[N];
bool vis[N];
bool dfs(int u){
    for(auto &v:G[u]){
        if(vis[v]) continue;
        vis[v]=1;
        if(!match[v]||dfs(match[v])){
            match[v]=u;
            return 1;
        }
    }
    return 0;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int n,m,e;cin>>n>>m>>e;
    for(int i=1;i<=e;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
    }
    ll ans=0;
    for(int i=1;i<=n;i++) {
        fill(vis+1,vis+1+n,false);
        ans+=dfs(i);
    }
    cout<<ans<<endl;
    return 0;
}
