struct Mat{
    vector<vector<ll>>a;
    int n;
    Mat(int n):n(n){
        a=vector<vector<ll>>(n+1,vector<ll>(n+1));
    };
    Mat(){};
    friend Mat operator+(Mat &A,Mat &B){
        Mat C(A.n);
        for(int i=0;i<=A.n;i++){
            for(int j=0;j<=A.n;j++){
                C.a[i][j]=(A.a[i][j]+B.a[i][j])%mod;
            }
        }
        return C;
    }
    friend Mat operator+=(Mat &A,Mat &B){
        A=A+B;
        return A;
    }
    friend Mat operator*(Mat &A,Mat &B){
        Mat C(A.n);
        for(int k=0;k<=A.n;k++){
            for(int i=0;i<=A.n;i++){
                if(A.a[i][k]==0) continue;
                for(int j=0;j<=A.n;j++){
                    C.a[i][j]=(C.a[i][j]+A.a[i][k]*B.a[k][j]%mod)%mod;
                }
            }
        }
        return C;
    }
    friend Mat operator*=(Mat &A,Mat &B){
        A=A*B;
        return A;
    }
    void q_pow(Mat &A,ll B){
        Mat S(A.n);//单位矩阵
        for(int i=0;i<=A.n;i++) S.a[i][i]=1;
        while(B>0){
            if(B&1){
                S*=A;
            }
            A*=A;
            B>>=1;
        }
        A=move(S);
    }
}M;
