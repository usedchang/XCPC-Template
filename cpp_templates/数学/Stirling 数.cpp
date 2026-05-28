typedef unsigned long long ll;
const int N=10010;
ll dp[N][N/10],p;
void init(){
    dp[1][1]=1;
    for(int i=2;i<=10000;i++){
        for(int j=1;j<=1000;j++){
            dp[i][j]=((j%p)*dp[i-1][j]%p+dp[i-1][j-1])%p;
        }
    }
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m>>p;
    init();
    cout<<dp[n][m]<<endl;
    return 0;
}
