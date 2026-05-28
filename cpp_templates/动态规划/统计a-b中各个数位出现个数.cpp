ll dp[18][18][2][2];
int digit[18],target;
ll dfs(int pos,int cnt,bool limit,bool lead){
    if(pos==-1) return cnt;
    if(dp[pos][cnt][limit][lead]!=-1) return dp[pos][cnt][limit][lead];
    int up=(limit)?digit[pos]:9;
    ll res=0;
    for(int i=0;i<=up;i++){
        int ncnt=cnt;
        if(i==target){
            if(!(lead&&i==0)){
                ncnt++;
            }
        }
        bool nlead=lead&&(i==0);
        bool nlimit=limit&&(i==up);
        res+=dfs(pos-1,ncnt,nlimit,nlead);
    }
    return dp[pos][cnt][limit][lead]=res;
}
ll solve(ll x){
    if(x<0) return 0;
    int len=0;
    while(x>0){
        digit[len++]=x%10;
        x/=10;
    }
    memset(dp,-1,sizeof(dp));
    return dfs(len-1,0,true,true);
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    ll a,b;cin>>a>>b;
    for(int i=0;i<10;i++){
        target=i;
        cout<<solve(b)-solve(a-1)<<' ';
    }
    cout<<endl;
    return 0;
}
