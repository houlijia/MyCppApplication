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

mutex mtx1;  //����������
mutex mtx2;  //����������
int globalvariables = 0;
//atomic<int> globalvariables = 0;   //ԭ��

void task1(){
    for (int i = 0; i < 10000; ++i) {
        // RAII  ��Դ��ȡ����ʼ��
        //lock_guard<mutex> lock(mtx);   //���Ա���  throw return����
        mtx1.lock();   //�̲߳���ȫ�ĵط�������ͬunlock()һ��
//        lock(mtx1,mtx2);   //���������������
        globalvariables++;
        globalvariables--;
//        mtx1.unlock();
//        mtx2.unlock();
        //callfun()  //throw
//        if(1==1){
//            return ;
//        }
        mtx1.unlock();  //����
    }
}
void task2(){
    for (int i = 0; i < 10000; ++i) {
        // RAII  ��Դ��ȡ����ʼ��?
        //lock_guard<mutex> lock(mtx);   //���Ա���  throw return������lock_guard������������forѭ�����Զ����
        //mtx1.lock();   //�̲߳���ȫ�ĵط�������ͬunlock()һ��
        //lock(mtx1,mtx2);   //���������������
//        unique_lock<mutex> lock3(mtx1);   //unique_lock���Ƚ���������ʱ����
//        lock3.unlock();
        globalvariables++;
        globalvariables--;
        //mtx1.unlock();
//        mtx2.unlock();
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

void testthread01(){
    cout<<"��ǰ���߳�IDΪ��"<<get_id()<<endl;
    cout<<"��ʼ�������߳�"<<endl;
    for (int i = 1; i < 6; ++i) {
        cout<<"���������߳��� "<<i<<endl;
        sleep_for(chrono::seconds(1));   //sleep��ʾ�ͷ�CPU��Դ
    }
    cout<<"���߳��˳�"<<endl;
}
void funthreading(void){
//    //���߳�
//    thread t1(task1);   //thread ���յ��Ǹ�����ָ�루û��Բ���Ż������ƵĶ�����
//    thread t2(task2);   //t2��һ���̵߳Ķ���
//    t1.join();    //join�ı����ǵȴ�����̼߳������
//    t2.join();
//    cout<<" current values is : "<<globalvariables<<endl;
//
//    thread thread01(testfun);
//    __thread_id threadid=thread01.get_id();  //��ȡ�߳�ID

//    cout<<"thread01 id is : "<<threadid<<endl;
//    thread01.join();  //�����̺߳�main�̷߳��뿪
//    while (true){
//        cout<<"main \n";
//        this_thread::sleep_for(chrono::microseconds(50));
//    }

    // 0529 �߳�ѧϰ
    //�÷�1
//    cout<<"��ǰmain�߳�IDΪ��"<<get_id()<<endl;
//    thread testthread011(testthread01);
//    cout<<"����ʼ���ȴ����߳�"<<endl;
//    testthread011.join();
//    cout<<"�ȴ����߳̽���"<<endl;

    //�÷�2
//    {
//        thread testthread011(testthread01);   //�ᱨ��
//    }
    //�÷�3
//    {
//        thread testthread011(testthread01);
//        testthread011.join();    //�������̣߳��ȴ����߳��˳�
//    }

    // �÷�4
    {
        thread testthread011(testthread01);
         //���߳������̷߳��룬�������ػ��߳�
        // �ӣ����߳��˳������̲߳�һ���˳�
        // �������߳��з��������̵߳ı�������崵������߳�ֻ�������̱߳������Դ�ͺ�
        testthread011.detach();
    }

    cout<<"ִ����ϡ�������"<<endl;
}
