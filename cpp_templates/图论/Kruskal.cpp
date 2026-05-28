#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
ll ans;int n,m,cntn;
const int N=2e5+10;
int f[N];
int find(int x){
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}
struct node{
    int x,y,w;
    friend bool operator <(node a,node b){
        return a.w<b.w;
    }
}a[N];
void kruskal(){
    cntn=n;
    for(int i=1;i<=m;i++){
        int fx=find(a[i].x);
        int fy=find(a[i].y);
        if(fx!=fy){
            f[fx]=fy;
            cntn--;
            ans+=a[i].w;
            if(cntn==1) break;
        }
    }
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++){
        int x,y,w;
        cin>>a[i].x>>a[i].y>>a[i].w;
    }
    sort(a+1,a+1+m);
    kruskal();
    if(cntn==1) cout<<ans<<endl;
    else cout<<"none"<<endl;
    return 0;
}
