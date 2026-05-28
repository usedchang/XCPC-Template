vector<int>border(const string &s){
    int n=s.size();
    vector<int>pi(n);
    for(int i=1;i<n;i++){
        int j=pi[i-1];
        while(j>0&&s[j]!=s[i]) j=pi[j-1];
        if(s[i]==s[j]) j++;
        pi[i]=j;
    }
    return pi;
}
void kmp(const string &s,const string &t){
    vector<int>pi=border(t);
    int n=s.size(),m=t.size();
    for(int i=0,j=0;i<n;i++){
        while(j>0&&s[i]!=t[j]) j=pi[j-1];
        if(s[i]==t[j]) j++;
        if(j==m){
            j=pi[j-1];
            cout<<i-m+2<<endl;
        }
    }
    for(int x:pi) cout<<x<<' ';
    cout<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    string s,t;
    cin>>s>>t;
    kmp(s,t);
    return 0;
}
