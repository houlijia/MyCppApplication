#include <iostream>
#include <thread>
#include "thread/threading.h"

using namespace std;
int main() {
    //���߳�
    thread thread01(funthreading);
    __thread_id threadid=thread01.get_id();  //��ȡ�߳�ID
    cout<<"thread01 id is : "<<threadid<<endl;
    //thread01.join();  //�����̺߳�main�̷߳��뿪
//    while (true){
//        cout<<"main \n";
//        this_thread::sleep_for(chrono::microseconds(50));
//    }
    return 0;
}
