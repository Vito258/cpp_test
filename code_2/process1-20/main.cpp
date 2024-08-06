// 为什么#include 后面有<>和“”两种，""可用于任何路径，<>用于编译器路径
#include <iostream>
#include <windows.h>

using namespace std;

//C++中的类
class Player {
public:
    int x;
    int y;
    int speed = 1;
    void move(int xa,int ya)
    {
       x += xa*speed;
       y += ya*speed;
    }
};

//int main() {
//    SetConsoleOutputCP(CP_UTF8);
////    Log("hello,world");
////    init_log();
////    const char *p = "hello";
//
//    //判断语句新增
//    //可以直接在判断语句中写指针，根据指针是否是nullptr（空指针）
//    const char *p = nullptr;
//    if (p) {
//        cout << "p的值为：" << p << endl;
//        cout << "*p的值为：" << *p << endl;
//    } else {
//        cout << "p is nullptr" << endl;
//    }
//
//    //循环语句新增
//    int i = 0;
//    bool condition = true;
//    for (; condition;) {
//        cout << "执行第" << i << "次" << endl;
//        i++;
//        if (!(i < 5))
//            condition = false;
//    }
//    cout << "---------------------------------------" << endl;
//    //指针新增
//    //使用new 在堆上申请内存时，使用memset()方法在申请的内存上填值
//    char *str_p = new char[4];
//    memset(str_p, 0, 4);
//    //双指针，储存指针变量的内存地址
//    char **str_p2 = &str_p;
//    cout << str_p << endl;
//    cout << str_p2 << endl;
//    delete[] str_p;
//    cout << "---------------------------------------" << endl;
//    //C++中类与结构体的区别，struct 中的变量默认可见性都是public，而class中都是private，仅此而已
//    /*
//     * 由结构体去继承类时有些编译器可能会发出警告，但仍然可以运行
//     * 如果只是想表示一些数据使用结构体，如果想要一个完整功能的类那就用class，只是规范问题
//     * */
//    Player player1 ;
//    player1.x = 20;
//    player1.y = 30;
//    cout << player1.x << "," << player1.y<<endl;
//    player1.move(20,10);
//    cout << player1.x << "," << player1.y<<endl;
//    return 0;
//}
