/**
 * @Author houlijia 
 * @Date   2024-05-13 22:54
 * @Desc
**/
#include "threading.h"
void funthreading(void){
    while(true){
        cout<<"Hello world"<<endl;
        __thread_id threadid=this_thread::get_id();   //在线程内部获取线程id
        this_thread::sleep_for(chrono::microseconds(50));   //睡眠 50ms
    }
}
