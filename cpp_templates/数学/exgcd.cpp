//P1516青蛙的约会
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    ll d=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
void solve(){
    int x,y,m,n,l;
    cin>>x>>y>>m>>n>>l;
    ll X,Y;
    ll d=exgcd(n-m,l,X,Y);
    if((x-y)%d) cout<<"Impossible"<<endl;
    else{
        ll s=(x-y)/d;
        ll mod=abs(l/d);
        X*=s;
        Y*=s;
        cout<<(X%mod+mod)%mod<<endl;
    }
}
