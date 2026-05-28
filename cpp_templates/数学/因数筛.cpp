const int N = 1000010;
int p[N];     // p[i]: i 的最小质因子（spf）
int pr[N];    // pr[]: 质数表
int cnt;
int d[N];     // d[i]: i 的正因数个数
int a[N];     // a[i]: i 的最小质因子的指数
void init(int n) {
    d[1] = 1; a[1] = 0; p[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!p[i]) {                    // i 是质数
            p[i] = pr[++cnt] = i;
            d[i] = 2;
            a[i] = 1;
        }
        for(int j = 1; j <= cnt && 1LL * i * pr[j] <= n; j++) {
            int m = i * pr[j];
            p[m] = pr[j];              // 记录 m 的最小质因子
            if(p[i] == pr[j]) {        // 还是同一个质因子
                d[m] = d[i] / (a[i] + 1) * (a[i] + 2);
                a[m] = a[i] + 1;
                break;
            } 
            else {                     // 新增一个不同质因子
                d[m] = d[i] * 2;       // 等价于 d[i] * d[pr[j]]
                a[m] = 1;
            }
        }
    }
}
