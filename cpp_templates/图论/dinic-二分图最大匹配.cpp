#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll INF=4e18;
struct Dinic{
    struct E{
        int to;ll cap;int rev;
        //to:目标点,cap:容量,rev:反向边索引
    };//边集
    vector<vector<E>>g;
    vector<int>lv,it;//bfs层次，当前弧优化迭代器
    int n;
    Dinic(int n):g(n),lv(n),it(n),n(n){}
    int add(int u,int v,ll c){
        g[u].push_back({v,c,(int)g[v].size()});
        g[v].push_back({u,0,(int)g[u].size()-1});
        return (int)g[u].size()-1;
    }//添加边,返回正向边索引
    void bfs(int s){
        fill(lv.begin(),lv.end(),-1);
        queue<int>q;
        lv[s]=0;
        q.push(s);
        while(!q.empty()){
            int v=q.front();
            q.pop();
            for(auto &e:g[v]){
                //只走残余容量为正的边,且未访问
                if(e.cap>0&&lv[e.to]<0){
                    lv[e.to]=lv[v]+1;
                    q.push(e.to);
                }
            }
        }
    }//使用队列计算层次图
    ll dfs(int v,int t,ll f){
        if(v==t) return f;
        for(int &i=it[v];i<(int)g[v].size();i++){
            E &e=g[v][i];
            if(e.cap>0&&lv[v]<lv[e.to]){
                ll d=dfs(e.to,t,min(f,e.cap));
                if(d>0){
                    e.cap-=d;
                    g[e.to][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }//递归寻找增广路
    ll maxflow(int s,int t){
        ll f=0;
        while(true){
            bfs(s);//构建层次图
            if(lv[t]<0){
                return f;
            }//汇点不可达,返回
            fill(it.begin(),it.end(),0);//重置当前弧
            ll d;
            while((d=dfs(s,t,INF))>0) f+=d;
        }
    }
    vector<char>cut(int s){
        vector<char>vis(n);
        queue<int>Q;
        Q.emplace(s);
        vis[s]=1;
        while(!Q.empty()){
            int u=Q.front();
            Q.pop();
            for(auto &e:g[u]){
                if(e.cap>0&&!vis[e.to]){
                    vis[e.to]=1;
                    Q.emplace(e.to);
                }
            }
        }
        return vis;
    }
};
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int m,n;
    cin>>m>>n;
    int S=m+n,T=S+1;
    Dinic din(T+1);
    for(int i=0;i<m;i++) din.add(S,i,1);//S->m个左部节点
    for(int i=0;i<n-m;i++) din.add(i+m,T,1);//n-m个右部节点->T
    int a,b;
    while(cin>>a>>b&&!(a==-1&&b==-1)){
        --a,--b;
        din.add(a,b,1);
    }
    ll ans=din.maxflow(S,T);//求解最大流
    cout<<ans<<endl;
    for(int i=m;i<n;i++){
        for(auto &e:din.g[i]){
            if(e.to<m&&e.cap>0){
                cout<<e.to+1<<' '<<i+1<<endl;
            }
        }
    }
    return 0;
}