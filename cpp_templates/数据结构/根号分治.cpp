void solve(){
    int n,q;cin>>n>>q;
    vector<int>a(n+1);
    unordered_map< int,vector<int> >pos;//存储重数
    for(int i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]].push_back(i);
    }
    int siz=sqrt(n+0.5);
    vector<int>H;
    for(auto const&[x,y]:pos){
        if(y.size()>siz) H.emplace_back(x);
    }
    map<pair<int,int>,ll>mp;
    for(int i=0;i<H.size();i++){
        for(int j=0;j<H.size();j++){
            for(int &p:pos[H[i]]){
                mp[{H[i],H[j]}]+=pos[H[j]].end()-upper_bound(pos[H[j]].begin(),pos[H[j]].end(),p);
            }
        }
    }
    map<pair<int,int>,ll>memo;
    for(int i=1;i<=q;i++){
        int x,y;cin>>x>>y;
        if(memo.count({x,y})){
            cout<<memo[{x,y}]<<endl;
            continue;
        }
        if(pos[x].size()>siz&&pos[y].size()>siz) {
            cout<<(memo[{x,y}]=mp[{x,y}])<<endl;
        }
        else{
            ll ans=0;
            if(pos[x].size()<=pos[y].size()||pos[x].size()<=siz&&pos[y].size()<=siz){
                for(int &p:pos[x]){
                    ans+=pos[y].end()-upper_bound(pos[y].begin(),pos[y].end(),p);
                }
            }
            else{
                for(int &p:pos[y]){
                    ans+=lower_bound(pos[x].begin(),pos[x].end(),p)-pos[x].begin();
                }
            }
            cout<<(memo[{x,y}]=ans)<<endl;
        }
    }
}
