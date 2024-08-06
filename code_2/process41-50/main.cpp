#include <iostream>
#include <windows.h>
#include <memory>
#include <vector>

using namespace std;

class Entity {
private:
    int age;
    string m_Name;
public:
    Entity()
            : age(-1), m_Name("UnKnown") {
        cout << "Entity Created!" << endl;
    }

    //explicit 关键字，该构造函数必须显式调用，不能通过隐式转换
    explicit Entity(int age)
            : age(age), m_Name("UnKnown") {
        cout << "Entity Created with age" << endl;
    }

    Entity(const string &name)
            : m_Name(name), age(-1) {
        cout << "Entity Created with m_Name" << endl;
    }

    Entity(int age, const string &name) : age(age), m_Name(name) {
        cout << "Entity Created with m_Name and age!" << endl;
    }

    ~Entity() {
        cout << "Entity Destroyed!" << endl;
    }

    string getName() const {
        return m_Name;
    }

    int getAge() const {
        return age;
    }
};

void Print_Entity(Entity e) {
    cout << e.getName() << e.getAge() << endl;
}

class Vector {
public:
    int x, y;

    Vector(int x, int y)
            : x(x), y(y) {
        cout << "Vector Created!" << endl;
    }

    //运算符重载
    Vector operator+(const Vector &v) {
        return Vector(x + v.x, y + v.y);
    };

    Vector operator*(const Vector &v) {
        return Vector(x * v.x, y * v.y);
    }

    bool operator==(const Vector &v) const {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vector &v) const {
        return !(*this == v);
    }

    void printXY() {
        cout << "x: " << x << ", y:" << y << endl;
    }
};

//对左移运算符<< 进行重载
//ostream &operator<<(ostream &stream, const Vector &v) {
//    stream << "x: " << v.x << ", y: " << v.y << endl;
//    return stream;
//}

int *createArray() {
    int array[5];
    array[0] = 1;
    return array;
}

//自创建一个作用域指针类
class ScopePtr {
private:
    Entity *ptr;
public:
    ScopePtr(Entity *ptr) : ptr(ptr) {
        cout << "ScopePtr Created!" << endl;
    }

    ~ScopePtr() {
        cout << "ScopePtr Destroyed!" << endl;
        delete ptr;
    }

    Entity *getPtr() {
        return ptr;
    }

    //重载->操作符重载
    Entity *operator->() const {
        return ptr;
    }
};

//自定义String类
class String {
private:
    char *m_buffer;
    int m_size;
public :

    String(const char *string)
            : m_size(strlen(string)), m_buffer(new char[m_size])  //给\0终止符腾出空间
    {
//      for (int i = 0; i < m_size; i++)
//      {
//          m_buffer[i] = x[i];
//      }
        memcpy(m_buffer, string, m_size);  //将字符串拷贝到m_buffer中
//        m_buffer[m_size] = 0;
    }

    //拷贝构造函数,可以进行深拷贝
    String(const String &other)
            : m_size(other.m_size), m_buffer(new char[other.m_size]) {
        cout << "拷贝构造函数执行" << endl;
        memcpy(m_buffer, other.m_buffer, m_size);
    }

    // or more exciting
//    String (const String &other)
//
//    {
//        memcpy(m_buffer, other.m_buffer, m_size);
//    }
    ~String() {
        delete[] m_buffer;
    }

    friend ostream &operator<<(ostream &stream, const String &str); //友元函数,标注这个函数可以访问类私有变量
};

//ostream &operator<<(ostream &stream, const String &str) {
//    stream << str.m_buffer << endl;
//    return stream;
//}

//void Print_String(const String &string) {
//    std::cout << string << std::endl;
//};

struct Vertex {
    float x, y, z;
    Vertex(float i, float i1, float i2)
            :x(i),y(i1),z(i2)
    {
        cout<<"Vertex Created!"<<endl;
    }
    Vertex(const Vertex& vertex)
     :x(vertex.x),y(vertex.y),z(vertex.z)
    {
        cout<<"Vertex copied"<<endl;
    }
};
ostream &operator<<(ostream &stream, const Vertex &vtx) {
    stream<<"x: "<<vtx.x<<", y: "<<vtx.y<<", z: "<<vtx.z<<endl;
    return stream;
}
//int main() {
//    SetConsoleOutputCP(CP_UTF8);
//    string name = "James";
////     Entity a("James");
////     Entity b(20);    //显式调用构造函数创建对象
//
////     Entity a = string("James");
////     Entity b = 20;     //根据构造函数的形参类型进行隐式转换并创建对象
////    Print_Entity(string("James"));  //同样属于隐式转换
//
////    Vector v1 = Vector(1, 2);
////    Vector v2 = Vector(2, 3);
////    Vector powerUp = Vector(5, 5);
////    Vector result_vector = (v1 + v2) * powerUp;
////  result_vector.printXY();
//    //cout<<result_vector<<endl;
////    cout << (v1 == v2) << endl;
////    cout << (v1 != v2) << endl;
//
////    {
////        //两次隐式转换，第一次用来创建Entity对象，第二次用来创建ScopePtr对象
////        //sp是栈上创建的，堆上创建的是e的成员变量Ptr所指向的Entity对象
////        //这样就做到了既能在堆上创建对象，又能在离开作用域时释放内存
////        ScopePtr sp = new Entity(20);
////    }
//
//    //智能指针unique_ptr 和shared_ptr
//    /*
//     * unique_ptr 不能赋值，而shared_ptr 可以赋值, 因为unique_ptr 是独占的，而shared_ptr 是共享的
//     * 创建shared_ptr时会另开启一块儿内存，用来记录引用计数，当引用计数为0时，释放内存
//     * */
////    {
//////      unique_ptr<Entity> sp(new Entity());
////        unique_ptr<Entity> sp = make_unique<Entity>(20);
////        cout << sp->getAge() << endl;
////    }
//
////    shared_ptr<Entity> sp0;
////    {
////        shared_ptr<Entity> sp = make_shared<Entity>(20);
////        sp0 = sp;
////    }
////    cout<<sp0 -> getAge()<<endl;
////    cin.get();  //等两个指针都被删除时，释放创建的Entity对象占用的内存
//
//    //weak_ptr 弱指针 可以通过weak_ptr 来获取shared_ptr 指向的Entity对象，但这并不会增加引用计数
//    //即只有weak_ptr指向对象时，对象会被释放
////    weak_ptr<Entity> wp;
////    {
////        shared_ptr<Entity> sp = make_shared<Entity>(20);
////        wp = sp;
//////        cout<<wp -> getAge()<<endl;  报错
////    }
////    cin.get();
//
////    String s = "Hello!";
////    String second = s;
//////    cout<<s<<endl;
//////    cout<<second<<endl;   //Process finished with exit code -1073740940 (0xC0000374)程序崩溃 如果是浅拷贝，所以两个对象指向同一个内存地址。析构函数执行第二次时会没有内存释放
////    Print_String(second);
//
////    ScopePtr sp = new Entity(20);
////    cout<< sp -> getAge()<<endl;
////    int offset =  (int)&((Vertex*) nullptr) -> x;
//
//    //创建一个Vertex数组
////    Vertex* vertexs = new Vertex[5];
////    vertexs[0] = Vertex{1,2,3};
////    cout<< vertexs[4]<<endl;
////    vector<Vertex> vtxs;
////    //vector 数组中添加元素
////    vtxs.push_back(Vertex{1,2,3});
////    vtxs.push_back(Vertex{4,5,6});
////    //访问vector数组中的元素
////    cout<<vtxs[0]<<endl;
////    //修改元素
////    vtxs[0] = Vertex{7,8,9};
////    //删除指定索引的元素
////    vtxs.erase(vtxs.begin()+1);  //注意begin()返回的是迭代器，而不是数组的指针
////
////    cout<<vtxs[0]<<endl;
////
////    //清空数组
////    vtxs.clear();
//
//    vector<Vertex> vector_vtx ;
////    vector_vtx.push_back(Vertex(1,2,3));
////    vector_vtx.push_back(Vertex(4,5,6));
////    vector_vtx.push_back(Vertex(7,8,9));  //执行3次创建和6次复制，第一次创建并复制一次对象；第二次创建一次对象但vector数组中重新开辟内存，再把第一个对象重新复制，这就要复制两次，同理第三次复制3次，所以总共复制了6次
//
////    vector_vtx.reserve(3);
////    vector_vtx.push_back(Vertex(1,2,3));
////    vector_vtx.push_back(Vertex(4,5,6));
////    vector_vtx.push_back(Vertex(7,8,9)); //创建3次，复制3次。因为vector数组中开辟了内存，所以不需要重新开辟内存，直接把对象复制到vector数组中
//
////    vector_vtx.reserve(3);
////    vector_vtx.emplace_back(1,2,3);
////    vector_vtx.emplace_back(4,5,6);
////    vector_vtx.emplace_back(7,8,9);  //只会创建3次，而不会复制3次，因为emplace_back()会直接把对象构造到vector数组中，而不会从main函数中构造再复制到vector数组中
//
//    return 0;
//}
