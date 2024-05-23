/**
 * @Author houlijia 
 * @Date   2024-05-23 23:23
 * @Desc
**/
#include "testclass.h"


class class01{
public:
    double width;
    double height;
    char str='c';
    double set(double hg){
        height=hg;
    }
};
void testclass(void){
    class01 c01;
    c01.set(10);
    char str='q';
}

