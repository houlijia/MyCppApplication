/**
 * @Author houlijia 
 * @Date   2024-05-15 23:48
 * @Desc
**/

using namespace std;
#include "stackandhap.h"
struct struct1{
    float x,y,z;
    struct1():x(10),y(11),z(12){};   //默认初始值
};

void stackandhap(){   //栈和堆的区别
    int value01=10; // 将会在栈上分配内存 栈地址连续分配
    int array[5]; // 将会在栈上分配内存
    struct1 st01;   //在栈中一旦作用域结束了，在栈中分配的所有内存都会被弹出，释放内存没有开销

    int* hvalue =new int;  //new 关键字在堆上分配内存
    *hvalue=5;             //对hvalue做解引用（逆向引用）
    int* hvarray =new int[5];
    struct1* st02=new struct1();  //括号可加可不加
    delete hvalue;
    delete hvarray;
    delete st02;     //手动释放内存、也就是生命周期比作用域的生命周期时间长    cache miss 问题

    int aa=11;
}