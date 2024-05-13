/**
 * @Author houlijia 
 * @Date   2024-05-13 22:54
 * @Desc
**/
#include "threading.h"
#include <mutex>

mutex mtx1;  //����������
mutex mtx2;  //����������
int globalvariables = 0;

void task1(){
    for (int i = 0; i < 10000; ++i) {
        // RAII  ��Դ��ȡ����ʼ��
        //lock_guard<mutex> lock(mtx);   //���Ա���  throw return����
        //mtx.lock();   //�̲߳���ȫ�ĵط�������ͬunlock()һ��
        lock(mtx1,mtx2);   //���������������
        globalvariables++;
        globalvariables--;
        mtx1.unlock();
        mtx2.unlock();
        //callfun()  //throw
//        if(1==1){
//            return ;
//        }
        //mtx.unlock();  //����
    }
}
void task2(){
    for (int i = 0; i < 10000; ++i) {
        // RAII  ��Դ��ȡ����ʼ��
        //lock_guard<mutex> lock(mtx);   //���Ա���  throw return������lock_guard������������forѭ�����Զ����
        //mtx.lock();   //�̲߳���ȫ�ĵط�������ͬunlock()һ��
        //lock(mtx1,mtx2);   //���������������
        unique_lock<mutex> lock3(mtx1);   //unique_lock���Ƚ���������ʱ����
        lock3.unlock();
        globalvariables++;
        globalvariables--;
        mtx1.unlock();
        mtx2.unlock();
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
    thread t2(task2);
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
