#include <utility>

#include "pch.h"


//代表分配的次数
static uint32_t s_AllocCount = 0;
template<typename T>
struct CustomAllocator : public std::allocator<T> {
    template<typename U>
    struct rebind { typedef CustomAllocator<U> other; };

    // 重载allocate函数
    T* allocate(std::size_t n) {
        void* p = ::operator new(n * sizeof(T));
        std::cout << "Allocating: " << n * sizeof(T) << " bytes" << std::endl;
        return static_cast<T*>(p);
    }

    // 重载deallocate函数
    void deallocate(void* p, std::size_t n) {
        ::operator delete(p);
    }
};

void print_name(const std::string& name){
    std::cout<<"name: "<<name<<std::endl;
}
// 重载全局new和delete运算符
void* operator new (size_t size) {
    s_AllocCount++;
    std::cout << "Custom Allocating: " << size << " bytes" << std::endl;
    return malloc(size);
}
void operator delete (void* ptr,size_t size) noexcept {
    std::cout<<"Freeing  "<<size<<"  bytes\n";
    free(ptr);
}

class Timer{
public:
    std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<long long, std::ratio<1, 1000000000>>>  startTime;
    Timer(){
        startTime = std::chrono::high_resolution_clock::now();
    }
    ~Timer(){
        auto endTime = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
        std::cout<<"Timer: "<<(end-start)<<"us"<<std::endl;
    }

};
struct ProfileResult{
    std::string Name;
    long long start,end;
};
struct InstrumentationSession{
    std::string Name;
    explicit InstrumentationSession(std::string  name)
    : Name(std::move(name)){

    }
};
class Instructor{
private:
    InstrumentationSession* m_currentSession;
    std::ofstream m_outPutStream;
    int m_profileCount;
public:
    Instructor()
    :m_currentSession(nullptr),m_profileCount(0) {

    }
    void BeginSession(const std::string& name,const std::string& filePath = "result.json"){
        m_outPutStream.open(filePath);
        Writeheader();
        m_currentSession = new InstrumentationSession(name);
    }
    void EndSession(){
        WriteFooter();
    m_outPutStream.close();
    delete m_currentSession;
    m_currentSession = nullptr;
    m_profileCount = 0;
    }

    void WriteProfile(const ProfileResult& result){
       if(m_profileCount++ > 0){
           m_outPutStream<<",";
       }

       std::string name = result.Name;
       std::replace(name.begin(),name.end(),'"','\'');
       m_outPutStream<<"{"
                     <<"\"cat\":\"function\","
                     <<"\"dur\":"<<result.end-result.start<<","
                     <<"\"name\":\""<<name<<"\","
                     <<"\"ph\":\"X\","
                     <<"\"pid\":0,"
                     <<"\"tid\":"<<0<<","
                     <<"\"ts\":"<<result.start<<"}";
       m_outPutStream.flush();
    }
    void Writeheader(){
        m_outPutStream<<"{\"otherData\": {}, \"traceEvents\":[";
        m_outPutStream.flush();
    }
    void WriteFooter(){
        m_outPutStream<<"]}";
        m_outPutStream.flush();
    }
    static Instructor& Get(){
      static Instructor* instance = new Instructor();
        return *instance;
    };
};
//可视化编程
void PrintFunction(std::string_view str) {
    Timer timer;
    for(int i=0;i<1000;i++){
        std::cout<<str<<": "<<i<<std::endl;
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto start = std::chrono::time_point_cast<std::chrono::microseconds>(timer.startTime).time_since_epoch().count();
    auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
    ProfileResult result = {"PrintFunction", start, end};
    Instructor::Get().WriteProfile(result);
}

//一种简单流行的创建单例的方式
// 当单例第一次被创建时，这个单例的生命周期就等于应用的生命周期
class Singleton{
public:
    //删除了复制构造函数和复制赋值操作符,使其不可复制
    Singleton (const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    //这里将静态常量放在函数下，第一次调用Get 函数时，创建一次实例，此后都是调用这个已经创建好的实例
    static Singleton& Get(){
        static Singleton instance;
        return instance;
    };
    static float Float (){
        return Get().IFloat();
    }
private:
    //将构造方法
    Singleton(){};
    float IFloat(){
        return m_float;
    }

    float m_float = 0.5f;

};

class Object{
    int x,y,z;
};
//Singleton Singleton::instance;

//返回左值引用,GetValue既可以作为左值，也可以作为右值
int& GetValue(){
    static int value = 10;
    return value;
}
//左值与右值的另一个规则就是，不能将右值赋值给左值引用
//这里的形参要求是一个左值引用
void SetLValue(const int& i){

}

void SetRValue(int&& i){

}

//c++中参数的计算顺序
void print_add(int a , int b){
    std::cout<<"a : "<<a<<", b: "<<b<<std::endl;
}

//c++移动语义
class String{
public:
    String() {

    }
    String(const char* string)
       :m_size(strlen(string)){
        std::cout<<"String Created"<<std::endl;
        m_string = new char [m_size];
        memcpy(m_string,string,m_size);
   }
    String(const String& other)
            :m_size(other.m_size){
        std::cout<<"String Copied"<<std::endl;
        m_string = new char [m_size];
        memcpy(m_string,other.m_string,m_size);
    }
   String(String&& other) noexcept
      :m_size(other.m_size),m_string(other.m_string){
       std::cout<<"String Moved"<<std::endl;
       other.m_size = 0;
       //防止指针悬挂，设置为空指针
       other.m_string = nullptr;
   }

   //创建移动赋值操作符
   String& operator= (String&& other)
        {
        std::cout<<"String Moved"<<std::endl;
        if(this != &other){
            delete[] m_string;
            m_string = other.m_string;
            m_size = other.m_size;
            other.m_size = 0;
            //防止指针悬挂，设置为空指针
            other.m_string = nullptr;
        }
        return *this;
    }
   ~String(){
        std::cout<<"String destroied"<<std::endl;
        delete m_string;
    }
    void print_name(){
        for(uint32_t i=0; i<m_size;i++){
            printf("%c",m_string[i]);
        }
        printf("\n");
    }
private:
    char* m_string;
    uint32_t  m_size;
};
class Entity{
public:
    Entity(String string)
            : string(string){

    }
    Entity(const String& string)
      : string(string){

    }
    Entity(String&& string)
       :string(std::move(string)){

    }
    void print(){
       string.print_name();
    }
private:
    String string;
};
//int main()
//{
//    SetConsoleOutputCP(CP_UTF8);
////    std::string name(10000, 'a');
////    print_name(name);
////    std::cout<<s_AllocCount<<"  Allocations"<<std::endl;
//
//    // 使用自定义分配器创建std::string
//    using CustomString = std::basic_string<char, std::char_traits<char>, CustomAllocator<char>>;
////    CustomString long_name(10000, 'a');
////    CustomString first_long_name = long_name.substr(0,5000);
////    CustomString last_long_name = long_name.substr(5001,9999);  //发现分配了3次内存
////
////    std::string_view first_long_name_view(long_name.c_str(),5000);
////    std::string_view last_long_name_view(long_name.c_str()+5000,9999); //发现这样不会额外分配内存，因为这是观察之前早就创建好的long_name 字符串
////
////    //完美的0次分配
////    const char* name = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
////    std::string_view first_name(name,40);
////    std::string_view last_name(name+41,94);
////    std::cout << s_AllocCount << " Allocations" << std::endl;
//    //除了在substr方法中，在形参中使用也不会导致分配
//    // 例如 void print_name(const std::string& name) ,如果调用方法处使用string_view还是会分配一次内存，
//    // 可以写成 void print_name(std::string_view name)
//
//
//    // 开始记录
////    {
////        Instructor::Get().BeginSession("Profile");
////        PrintFunction("hello");
////        PrintFunction("world");
////        Instructor::Get().EndSession();
////    }
//
//    //单例模式
//    //c++中的单例模式是一种组织一堆全局变量和静态函数的方式，这些静态函数可能会作用于这些全局变量，也可能不会
//    //实例化只有一次，这个实例类似于一个单一的名称空间
////    float f = Singleton::Float();
////    std::cout<<f<<std::endl;
//
//    //c++中的小字符串优化
//    //c++中对std::string 会有小字符串的优化，当字符串的长度小于某个值时，字符串的创建并不会分配内存，而是保存在栈缓冲区中，这在debug模式下不会生效，但这并不代表
//    //c++没有对小字符串进行优化，只是debug 模式下的特殊设置
////    std::string str = "hello world";
////    const char* str2 = "hello world";
////    std::cout<<str.size()<<std::endl;
////    std::cout<<strlen(str2)<<std::endl;
//
//    //跟踪内存分配的简单方法，观察调用堆栈
//    //在operator new 重写函数中定义断点，观察分配内存
////    using CustomObject = CustomAllocator<Object>;
////    auto* cusObj = new CustomObject ();
////    delete cusObj;
//
//
//    //c++中的左值和右值，左值是有某种存储支持的变量，右值就是临时值。并不是单纯的等号左边就是左值，反之就是右值
////    int i = 10;
////    int j = GetValue();
////    GetValue() = 20;
////    std::cout<<j<<std::endl;
////    std::cout<<GetValue()<<std::endl;
//////    SetValue(10); 报错，因为10 是一个右值
////    //赋值给左值引用的只能是左值
////    SetLValue(GetValue());
////    SetLValue(i);
////
////    const int& t = 10;  //这种情况看似是将一个右值赋值给了左值引用，但是实际上编译器是创建了一个临时左值 temp，int temp = 10; 然后 int & t = temp; 所以实际上还是左值赋给左值引用
////    std::string firstName = "Vito";
////    std::string lastName = "kang";
////    std::string fullName = firstName + lastName;  //这里的firstName + lastName是一个右值，即一个拼接好的字符串
////
////    //右值引用
//////    SetRValue(i);  只能将右值赋值给右值引用，使用左值报错
////    SetRValue(10);
//
//
//    //c++中某些时候的参数运算顺序属于未定义的行为，会根据debug/rel ease 模式的不同或者 编译器种类的不同而不同
//    //c++17 规定了两个参数的计算不是同时的，但还是没有规定顺序
////    int value = 0;
////    print_add(value++,value++);
//
//    //c++中的移动语义
//    //在使用的类中实现移动
////    Entity("Vito258");
//     String apple ("apple");
//
//    //使用移动赋值语法
////    String string("chervno");
////    String dest = string;    这样会调用赋值构造方法
//    //std::move 会将已有对象标记为临时对象，用于之后的窃取资源
//    //使用移动构造函数
////    String dest = std::move(string);
////    string.print_name();
////    dest.print_name();
////使用移动赋值操作符
////      String dest;
////      dest = std::move(dest);
//}
