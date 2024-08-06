
#include <iostream>
#include <array>
#include <string>
#include <stdlib.h>
#include <cstring>

using namespace std;
using namespace string_literals;
class Examble
{
public:
    int x;
    Examble()
    {
        cout<<"Examble is already!"<<endl;
    }
    Examble(int num)
       :x(num)
    {
        cout<<"Examble is already with"<<x<<endl;
    }
};
class Student
{
private:
    string m_Name;
    Examble m_examble;
public:
    int x, y;
    mutable  int z;
    Student()
       :m_Name("UnKnown"), x(0), y(0), z(0), m_examble(8)  //初始化成员列表
    {
//       x = 0;                也可以这样初始化
//        m_examble = Examble(8); 类实例以这种方式初始化时，Examble 会被初始化两次
    }
    Student(const string & name)
          :m_Name(name)
    {
    }
    int Get_X() const
    {
        z = 20;
        return x;
    }
    string Get_Name() const
    {
        return m_Name;
    }

};
void Set_Student(const Student* p)
{
   cout<<p->Get_X()<<endl;   //get_x() 方法必须有const 关键字
}
//int main() {
//    //array
////  int arr[5];
////  for (int i = 0; i<5; i++){
////      arr[i] = i;
////  }
////  int *p = arr;
////  cout<<*((char*)p+8)<<endl;
////在堆上创建数组
////    const int count = 10;
////    int *arr_heap = new int[count];
////    delete []arr_heap;
////使用c++库中的array,它可以返回容量大小和进行边界检查
////    std::array<int, 5> arr;
////   char * str =  "Vit\0o258\0";
//////   str[2] = "i";  不能操作，因为指针是只读的，改成数组可以实现
////   wchar_t * str2 = L"Vito258"; //宽字符
////   const char16_t * str3 = u"Vito258";
////   const char32_t * str4 = U"Vito258";
////
////   u32string str5 = U"Vito258"s + U"Vito258";  //这里的s是一个函数，一般字符串是指针常量，使用s转为string类型
////   const char* str6 = R"(Line
////                         Line2,
////                         Line3
////                        )";    //使用R函数简单编辑多行字符串而不是使用多个\n
////   cout<< strlen(str)<<endl;
////   cout<<str6<<endl;
//
//
//    //const 的用法
//    int val_1 = 10;
//    int val_2 = 20;
//    int val_3 = 30;
//    /*
//     * 以下三段代码前两行是等价的，代表指针指向的值不能改变，但是指针本身是可以改变的-常量指针
//     * 第三行代码代表指针的指向不能改变，但指针指向的值可以改变 - 指针常量
//     * 第四行代表既不能也不能
//     * */
//    const int * a = new int(10);
//    int const * b = new int(10);
//    int * const c = new int(10);
//    const int * const d = new int(10);
//    a = &val_1;
//    val_1 = 100;  //这样可以改变
////    *a = 100;    这样不能改变
//
//    *c= 300;
////    cout<<*a<<endl;
////    cout<<*c<<endl;
//    //在类中的方法 例如 int Get() const {} 代表不修改类成员变量的方法，只返回值
//    //在只读取数据的函数中一定不要忘记const，在有常量引用或者常量指针的形参的调用只读函数必须有const
//
//    //mutable 关键字的使用
//    // 但是我们有时候想在const 函数中修改一个参数，应该怎么办？ 将要修改的参数前面加上mutable 关键字，使其在const函数中也可以被修改
//    //mutable lambda 中，mutable 是一个关键字，代表在lambda中可以修改外部变量的值
//    /*
//     * 方括号中传入&代表传入所有值的引用，传入=代表传入所有值的复制值
//     * */
//    int y = 10;
//    auto get_Y = [&]()
//    {
//        y++;
//        return y;
//    };
////    cout<<get_Y()<<endl;
////    cout<<y<<endl;
//
//    //C++中初始化成员列表
//    Student s1;
////    Student s2("Carlo");
////    Student *s3 = new Student("Vito258");
////
////    cout<<s3->Get_Name()<<endl;
//
//    //三元运算符
//    int fu_1 = 7;
//    string print_val = fu_1 > 5 ? fu_1 >= 10 ? "fu_1 >= 10" : " 5 < fu_1 < 10": "fu_1 < 5";
//    cout<< print_val<<endl;
//    return 0;
//};
