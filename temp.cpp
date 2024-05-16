/**
 * @Author houlijia 
 * @Date   2024-05-17 00:32
 * @Desc
**/
#include <iostream>
using namespace std;

extern int a, b;
extern int c;
extern float f;

void funlambda(){

    auto sum = [](int lama, int lamb) -> int {
        return a + b;
    };
    cout << sum(2, 3) << endl; // ???? 5
}
int fun04(){
    int a04=10;

}
int fun03(){
    int a03=10;
    fun04();
}
int fun02(){
    int a02=10;
    fun03();
}
int fun01(){
    int a01=10;
    fun02();
    return 0;
}

int main (int aa)
{
    int a, b;
    int c;
    float f;
    a = 10;
    b = 20;
    c = a + b;
    fun01();
    cout << c << endl ;
    f = 70.0/3.0;
    cout << f << endl ;
    return 0;
}
