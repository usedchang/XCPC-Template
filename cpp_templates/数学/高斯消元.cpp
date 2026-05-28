const int N=110;
const double eps=1e-8;
int n;
double a[N][N];
ll gauss(){
    ll c,r;
    for(c=0,r=0;c<n;c++){
        ll t=r;
        for(int i=r;i<n;i++){
            if(abs(a[i][c])>abs(a[t][c])) t=i;
        }
        if(abs(a[t][c])<eps) continue;
        for(int j=c;j<n+1;j++) swap(a[t][j],a[r][j]);//将绝对值最大的换到最顶端
        for(int j=n;j>=c;j--) a[r][j]/=a[r][c];//将当前行首位变成1
        for(int i=r+1;i<n;i++){
            if(abs(a[i][c])>eps){
                for(int j=n;j>=c;j--) a[i][j]-=a[r][j]*a[i][c];
            }
        }
        r++;
    }
    if(r<n){
        for(int i=r;i<n;i++) if(abs(a[i][n])>eps) return 2;
        return 1;
    }
    for(int i=n-1;i>=0;i--){
        for(int j=i+1;j<n;j++) a[i][n]-=a[i][j]*a[j][n];
    }
    return 0;
}
void solve(){
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            cin>>a[i][j];
        }
    }
    ll t=gauss();
    cout<<fixed<<setprecision(2);
    if(t==0) {
        for(int i=0;i<n;i++){
            if(abs(a[i][n])<eps) a[i][n]=abs(a[i][n]);
            cout<<a[i][n]<<endl;
        }
    }
    else cout<<"No Solution"<<endl;
}
