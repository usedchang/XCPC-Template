vector<int>Kmp(string s){
    vector<int>pi(s.size()+1);
    for(int i=1;i<s.size();i++){
        int j=pi[i-1];
        while(j&&s[j]!=s[i]) j=pi[j-1];
        if(s[i]==s[j]) j++;
        pi[i]=j;
    }
    return pi;
}
void solve(){
    string s,t;
    cin>>t>>s;
    string res=s+"#"+t;
    vector<int>pi=Kmp(res);
    vector<int>ans=Kmp(s);
    for(int i=s.size();i<pi.size();i++){
        if(pi[i]==s.size()) cout<<i-s.size()*2+1<<endl;
    }
    for(int i=0;i<s.size();i++) cout<<ans[i]<<' ';
    cout<<endl;
}
