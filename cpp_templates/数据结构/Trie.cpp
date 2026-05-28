struct Trie{
    vector<int>cnt;
    vector< array<int,65> >son;
    int idx=0;
    Trie(int n){
        cnt.resize(n+1);
        son.resize(n+1);
    }
    void insert(string &s){
        int num;
        int p=0;
        for(char &c:s){
            if(isdigit(c)) num=c-'0'+52;
            else if(islower(c)) num=c-'a'+26;
            else if(isupper(c)) num=c-'A';
            if(!son[p][num]) son[p][num]=(++idx);
            p=son[p][num];
            ++cnt[p];
        }
    }
    int query(string &s){
        int num;
        int p=0;
        for(char &c:s){
            if(isdigit(c)) num=c-'0'+52;
            else if(islower(c)) num=c-'a'+26;
            else if(isupper(c)) num=c-'A';
            if(!son[p][num]) return 0;
            p=son[p][num];
        }
        return cnt[p];
    }
}trie;
