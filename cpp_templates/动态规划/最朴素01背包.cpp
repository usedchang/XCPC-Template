void solve(){
    int w,n;cin>>w>>n;
    vector<int>a(n+1),b(n+1);
    vector<int>f(w+1);
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(int i=1;i<=n;i++) {
        for(int j=w;j>=a[i];j--){
            f[j]=max(f[j-a[i]]+b[i],f[j]);
        }
    }
    cout<<f[w]<<endl;
}
