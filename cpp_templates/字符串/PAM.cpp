//Stop learning useless algorithms, go and solve some problems, learn how to use binary search.
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
const int N=5e5+5;
struct PAM{
    int tot,last,sz;    // tot:节点数,last:以当前位置结尾最长回文串节点 sz:当前串长
    int len[N];         // len[i]:节点i代表的回文长度
    int fail[N];        // fail[i]:节点i的最长回文后缀
    int ch[N][26];      // ch[i][c]:回文串i两边加c得到的节点
    int cnt[N];         // cnt[i]:节点i的出现次数
    int num[N];         // num[i]:以该节点结尾的回文后缀个数
    char s[N];          // 原串,下标从1开始,s[0]是哨兵
    int newnode(int l) {
        ++tot;
        memset(ch[tot],0,sizeof ch[tot]);
        len[tot]=l;
        fail[tot]=cnt[tot]=num[tot]=0;
        return tot;
    }
    PAM(){ init();}
    void init() { //初始化两个根
        tot=-1,last=0;sz=0; 
        newnode(0);     //节点0:偶根,len=0
        newnode(-1);    //节点1:奇根,len=-1
        fail[0]=1;      //偶根的fail指向奇根
        fail[1]=0;
        s[0]=-1;        //哨兵
    }
    int get_fail(int x){
        while(s[sz-len[x]-1]!=s[sz]) x=fail[x];
        return x;
    }
    void insert(int c){
        s[++sz]=c;
        int p=get_fail(last);
        if(!ch[p][c]){
            int cur=newnode(len[p]+2);
            fail[cur]=ch[get_fail(fail[p])][c];
            ch[p][c]=cur;
            num[cur]=num[fail[cur]]+1;
        }
        last=ch[p][c];
        cnt[last]++;
    }
    void insert(char c){ insert(c-'a');}
    void count(){
        for(int i=tot;i>=2;--i) cnt[fail[i]]+=cnt[i];
    }
}pam;
string s;
void solve(){
    cin>>s;
    int k=0;
    for(char c:s){
        char p=(c-97+k)%26+97;
        pam.insert(p);
        k=pam.num[pam.last];
        cout<<k<<' ';
    }
    cout<<endl;
}
int main(){
    cin.tie(0)->ios::sync_with_stdio(false);
    solve();
    return 0;
}