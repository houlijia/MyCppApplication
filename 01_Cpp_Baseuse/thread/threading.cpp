/**
 * @Author houlijia 
 * @Date   2024-05-13 22:54
 * @Desc
**/
#include "threading.h"
#include <thread>
#include <mutex>
#include <atomic>
using namespace std::this_thread;

mutex mtx1;  //创建互斥量
mutex mtx2;  //创建互斥量
int globalvariables = 0;
//atomic<int> globalvariables = 0;   //原子

void task1(){
    for (int i = 0; i < 10000; ++i) {
        // RAII  资源获取及初始化
        //lock_guard<mutex> lock(mtx);   //可以避免  throw return场景
        mtx1.lock();   //线程不安全的地方枷锁、同unlock()一起
//        lock(mtx1,mtx2);   //给多个互斥量上锁
        globalvariables++;
        globalvariables--;
//        mtx1.unlock();
//        mtx2.unlock();
        //callfun()  //throw
//        if(1==1){
//            return ;
//        }
        mtx1.unlock();  //解锁
    }
}
void task2(){
    for (int i = 0; i < 10000; ++i) {
        // RAII  资源获取及初始化?
        //lock_guard<mutex> lock(mtx);   //可以避免  throw return场景、lock_guard作用域在整个for循环、自动结果
        //mtx1.lock();   //线程不安全的地方枷锁、同unlock()一起
        //lock(mtx1,mtx2);   //给多个互斥量上锁
//        unique_lock<mutex> lock3(mtx1);   //unique_lock锁比较灵活，可以随时解锁
//        lock3.unlock();
        globalvariables++;
        globalvariables--;
        //mtx1.unlock();
//        mtx2.unlock();
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

void testthread01(){
    cout<<"当前子线程ID为："<<get_id()<<endl;
    cout<<"开始启动子线程"<<endl;
    for (int i = 1; i < 6; ++i) {
        cout<<"现在在子线程里 "<<i<<endl;
        sleep_for(chrono::seconds(1));   //sleep表示释放CPU资源
    }
    cout<<"子线程退出"<<endl;
}
void funthreading(void){
//    //多线程
//    thread t1(task1);   //thread 接收的是个函数指针（没有圆括号或者类似的东西）
//    thread t2(task2);   //t2是一个线程的对象
//    t1.join();    //join的本质是等待这个线程加入进来
//    t2.join();
//    cout<<" current values is : "<<globalvariables<<endl;
//
//    thread thread01(testfun);
//    __thread_id threadid=thread01.get_id();  //获取线程ID

//    cout<<"thread01 id is : "<<threadid<<endl;
//    thread01.join();  //将主线程和main线程分离开
//    while (true){
//        cout<<"main \n";
//        this_thread::sleep_for(chrono::microseconds(50));
//    }

    // 0529 线程学习
    //用法1
//    cout<<"当前main线程ID为："<<get_id()<<endl;
//    thread testthread011(testthread01);
//    cout<<"【开始】等待子线程"<<endl;
//    testthread011.join();
//    cout<<"等待子线程结束"<<endl;

    //用法2
//    {
//        thread testthread011(testthread01);   //会报错
//    }
    //用法3
//    {
//        thread testthread011(testthread01);
//        testthread011.join();    //阻塞主线程，等待子线程退出
//    }

    // 用法4
    {
        thread testthread011(testthread01);
         //子线程与主线程分离，创建了守护线程
        // 坑：主线程退出后子线程不一定退出
        // 若是子线程中访问了主线程的变量，会宕掉，子线程只访问子线程本身的资源就好
        testthread011.detach();
    }

    cout<<"执行完毕。。。。"<<endl;
}
