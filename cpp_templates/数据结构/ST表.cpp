#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const ll INF=4e18;
struct ST{
    ST(){};
    vector<vector<ll>>mx,mn;
    ST(const vector<ll>&a){
        int n=a.size()-1;
        mx=vector<vector<ll>>(n+1,vector<ll>(21,-INF));
        mn=vector<vector<ll>>(n+1,vector<ll>(21,INF));
        for(int i=1;i<=n;i++) mx[i][0]=mn[i][0]=a[i];
        for(int i=1;i<=21;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                mx[j][i]=(mx[j][i-1]>mx[j+(1<<i-1)][i-1])?mx[j][i-1]:mx[j+(1<<i-1)][i-1];
                mn[j][i]=(mn[j][i-1]<mn[j+(1<<i-1)][i-1])?mn[j][i-1]:mn[j+(1<<i-1)][i-1];
            }
        }
    };
    ll qry_mx(int l,int r){
        int len=__lg(r-l+1);//31-__builtin_clz(r-l+1)
        return (mx[l][len]>mx[r-(1<<len)+1][len])?mx[l][len]:mx[r-(1<<len)+1][len];
    }  
    ll qry_mn(int l,int r){
        int len=__lg(r-l+1);//31-__builtin_clz(r-l+1)
        return (mn[l][len]<mn[r-(1<<len)+1][len])?mn[l][len]:mn[r-(1<<len)+1][len];
    }  
};
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int n,q,l,r;cin>>n>>q;
    vector<ll>a(n+1);
    for(int i=1;i<=n;i++) cin>>a[i];
    ST st(a);
    while(q--){
        cin>>l>>r;
        cout<<st.qry_mx(l,r)<<endl;
    }
    return 0;
}
