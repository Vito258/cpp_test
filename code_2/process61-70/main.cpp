#include <iostream>
#include <windows.h>
#include <thread>
//chrono 主要用于高精度计时
#include <chrono>
#include <vector>
#include <algorithm>
#include <functional>

namespace apple{
    void print(std::string str){
        std::cout<<"apple: "<<str<<std::endl;
    }
}
namespace banana{
    void print(const char* str){
        std::cout<<"banana: "<<str<<std::endl;
    }
}

static bool finished_flag = false;
void thread_func(){
    std::cout<<"id: "<< std::this_thread::get_id()<<std::endl;
    while(!finished_flag){
       std::cout<<"thread_func is running."<<std::endl;
       std::this_thread::sleep_for(std::chrono::seconds(1));  //睡1秒
    }
}
struct Timer {
    std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<long long, std::ratio<1, 1000000000>>> start_time;
    std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<long long, std::ratio<1, 1000000000>>> end_time;
    Timer(){
        start_time = std::chrono::high_resolution_clock::now();
    }
    ~Timer(){
        end_time = std::chrono::high_resolution_clock::now();
        std::cout<<"Timer: "<<std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count()<<"ms\n";
    }
};
void print_100(){
    Timer timer;
    for(int i=0;i<100;i++){
        std::cout<<i<<std::endl;
    }
}

struct Entity{
    int x , y;
    //返回数组访问形式的方法
    int * GetPosition(){
        return &x;
    }
};
struct Vector2{
    float x , y;
};
struct Vector4{
    union{
        //匿名联合体,这两个struct 的成员共用一个内存空间，k的内存大小等于r+g，所以k.x和r是相同的
        struct{
            float r,g,b,a;
        };
        struct {
            Vector2 k,l;
        };
    };
};

void print_vector2(const Vector2& v){
    std::cout<<"x: "<<v.x<<" y: "<<v.y<<std::endl;
}

class Base{
public:
    Base(){
        std::cout<<"Base 的构造函数被调用"<<std::endl;
    }
    //将父类的析构函数前加virtual修饰符，可以使派生类的析构函数被调用，而且父类的析构函数也会被调用，虚析构函数的覆写更像是叠加作用
    virtual ~Base(){
        std::cout<<"Base 的析构函数被调用"<<std::endl;
    }
};
class Derived : public Base{
public:
    Derived(){
        std::cout<<"Derived 的构造函数被调用"<<std::endl;
    }
    ~Derived(){
        std::cout<<"Derived 的析构函数被调用"<<std::endl;
    }
};
class AnotherBase : public Base{
    AnotherBase(){
        std::cout<<"AnotherBase 的构造函数被调用"<<std::endl;
    }
    ~AnotherBase(){
        std::cout<<"AnotherBase 的析构函数被调用"<<std::endl;
    }
};
//int main()
//{
//    using namespace std::literals::chrono_literals;
//    SetConsoleOutputCP(CP_UTF8);
//    //命名空间
//    const char* str = "Hello World!";
////    using namespace banana;
////    using namespace apple;
////
////     print(str);    //发现使用命名空间后，编译器会自动将banana中的print函数替换掉apple中的print函数，这是因为函数重载的优先级问题，apple中的print 函数的形参是string 类型，需要额外的隐式转换
//
////     apple::print(str);
//
//    //线程
////    std::thread worker(thread_func);// 接收一个函数指针作为参数
////
////    std::cin.get();
////    finished_flag = true;
////    std::cout<<"main id: "<< std::this_thread::get_id()<<std::endl;
////    std::cout<<"Finished."<<std::endl;
////
////    worker.join();
////    std::cin.get();
//
//    //计时
//    //记载现在的时间
////    print_100();
//
//   //多维数组
////   int* a1d = new int [5];
////   int** a2d = new int* [5];   //二维数组
////   int ***a3d = new int** [5]; //三维数组
////   //分配内存
////   for(int i=0;i<5;i++){
////       //为二维数组分配内存,内存的总值为(5^2 * 4)
////       a2d[i] = new int[5];
////       for(int j=0;j<5;i++){
////           //为三维数组分配内存,内存的总值为(5^3 * 4)
////           a3d[i][j] = new int[5];
////       }
////   }
////   delete [] a1d;
////   delete [] a2d;
////   delete [] a3d;
//
//   //测试一下一维数组和二维数组读取数据的速度
////   int* a1d = new int [1000000];
////    int** a2d = new int* [1000];
////    auto start_time = std::chrono::high_resolution_clock::now();
////   for(int i=0;i<1000000;i++){
////       a1d[i] = i;
////   }
////
////    auto end_time_middle = std::chrono::high_resolution_clock::now();
////   for(int i=0;i<1000;i++){
////       a2d[i] = new int[1000];
////       for(int j=0;j<1000;j++){
////           a2d[i][j] = i*j;
////       }
////   }
////   //
//////   auto start_time = std::chrono::high_resolution_clock::now();
//////   for(int i=0;i<1000000;i++){
//////       std::cout<<a1d[i]<<std::endl;
//////   }
//////   auto end_time_middle = std::chrono::high_resolution_clock::now();
//////   for(int i=0;i<1000;i++){
//////       for(int j=0;j<1000;j++){
//////           std::cout<<a2d[i][j]<<std::endl;
//////       }
//////   }
////   auto end_time = std::chrono::high_resolution_clock::now();
////   delete [] a1d;
////   delete [] a2d;
////   std::cout<<"一维数组读取用时："<<std::chrono::duration_cast<std::chrono::milliseconds>(end_time_middle - start_time).count()<<"ms"<<std::endl; //一维数组读取用时：285997ms ,一维数组分配内存用时：3ms
////   std::cout<<"二维数组读取用时："<<std::chrono::duration_cast<std::chrono::milliseconds>(end_time - end_time_middle).count()<<"ms"<<std::endl;  //二维数组读取用时：286374ms，二维数组分配内存用时：4ms
//
//   //C++中的排序
////   std::vector<int> a = {1,3,5,7,9,2,4,6,8,0};
////    //int 类型按照升序排序
////   std::sort(a.begin(),a.end());
////   for(int i=0;i<10;i++){
////       std::cout<<a[i]<<std::endl;
////   }
////   //comp可以传入函数指针，也可以传入lambda表达式
//////   std::sort(a.begin(),a.end(),[](int a,int b){return a>b;});
//////   std::cout<<"lambda表达式排序："<<std::endl;
//////    for(int i=0;i<10;i++){
//////        std::cout<<a[i]<<std::endl;
//////    }
////   std::sort(a.begin(),a.end(),std::greater<int>());
////   std::cout<<"传入函数指针排序："<<std::endl;
////   for(int i=0;i<10;i++){
////        std::cout<<a[i]<<std::endl;
////    }
//
//   //c++中的类型双关，即拥有的这段内存当成不同类型的内存值来看待
//   //1、通过转换内存地址类型，再使用解引用的方式。
//   //这是一个不好的例子,因为强制类型转换会破坏类型安全，int值有有4个字节，强制使用解引用的方式将这个值转换为double类型，会额外读取4个字节的内存赋值给b，导致错误
////   int a = 10;
////   double& b = *(double*)&a;
////   std::cout<<b<<std::endl;
////
////   //2、访问类型,可以通过类型双关的方式将一个类通过数组访问的方式访问类型变量
////   //单独的struct 为空时，它只占一个字节，被赋值时内存大小为值的总内存大小，例如这里就是两个int 值的内存大小为8个字节
////   Entity e = {5,6};
//////   int * position = (int *)&e;
////     int * position = e.GetPosition();
//////   int y = *(int *)(&e + 4);
////   std::cout<<position[0]<<","<<position[1]<<std::endl;
//
//
//   //union-联合体
////   Vector4  v = {1.0f,2.0f,3.0f,4.0f};
////    print_vector2(v.k);
////    print_vector2(v.l);
////    std::cout<<v.r<<v.g<<v.b<<v.a<<std::endl;
////    std::cout<<"---------------------------------"<<std::endl;
////    v.r = 10.0f;
////    print_vector2(v.k);    //x:10, 所以存在映射关系
//
//   //虚析构函数，假如b派生于a，你想把类b引用为类a，当a内存被释放时，那么a的析构函数会被调用，但是b的析构函数不会被调用，所以需要虚析构函数
//
//   //调用Base 和Derived 的构造函数以及Base和Derived 的析构函数
////    {
////        Base* b = new Derived();
////        delete b;
////    }
//
//   //类型转换
//   //1\ C语言风格的转换
//   double a = 5.63;
//   double b = 5.72;
////   double value = (int) a + b;   //10.72
//
//   //C++风格的转换，分为四种方法staic_cast,const_cast,reinterpret_cast,dynamic_cast
//   double value = static_cast<int>(a) + b;  //10.72
//   std::cout<<value<<std::endl;
//
//   //通过dynamic_cast判断派生类数据类型，如果是派生类，则返回派生类指针，否则返回nullptr
//   Derived* d = new Derived();
//   Base* base = d;
//   AnotherBase* ac = dynamic_cast<AnotherBase *> (base);
//   Derived* d2 = dynamic_cast<Derived *> (base);
//   if(!ac){
//       std::cout<<"ac:nullptr"<<std::endl;
//   }
//   if(!d2){
//       std::cout<<"d2:nullptr"<<std::endl;
//   }
//    delete d;
//    delete base;
//   return 0;
//}
