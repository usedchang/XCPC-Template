void solve(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>G(n+1);
    vector<int>nxt(n+1);
    vector<int>in(n+1),out(n+1);
    for(int i=1;i<=m;i++){
        int x,y;
        cin>>x>>y;
        G[x].emplace_back(y);
        ++in[y],++out[x];
    }
    auto find=[&]() ->int {
        int cnt1=0,cnt2=0;
        for(int i=1;i<=n;i++){
            if(in[i]-out[i]<-1||in[i]-out[i]>1) return -1;
            cnt1+=(in[i]-out[i]==-1);
            cnt2+=(in[i]-out[i]==1);
        }
        if(cnt1+cnt2==0){
            for(int i=1;i<=n;i++){
                if(out[i]>0) return i;
            }
        }//存在欧拉回路,需要保证图联通
        else if(cnt1==1&&cnt2==1){
            for(int i=1;i<=n;i++){
                if(out[i]-in[i]==1) return i;
            }
        }//存在欧拉路径
        return -1;
    };//找到起点
    int s=find();
    if(s==-1){
        cout<<"No"<<endl;
        return;
    }
    vector<int>res;
    vector<char>vis(m+1);
    for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].end());
    auto dfs=[&](auto &&dfs,int u) ->void {
        while(nxt[u]<G[u].size()){
            int v=G[u][nxt[u]];
            nxt[u]++;//当前弧优化
            dfs(dfs,v);
        }
        res.push_back(u);
    };
    dfs(dfs,s);
    if(res.size()!=m+1){
        cout<<"No"<<endl;
        return;
    }
    reverse(res.begin(),res.end());
    for(int x:res) cout<<x<<' ';
    cout<<endl;
}
