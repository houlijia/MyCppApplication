/**
 * @Author houlijia 
 * @Date   2024-05-14 22:22
 * @Desc
**/
#include "stlvariables.h"
struct struct01{
    float x,y,z;
    struct01(float x,float y,float z):x(x),y(y),z(z){}   //struct01�Ĺ��캯��
    struct01(const struct01& struct01):x(struct01.x),y(struct01.y),z(struct01.z){
        cout<<"copy ���캯��"<<endl;
    }
};
vector<int> testvector(){
    // ����һ�������洢 int
    int n=10;
    vector<struct01> vectstruct;
    //cout<<"vectstruct �ĵڶ���Ԫ��Ϊ��"<< &*vectstruct.begin()<< endl;
    vectstruct.reserve(3);
    vectstruct.emplace_back(1,2,3);
    vectstruct.emplace_back(4,5,6);
    vectstruct.emplace_back(7,8,9);   //�Ż����ƹ��̣���push_back�ĳ�emplace_back
    //vectstruct.push_back({1,2,3});
//    vectstruct.push_back({2,3,4});
//    vectstruct.push_back({3,4,5});
    cout<<"vectstruct �ĵڶ���Ԫ��Ϊ��"<< &*vectstruct.begin()<< endl;
    //vectstruct.erase(vectstruct.begin()+1);       //ɾ���ڶ���ֵ
    //vectstruct.clear();              //��vectstruct���

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
    for (auto& i:vecvar) {    //�ǽ�vecvar������forѭ���У�����&�����⿽����������
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