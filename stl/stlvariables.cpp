/**
 * @Author houlijia 
 * @Date   2024-05-14 22:22
 * @Desc
**/
#include "stlvariables.h"
vector<int> testvector(){
    // ����һ�������洢 int
    int n=10;
    vector<int> vecvar;              // vector��̬���飬֧�ֿ����������
    vector<int> v01(n);              //����һ������Ϊn�����飬��̬���壬��ָ����ֵĬ�ϳ�ֵΪ0
    vector<double> v02(n, 0);     //���е�Ԫ�ؾ�Ϊ0
    vector<int> v03({1, 2, 3, 4, 5});// ����a�������Ԫ��
    vector<int> v04({2,3,4,5,6});
    vector<int> v05 = {1, 2, 3, 4, 5};  //
    vector<int> v06 = vector<int>({1, 2, 3, 4, 5});
    //ע�⣺ָ�����鳤��֮��ָ�����Ⱥ��������൱�������������ˣ�
    //vector<node>   v03;               //node�ǽṹ������
    int vecvarsize=vecvar.size();
    cout<<"vecvar ��СΪ�� "<<vecvarsize<<endl;
    for (int i = 1; i < 5; ++i) {
        vecvar.push_back(i);
    }
    for (int i = 5; i < 11; ++i) {
        vecvar.push_back(i);
    }
    cout<<"����ֵ֮��� vecvar ��СΪ�� "<<vecvar.size()<<endl;
    for (int i = 0; i < vecvar.size(); ++i) {   //1������ vector �е�ֵ
        cout<<"������ʽһ: vecvar["<<i<<"]= "<<vecvar[i]<<endl;
    }
    cout<<endl;
    //vecvar.erase(2,6);   //ɾ��[first,last)������Ԫ��       ----xxxx
    for (auto i:vecvar) {
        cout<<"������ʽ��: vecvar["<<i<<"]= "<<i<<endl;
    }
    cout<<"vecvar �ĵ�һ��Ԫ��Ϊ��"<<vecvar.front()<<endl;
    cout<<"vecvar �����һ��Ԫ��Ϊ��"<<vecvar.back()<<endl;
    vecvar.pop_back();
    cout<<"ɾ���� vecvar ��СΪ�� "<<vecvar.size()<<endl;
    vecvar.clear();
    cout<<"��� vecvar Ԫ�ظ����� ��СΪ�� "<<vecvar.size()<<endl;
    int n02=3;
    vecvar.resize(n02,12);
    for (auto i:vecvar) {
        cout<<"�ı��С��Ԫ������: vecvar["<<i<<"]= "<<i<<endl;
    }
    auto address= *(vecvar.begin());
    cout << "vecvar[0]��ַΪ��" << &(vecvar[0]) <<" == " << &*(vecvar.begin()) <<endl;
    int aa=10;
    return vecvar;
}
void teststlvar(){
    testvector();
}