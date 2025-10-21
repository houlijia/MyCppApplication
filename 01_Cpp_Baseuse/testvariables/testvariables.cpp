/**
 * @Author houlijia 
 * @Date   2024-06-01 21:39
 * @Desc
**/

#include "testvariables.h"
#include <string>

int gi01=111;

void testvariables(){
    int i01=10;
    int i02=20;
    int *i03;
    double d01=3.123456789101121314;     //占8个字节/64位
    float f01=3.12345678;      //占4个字节/32位
    float *f02;      //占4个字节/32位
    bool b01= true;
    void *v01;  //表示 v01可以指向任何变量的指;
   // v01=b01;
    //char是八位字符类型，最多能包含256中字符，许多的外文字符集所包含的字符数目超过256个，char型不能表示。
    //数据类型一般为16或者32位，不同的C/C++库有不同的规定。总之：wchar_t所能表示的字符远远多于char类型。
    wchar_t wc01[]=L"Addfffgggghfddwwtgcdgjiqidbfhucnskhrfmbkgawgiwgfgbasfgbakljwbgilwbgjkawbgawbgkjasbgfkjakkkkwbgkfljjawgb";
    string s01="hello string";
    //string s02=NULL;
    //string s02=0;  错误使用

    char x = 'x';
    // 数组
    int array01[] = {1, 2, 3, 4, 5};
    double array02[] = {1000.0, 2.0, 3.4, 7.0, 50.0};
    enum color01{
        RED,
        GREEN,
        BLUE
    }backColor = RED, frontColor = GREEN, innerColor = BLUE;
    color01 cr;
    enum color { red, green=5, blue } c;
    c = blue;
};