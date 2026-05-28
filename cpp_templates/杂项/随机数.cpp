#include<bits/stdc++.h>
using namespace std;
mt19937 rng;                // 32 位梅森旋转生成器
mt19937_64 rng64;           // 64 位梅森旋转生成器
struct Random {    
    // 构造函数：用随机设备 + 时间戳初始化种子
    Random() {
        auto seed = random_device{}();
        auto time_seed = chrono::steady_clock::now().time_since_epoch().count();
        rng.seed(seed ^ time_seed);
        rng64.seed(seed ^ time_seed);
    }
    template<typename T>
    T randInt(T l, T r) {
    //static_assert(is_integral<T>::value, "T must be an integral type");
        uniform_int_distribution<T> dist(l, r);
        return dist(rng);
    }// 生成 [l, r] 范围内的随机整数（支持 int/long long/short 等）
    template<typename T>
    T randDouble(T l, T r) {
    //static_assert(is_floating_point<T>::value, "T must be a floating point type");
        uniform_real_distribution<T> dist(l, r);
        return dist(rng);
    }// 生成 [l, r) 范围内的随机浮点数（支持 float/double/long double）
};
// ---------------- 示例用法 ----------------
int main() {
    Random rnd;  // 全局或局部声明均可
    int a = rnd.randInt(1, 100);          // [1, 100]
    long long b = rnd.randInt(0LL, 114514LL); // [0, 114514]
    double c = rnd.randDouble(0.0, 1e18);  // [0.0, 1e18)
    std::vector<int> vec = {1, 2, 3, 4, 5};
    shuffle(vec.begin(), vec.end(),rng);
    cout<<"a="<<a<<endl;
    cout<<"b="<<b<<endl;
    cout<<fixed<<setprecision(10)<<c<<endl;
    cout<<"vec:=";
    for(int x:vec) cout<<x<<' ';
    return 0;
}
