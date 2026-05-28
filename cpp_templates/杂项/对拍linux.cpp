#include<bits/stdc++.h>
using namespace std;
int main(){
    //一直循环，直到找到不一样的数据
    while (1) {
        system("./data > data.txt");
        system("./bf < data.txt > bf.txt");
        system("./test < data.txt > test.txt");
        if (system("diff test.txt bf.txt")) break;                          
        //不一样就跳出循环
    }//当 diff 返回非0 时，说明这时数据不一样
    return 0;
}
