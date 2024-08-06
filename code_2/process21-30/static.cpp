/*
 * static 分为在类中和类外使用
 * 1、类中
 *    表示static 修饰的变量和函数全部同类共享
 * 2、类外
 *    表示static 修饰的变量或者函数在链接时只会在它被“声明的文件”里看到,如果没有static，编译器
 *    就会跨单元链接，如果其他地方有同名的变量可能会报链接错误
 * */
#include <iostream>

using namespace std;
// 全局变量
int var_val = 11;
//static 修饰的变量
static int is_static_val = 22;

//局部作用域中的static
int Function() {
    //静态变量
    //意味着当第一次调用这个函数时i被初始化为1，但是以后程序运行中再调用这个函数时并不会重新声明新的i
    static int i = 1;
    i++;
    return i;
}
