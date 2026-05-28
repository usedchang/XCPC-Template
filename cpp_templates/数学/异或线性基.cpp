struct LB{
    vector<ll>a;
    bool flag;
    LB(){
        flag=false;
        a.resize(63);
    }
    bool insert(ll x){
        for(int i=61;i>=0;i--){
            if(x>>i&1LL){
                if(!a[i]) {
                    a[i]=x;
                    return true;
                } 
                x^=a[i];
            }
        }
        flag=true;
        return false;
    }
    ll ask_max(){
        ll ans=0;
        for(int i=61;i>=0;i--){
            if((ans^a[i])>ans) ans^=a[i];
        }
        return ans;
    }
    ll ask_min(){
        if(flag) return 0;
        for(int i=0;i<=61;i++){
            if(a[i]) return a[i];
        }
        return 0;
    }
};
