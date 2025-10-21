/**
 * @Author houlijia 
 * @Date   2024-05-14 22:22
 * @Desc
**/
#include "stlvariables.h"
struct struct01{
    float x,y,z;
    struct01(float x,float y,float z):x(x),y(y),z(z){}   //struct01的构造函数
    struct01(const struct01& struct01):x(struct01.x),y(struct01.y),z(struct01.z){
        cout<<"copy 构造函数"<<endl;
    }
};
vector<int> testvector(){
    // 创建一个向量存储 int
    int n=10;
    vector<struct01> vectstruct;
    //cout<<"vectstruct 的第二个元素为："<< &*vectstruct.begin()<< endl;
    vectstruct.reserve(3);
    vectstruct.emplace_back(1,2,3);
    vectstruct.emplace_back(4,5,6);
    vectstruct.emplace_back(7,8,9);   //优化复制过程，将push_back改成emplace_back
    //vectstruct.push_back({1,2,3});
//    vectstruct.push_back({2,3,4});
//    vectstruct.push_back({3,4,5});
    cout<<"vectstruct 的第二个元素为："<< &*vectstruct.begin()<< endl;
    //vectstruct.erase(vectstruct.begin()+1);       //删除第二个值
    //vectstruct.clear();              //将vectstruct清除

    vector<int> vecvar;              // vector动态数组，支持快速随机访问
    vector<int> v01(n);              //定义一个长度为n的数组，动态定义，不指定初值默认初值为0
    vector<double> v02(n, 0);     //所有的元素均为0
    vector<int> v03({1, 2, 3, 4, 5});// 数组a中有五个元素
    vector<int> v04({2,3,4,5,6});
    vector<int> v05 = {1, 2, 3, 4, 5};  //
    vector<int> v06 = vector<int>({1, 2, 3, 4, 5});
    //注意：指定数组长度之后（指定长度后的数组就相当于正常的数组了）
    //vector<node>   v03;               //node是结构体类型
    int vecvarsize=vecvar.size();
    cout<<"vecvar 大小为： "<<vecvarsize<<endl;
    for (int i = 1; i < 5; ++i) {
        vecvar.push_back(i);
    }
    for (int i = 5; i < 11; ++i) {
        vecvar.push_back(i);
    }
    cout<<"加入值之后的 vecvar 大小为： "<<vecvar.size()<<endl;
    for (int i = 0; i < vecvar.size(); ++i) {   //1、遍历 vector 中的值
        cout<<"遍历方式一: vecvar["<<i<<"]= "<<vecvar[i]<<endl;
    }
    cout<<endl;
    //vecvar.erase(2,6);   //删除[first,last)的所有元素       ----xxxx
    for (auto i:vecvar) {
        cout<<"遍历方式二: vecvar["<<i<<"]= "<<i<<endl;
    }
    cout<<"vecvar 的第一个元素为："<<vecvar.front()<<endl;
    cout<<"vecvar 的最后一个元素为："<<vecvar.back()<<endl;
    vecvar.pop_back();
    cout<<"删除后 vecvar 大小为： "<<vecvar.size()<<endl;
    vecvar.clear();
    cout<<"清除 vecvar 元素个数后 大小为： "<<vecvar.size()<<endl;
    int n02=3;
    vecvar.resize(n02,12);
    for (auto& i:vecvar) {    //是将vecvar拷贝至for循环中，加上&，避免拷贝，是引用
        cout<<"改变大小后元素内容: vecvar["<<i<<"]= "<<i<<endl;
    }
    auto address= *(vecvar.begin());
    cout << "vecvar[0]地址为：" << &(vecvar[0]) <<" == " << &*(vecvar.begin()) <<endl;
    int aa=10;
    return vecvar;
}

void teststlvar(){
    testvector();
}