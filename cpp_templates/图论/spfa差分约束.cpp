const int N=2e5+5;
struct node{
    int u;ll w;
};
vector<node>G[N];
int cnt[N];
bool inq[N];
ll dis[N];
int n,m;
bool spfa(){
    fill(dis+1,dis+1+n,INT_MAX);
    queue<int>Q;
    Q.push(0);
    inq[0]=0;
    cnt[0]=1;
    while(!Q.empty()){
        int u=Q.front();
        Q.pop();
        inq[u]=false;
        for(auto &[v,w]:G[u]){
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!inq[v]){
                    cnt[v]++;
                    if(cnt[v]>n) return false;
                    Q.push(v);
                    inq[v]=1;
                }
            }
        }
    }
    return true;
}
void solve(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int x,y;ll w;cin>>x>>y>>w;
        G[y].push_back({x,w});
    }
    for(int i=1;i<=n;i++){
        G[0].push_back({i,0});
    }
    if(spfa()){
         for(int i=1;i<=n;i++) cout<<dis[i]<<' ';
        cout<<endl;
    }
    else cout<<"NO"<<endl;
}
