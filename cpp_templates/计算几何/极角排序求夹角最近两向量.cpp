#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
typedef long double ld;
const ll INF=1e18;
const ld pi=acos(-1);
struct Point{
    ll x,y;
    int id,idx;
    Point(ll x,ll y,int idx):x(x),y(y),idx(idx){
        if(x>=0&&y>=0) id=1;
        else if(x>=0&&y<0) id=2;
        else if(x<0&&y<0) id=3;
        else id=4; 
    };
    Point(){};
    friend bool operator<(Point A,Point B){
        if(A.id!=B.id) return A.id<B.id;
        return A.x*B.y-A.y*B.x<0; 
    }//极角排序
};
void solve(){
    int n;cin>>n;
    vector<Point>a(n+2);
    for(int i=1;i<=n;i++) {
        ll x,y;
        cin>>x>>y;
        a[i]=Point(x,y,i);
    }
    sort(a.begin()+1,a.begin()+1+n);
    ll x=0,y=0;
    auto calc=[&](Point &A,Point &B) ->ld {
        ld cross=A.x*B.y-A.y*B.x;
        ld dot=A.x*B.x+A.y*B.y;
        return fabsl(atan2l(cross,dot));
    };//较小精度损失的计算角度
    ++n;
    a[n]=a[1];//让 n和1比一次
    ld mn=INF;
    for(int i=1;i<n;i++){
        ld res=calc(a[i],a[i+1]);
        if(res<mn){
            x=a[i].idx,y=a[i+1].idx;
            mn=res;
        }
    }
    cout<<x<<' '<<y<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    solve();
    return 0;
}
