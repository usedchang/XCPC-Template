// 线性筛：一次求出素数表与莫比乌斯函数；用法见正文。
const int N=1e6+5;
int p[N],vis[N],cnt;
int mu[N];
void init(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){
            p[cnt++]=i;
            mu[i]=-1;
        }
        for(int j=0;i*p[j]<=n;j++){
            int m=i*p[j];
            vis[m]=1;
            if(i%p[j]==0){
                mu[m]=0;
                break;
            }
            else{
                mu[m]=-mu[i];
            } 
        }
    }
}
