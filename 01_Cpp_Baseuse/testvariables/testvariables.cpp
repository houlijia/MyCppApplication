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
    double d01=3.123456789101121314;     //ռ8���ֽ�/64λ
    float f01=3.12345678;      //ռ4���ֽ�/32λ
    float *f02;      //ռ4���ֽ�/32λ
    bool b01= true;
    void *v01;  //��ʾ v01����ָ���κα�����ָ;
   // v01=b01;
    //char�ǰ�λ�ַ����ͣ�����ܰ���256���ַ������������ַ������������ַ���Ŀ����256����char�Ͳ��ܱ�ʾ��
    //��������һ��Ϊ16����32λ����ͬ��C/C++���в�ͬ�Ĺ涨����֮��wchar_t���ܱ�ʾ���ַ�ԶԶ����char���͡�
    wchar_t wc01[]=L"Addfffgggghfddwwtgcdgjiqidbfhucnskhrfmbkgawgiwgfgbasfgbakljwbgilwbgjkawbgawbgkjasbgfkjakkkkwbgkfljjawgb";
    string s01="hello string";
    //string s02=NULL;
    //string s02=0;  ����ʹ��

    char x = 'x';
    // ����
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