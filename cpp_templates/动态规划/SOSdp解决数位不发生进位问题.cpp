//ARC136D
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int N=1e6+1;
int Flip(int x){
    int p=1,res=0;
    for(int i=0;i<6;i++){
        res+=(9-x%10)*p;
        x/=10;
        p*=10;
    }
    return res;
}//这个数的反集,如123->876
bool judge(int x){
    while(x){
        if(x%10>=5) return false;
        x/=10;
    }
    return true;
}//判定这个数与自身相加是否发生进位情况
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int n;cin>>n;
    vector<ll>dp(N);
    vector<int>a(n+1);
    for(int i=1,x;i<=n;i++){
        cin>>a[i];
        dp[a[i]]++;
    } 
    int p=1;
    for(int i=1;i<=6;i++){//本质是对每个十进制数位进行一次强缀和,又称高维前缀和(SOS dp)
        for(int j=0;j<N;j++){
            if((j/p)%10) dp[j]+=dp[j-p];
        }
        p*=10;
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        int x=Flip(a[i]);
        ans+=dp[x];
        if(judge(a[i])) ans--;
    }
    cout<<ans/2<<endl;
    return 0;
}
