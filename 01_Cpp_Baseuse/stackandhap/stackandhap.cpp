/**
 * @Author houlijia 
 * @Date   2024-05-15 23:48
 * @Desc
**/

using namespace std;
#include "stackandhap.h"
struct struct1{
    float x,y,z;
    struct1():x(10),y(11),z(12){};   //Ĭ�ϳ�ʼֵ
};

void stackandhap(){   //ջ�Ͷѵ�����
    int value01=10; // ������ջ�Ϸ����ڴ� ջ��ַ��������
    int array[5]; // ������ջ�Ϸ����ڴ�
    struct1 st01;   //��ջ��һ������������ˣ���ջ�з���������ڴ涼�ᱻ�������ͷ��ڴ�û�п���

    int* hvalue =new int;  //new �ؼ����ڶ��Ϸ����ڴ�
    *hvalue=5;             //��hvalue�������ã��������ã�
    int* hvarray =new int[5];
    struct1* st02=new struct1();  //���ſɼӿɲ���
    delete hvalue;
    delete hvarray;
    delete st02;     //�ֶ��ͷ��ڴ桢Ҳ�����������ڱ����������������ʱ�䳤    cache miss ����

    int aa=11;
}