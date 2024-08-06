#include <iostream>
#include <windows.h>
#include <utility>
#include <functional>
//include 支持动态和静态链接
//静态链接时将dll文件放在项目目录下，动态链接时将dll文件放在系统目录下
#include <GLFW/glfw3.h>

//#include "../Engine/Engine.h"通过路径方式导入，不推荐
#include "Engine.h"
#include <functional>
#include<algorithm>
//C++中的宏，其作用类似于模板，但是模板作用于编译阶段，宏作用于编译的预处理阶段
#define WAIT std::cin.get()

//如果是#ifdef DEBUG，那么判断的不是bool值的true/false ，而是判断值是否存在，值存在且为0也会认为true
#if DEBUG == 1
    #define Log(x) std::cout << x << std::endl
#else
    #define Log(x) std::cout << "现在处于非Debug构建模式下..." << std::endl
#endif
//在宏中换行时需要使用 \转义
#define MAIN int main() \
{                       \
std::cin.get();\
}
using namespace std;
/*
 * 返回多个值的方法
 * 1、创建一个结构体或类，将多个值放入其中
 * 2、使用元组或者pair
 * 3、创建一个数组或者vector ，区别在于array是在栈上新建对象，所以速度会比较快一些
 * 4、需要传参数时使用指针或者引用，在调用方法处新建参数，然后调用void将参数传入，然后在方法中修改指针或者引用的值
 * */
// tuple
std::tuple<std::string,int, int> get_tuple()
{
  string str = "hello world!";
  int width = 0;
  int height = 0;
  return std::make_tuple(str,width,height);
}
// pair，最多只能放两个参数
std::pair<std::string,int> get_pair()
{
    string str = "hello world!";
    int width = 0;
    return std::make_pair(str,width);
}
//使用structure 结构体包装参数
struct Params
{
    string str;
    int width;
    int height;
};

//template,作用类似与泛型
//1、使用模板构造函数
template<typename T>
void PrintValue(T value)
{
    cout<<"value: "<<value<<endl;
}
//2、使用模板构造类
template<typename T,int N>
class Array
{
    int m_Array[N];
    T m_Name;
public:
    int GetSize() const{
        return N;
    }
    void SetName(T name)
    {
        m_Name = name;
    }
    T GetName() const{
        return m_Name;
    }
};
struct Vector{
    int x,y,z;
    Vector(int x,int y,int z):x(x),y(y),z(z){}
};
char* GetName()
{
    return "Vito";
}

template<typename T,unsigned long long size>
void Print_Array(std::array<T,size>& array)
{
   for(int i = 0;i<array.size();i++){
       std::cout<<array[i]<<std::endl;
   }
}
void Print_Hello(string& str){
    std::cout<<"Hello World! value: "<< str <<endl;
}

// 函数指针的使用场景
void Print_Vector(std::vector<int>& vector,const std::function<void(int)> &func)
{
   for(int i = 0;i<vector.size();i++)
       func(vector.at(i));
}
//int main()
//{
//     SetConsoleOutputCP(CP_UTF8);
//
////     int a = glfwInit();
////     cout<<a<<endl;
////     engine::PrintMessage();
//
////     std::tuple <std::string,int, int> t = get_tuple();
////     std::cout << std::get<0>(t) << std::endl;
////     std::cout << std::get<1>(t) << std::endl;
//
////     std::pair <std::string,int> p = get_pair();
////     std::cout<<p.first<<std::endl;
////     std::cout<<p.second<<std::endl;
////
////     Params param = {p.first,p.second,0};
////     cout<<param.height<<endl;
//
////    PrintValue("hello world");
////    PrintValue(1);
////    PrintValue(1.0f);
////     Array<std::string,5> array1;
////     cout<<array1.GetSize()<<endl;
////     array1.SetName("array1");
////     array1.SetName(1);         报错，因为创建array1时是string类型，所以不能赋值int类型
////     cout<<array1.GetName()<<endl;
//
//     //在堆上创建对象和在栈上创建对象的区别，堆上创建的对象需要手动释放，唯一需要在堆上创建对象的原因就是该对象不能在栈上创建，比如需要它存在的声明周期创建其的作用域要长
////     从栈上创建
////     Vector v1(1,2,3);
////     //从堆上创建
////     Vector* v2 = new Vector(4,5,6);
////     cout<<v2->x<<endl;
////     delete v2;
//
//     //宏
////     Log("hello world");
//
////     auto 自推断类型关键字
////     auto name = GetName(); 这种情况下不存在隐式转换，所以name的类型是char*，无法使用string类型的.size()方法，由此可见随意使用auto关键字，会带来意想不到的错误
////      std::string name = GetName();
////      long size = name.size();
//////     使用auto的情景，一般类型比较长或是比较复杂时
////    std::vector<std::string> strs = {"apple","pear"};
////    for(std::vector<std::string>::iterator it = strs.begin();it!=strs.end();it++){
////        std::cout<<*it<<std::endl;
////    }
//
////    for(auto it = strs.begin();it!=strs.end();it++){
////        std::cout<<*it<<std::endl;
////    }
//
//    //c++中的静态数组std::array,其大小和构造函数的参数一致，并且不能改变大小
////    std::array<int,5> myArray = {1,2,3,4,5};
////    Print_Array(myArray);
////    myArray[5] = 6;    虽然编译器不会报错，运行也不会报错，但实际上myArray[5] = 6; 是一个无效的操作，因为myArray的大小是5，所以越界了，如果你在迭代调试的环境下，编译器会提醒你
//
//   //函数指针
////   void(*func)(string& str);
////   string s = "vito";
////   func = Print_Hello;
////   func(s);
//
//    std::vector<int> values = {1,2,3,4,5};
////    Print_Vector(values,PrintValue);
//
//    //[]捕获方式
//    //函数指针搭配lambda
////    string name = "vito";
////    auto lambda = [name](int value){std::cout<<"name: "<<name<<"value: "<<value<<std::endl;};
////    Print_Vector(values,lambda);
//
//     // find_if 函数在范围内返回满足特定条件的第一个元素,如果没有找到则返回end()迭代器。
//     // 这里的pred 是谓词函数，可以是函数指针，函数对象，lambda表达式等
////     auto it =  std::find_if(values.begin(),values.end(),[](int value){return value > 3;});
////     cout<<"找到的第一个大于3的值为："<<*it<<endl;     //这里的it不是指针而是1个迭代器，*it用来获取迭代器it所指向的元素的实际值
//}
//MAIN
