const ll INF=1e18;
struct Mat{
    vector<vector<ll>>a;
    int n;
    Mat(int n):n(n){
        a=vector<vector<ll>>(n+1,vector<ll>(n+1,-INF));
    };
    Mat(){};
    friend Mat operator*(const Mat &A,const Mat &B){
        Mat C(A.n);
        for(int k=0;k<=A.n;k++){
            for(int i=0;i<=A.n;i++){
                for(int j=0;j<=A.n;j++){
                    C.a[i][j]=max(C.a[i][j],A.a[i][k]+B.a[k][j]);
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
        for(int i=0;i<=A.n;i++) S.a[i][i]=0;
        while(B>0){
            if(B&1) S*=A;
            A*=A;
            B>>=1;
        }
        A=move(S);
    }
}M;
