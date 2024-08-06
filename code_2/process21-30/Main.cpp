#include <iostream>
#include <windows.h>
#include "Log.h"

using namespace std;

//承接全局变量
extern int var_val;
enum Sesson {
    Spring,
    Summer,
    Autumn,
    Winter
};
//自定义不冲突变量
int is_static_val = 33;

class Prinable {
   virtual std::string GetClassName() = 0;
};

//类中static 修饰的变量
class Entity:Prinable{
public:
    static int x, y;
    float z;
    //构造函数
    /*
     * C++并不能像Java中将类中的基本数据类型初始化，你必须手动初始化
     * */
//    Entity() = delete;  删除构造方法
    Entity() {
        x = 0;
        y = 0;
        z = 0.0f;
        cout << "Created Entity" << endl;
    }

    //析构函数,对象实例被销毁时执行
    ~Entity() {
        cout << "Destroyed Entity" << endl;
    }

    Entity(float zValue) {
        z = zValue;
    }

    //静态方法，其只能访问静态变量
    static void print() {
        cout << "x:" << x << "," << "y:" << y << endl;
    }

    //非静态方法可以访问静态变量
    void printSum() {
        cout << "sum is :" << x + y << endl;
    }

    void printOption() {
        cout << "x:" << x << "," << "y:" << y << "z:" << z << endl;
    }

    void climb(float za) {
        z += za;
    }

    //虚函数，调用函数时生成一张V表，映射基类和子类中的相同函数，多态的实现原理
//    virtual std::string GetName()
//    {
//        return "Entity";
//    }
    //纯虚函数，必须由子类实现
    virtual std::string GetName() = 0;
    std::string GetClassName() override {
        return "Entity";
    }

};

class Player : public Entity {
private:
    std::string m_name;

public:
    string name;

    Player(const std::string &name) : m_name(name) {}

    std::string GetName() override {
        return m_name;
    }

    void printName() {
        cout << "name is :" << name << endl;
    }

    Player() {

    }
    std::string GetClassName() override {
        return "Player";
    }
};

int Entity::x;
int Entity::y;

int Function();

void PrintEntity(Entity *entity) {
    cout << entity->GetClassName() << endl;
}

//int main() {
//    SetConsoleOutputCP(CP_UTF8);
//    //对类的操作
//    Log log;
//    log.m_log_level = Log::Log_Error_Level;
//    log.printInfo("hello,world");
//    log.printWarning("hello,world");
//    log.printError("hello,world");
//
//    cout << var_val << endl;      //输出11
//    cout << is_static_val << endl;//输出33
//
////    Entity e1;
////    e1.x = 5;
////    e1.y = 10;
//
////    Entity e2;
////    e2.x = 8;
////    e2.y = 16;
////    Entity::x = 99;
////    Entity::print();
////    Entity::print();
//
//    cout << "===============================" << endl;
//    int f1 = Function();
//    int f2 = Function();
//    int f3 = Function();
//    cout << f1 << f2 << f3 << endl;
//
//    cout << "===============================" << endl;
//    Sesson today = Summer;
//    cout << today << endl;
//
//    cout << "===============================" << endl;
////    Entity e3 = Entity(10.0f);
////    cout<<e3.z<<endl;
////    e3.printOption();
//
//    cout << "===============================" << endl;
//    Player p;
//    p.name = "Tom";
//    p.printName();
//    p.climb(12);
//    p.printOption();
//
//    cout << "===============================" << endl;
//    //多态
////    Entity * e4 = new Entity();
//    Player *p1 = new Player("Vito");
//    Entity *entity = p1;
////    PrintEntity(e4);
//    PrintEntity(p1);
//    p1->printName();
//    PrintEntity(entity);
//    PrintEntity(new Player());
//    return 0;
//}
