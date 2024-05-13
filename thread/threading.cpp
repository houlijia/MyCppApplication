/**
 * @Author houlijia 
 * @Date   2024-05-13 22:54
 * @Desc
**/
#include "threading.h"
#include <mutex>

mutex mtx;  //����������
int globalvariables = 0;

void task1(){
    for (int i = 0; i < 10000; ++i) {
        lock_guard<mutex> lock(mtx);   //���Ա���  throw return����
        //mtx.lock();   //�̲߳���ȫ�ĵط�������ͬunlock()һ��
        globalvariables++;
        globalvariables--;
        //callfun()  //throw
//        if(1==1){
//            return ;
//        }
        //mtx.unlock();  //����
    }
}

void testfun(void){
    while(true){
        cout<<"Hello world"<<endl;
        __thread_id threadid=this_thread::get_id();   //���߳��ڲ���ȡ�߳�id
        this_thread::sleep_for(chrono::microseconds(50));   //˯�� 50ms
    }
}
void funthreading(void){
    //���߳�
    thread t1(task1);
    thread t2(task1);
    t1.join();
    t2.join();
    cout<<" current values is : "<<globalvariables<<endl;

//    thread thread01(testfun);
//    __thread_id threadid=thread01.get_id();  //��ȡ�߳�ID
//    cout<<"thread01 id is : "<<threadid<<endl;
//    thread01.join();  //�����̺߳�main�̷߳��뿪
//    while (true){
//        cout<<"main \n";
//        this_thread::sleep_for(chrono::microseconds(50));
//    }
}
