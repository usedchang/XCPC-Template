struct node{
    int u;ll w;
};
vector<node>G[N];
ll dis[N];
bool inq[N];
int n,m,s;
void spfa(int s){
    fill(dis+1,dis+1+n,INT_MAX);
    queue<int>Q;
    Q.push(s);
    dis[s]=0;
    inq[s]=1;
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        inq[u]=0;
        for(auto &[v,w]:G[u]){
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!inq[v]){
                    Q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
}
void solve(){
    cin>>n>>m>>s;
    for(int i=1;i<=m;i++){
        int x,y;ll w;
        cin>>x>>y>>w;
        G[x].push_back({y,w});
    }
    spfa(s);
    for(int i=1;i<=n;i++) cout<<dis[i]<<' ';
    cout<<endl;
}
