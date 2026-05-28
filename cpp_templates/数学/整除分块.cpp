void solve(){
    ll n;cin>>n;
    ll ans=0;
    for(int l=1,r;l<=n;l=r+1) {
        ll v=(n/l);
        r=min((n/v),n);
        ans+=v*(r-l+1);
    }
    cout<<ans<<endl;
}
