/**
 * @Author houlijia 
 * @Date   2024-05-13 22:54
 * @Desc
**/
#include "threading.h"
#include <mutex>

mutex mtx;  //创建互斥量
int globalvariables = 0;

void task1(){
    for (int i = 0; i < 10000; ++i) {
        lock_guard<mutex> lock(mtx);   //可以避免  throw return场景
        //mtx.lock();   //线程不安全的地方枷锁、同unlock()一起
        globalvariables++;
        globalvariables--;
        //callfun()  //throw
//        if(1==1){
//            return ;
//        }
        //mtx.unlock();  //解锁
    }
}

void testfun(void){
    while(true){
        cout<<"Hello world"<<endl;
        __thread_id threadid=this_thread::get_id();   //在线程内部获取线程id
        this_thread::sleep_for(chrono::microseconds(50));   //睡眠 50ms
    }
}
void funthreading(void){
    //多线程
    thread t1(task1);
    thread t2(task1);
    t1.join();
    t2.join();
    cout<<" current values is : "<<globalvariables<<endl;

//    thread thread01(testfun);
//    __thread_id threadid=thread01.get_id();  //获取线程ID
//    cout<<"thread01 id is : "<<threadid<<endl;
//    thread01.join();  //将主线程和main线程分离开
//    while (true){
//        cout<<"main \n";
//        this_thread::sleep_for(chrono::microseconds(50));
//    }
}
