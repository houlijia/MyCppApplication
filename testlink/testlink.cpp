/**
 * @Author houlijia 
 * @Date   2024-05-23 23:48
 * @Desc
**/
#include "testlink.h"

 void Log(const  char  *Message);

static  int Multiply(int a,int b){   //����static ��ָ���Multiplyֻ������ļ���ʹ��
    Log("Multiply");
    return a+b;
}

void testlink(){
    cout<<Multiply(4,5)<<endl;
}