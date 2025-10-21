/**
 * @Author houlijia 
 * @Date   2024-05-24 23:13
 * @Desc
**/
#include "testpointer.h"
#include <string.h>
void testpointer(){
    void* ptrr= nullptr;    //声明一个无效指针
    int* ptr=0;    //声明一个无效指针
    int var =10;
    ptr = &var;
    *ptr=100;

    char* buffer =new char[8];
    memset(buffer,0,8);
    char** ptr02=&buffer;

    //delete[] buffer;
    int var02=11;
}