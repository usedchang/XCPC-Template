#include<bits/stdc++.h>
using namespace std;
int main(){
    //一直循环，直到找到不一样的数据
    while (1) {
        system("data.exe > data.txt");
        system("bf.exe < data.txt>bf.txt");
        system("test.exe < data.txt > test.txt");
        if (system("fc test.txt bf.txt")) break;                          
        //不一样就跳出循环
    }//当 fc 返回 1 时，说明这时数据不一样
    return 0;
}
