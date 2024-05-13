#include <iostream>
#include <thread>
#include "thread/threading.h"

using namespace std;
int main() {
    //多线程
    thread thread01(funthreading);
    __thread_id threadid=thread01.get_id();  //获取线程ID
    cout<<"thread01 id is : "<<threadid<<endl;
    //thread01.join();  //将主线程和main线程分离开
//    while (true){
//        cout<<"main \n";
//        this_thread::sleep_for(chrono::microseconds(50));
//    }
    return 0;
}
