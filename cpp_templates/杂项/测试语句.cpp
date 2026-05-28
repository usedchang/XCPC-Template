#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void test_speed() {
    long long cnt = 0;
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000000000; ++i) cnt += i; // 10^9 次加法
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    cout << "10^9 additions: " << diff.count() << "s" << endl;
}
volatile ll sink = 0;// 防止编译器优化：将结果写入 volatile 变量
void test_time() {
    const int batch = 100000; // 每批执行 10 万次运算，减少时间检查开销
    ll add_cnt = 0, mul_cnt = 0, mod_cnt = 0;
    
    // ========== 1. 测试加法 ==========
    {
        ll v = 0;
        auto start = chrono::high_resolution_clock::now();
        while (true) {
            // 执行一批运算
            for (int i = 0; i < batch; ++i) v += 1;
            add_cnt += batch;
            
            // 检查时间
            auto now = chrono::high_resolution_clock::now();
            if (chrono::duration_cast<chrono::seconds>(now - start).count() >= 1)
                break;
        }
        sink = v; // 确保 v 被使用，防止优化
    }
    
    // ========== 2. 测试乘法 ==========
    {
        ll v = 1;
        auto start = chrono::high_resolution_clock::now();
        while (true) {
            for (int i = 0; i < batch; ++i) {
                v *= 2;
                if (v > 1e18) v = 1; // 防止溢出
            }
            mul_cnt += batch;
            
            auto now = chrono::high_resolution_clock::now();
            if (chrono::duration_cast<chrono::seconds>(now - start).count() >= 1)
                break;
        }
        sink = v;
    }
    
    // ========== 3. 测试取模 ==========
    {
        const ll MOD = 1e9+7;
        ll v = 0;
        auto start = chrono::high_resolution_clock::now();
        while (true) {
            for (int i = 0; i < batch; ++i) v = (v + 1) % MOD;
            mod_cnt += batch;
            
            auto now = chrono::high_resolution_clock::now();
            if (chrono::duration_cast<chrono::seconds>(now - start).count() >= 1)
                break;
        }
        sink = v;
    }
    cout << "1s add nums " << add_cnt << endl;
    cout << "1s mul nums " << mul_cnt << endl;
    cout << "1s mod&add nums " << mod_cnt << endl;
}
int main() {
    // 1. 测试编译器版本
    #ifdef __GNUC__
        cout << "GCC Version: " << __GNUC__ << "." << __GNUC_MINOR__ << endl;
    #endif
    // 2. 测试 __int128
    #ifdef __SIZEOF_INT128__
        cout << "__int128 is supported" << endl;
    #endif
    test_speed();// 3. 测试速度
    test_time(); // 4. 测试各运算1秒内执行次数
    return 0;
}
