#include "pch.h"

class Entity{
public:
    std::string name;
    int gender;
    virtual ~Entity() {
        std::cout<<"~Entity()"<<std::endl;
    }
};

class Player : public Entity{
    int level;
    int hp;
    int mp;
    int exp;
    int attack;
    int defense;
};

class Monster : public Entity{
public:
    int hp;
    int attack;
    int defense;

};
//使用Timer计时器进行基准测试
class Timer{

    std::chrono::time_point<std::chrono::system_clock,std::chrono::duration<long long, std::ratio<1, 1000000000>>>  startTime;
public:
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

std::tuple<std::string,int> creatPerson(){
    return std::make_tuple("张三",1);
}

//
//std::string ReadFileAsString (const std::string & filePath){
//    std::string resultString;
//    std::ifstream ifstream(filePath);
//
//    if(ifstream){
//        //读取文件
//        ifstream.close();
//        return resultString;
//    }
//    //这样会有一个问题，那就是当文件不存在或者为空时都会返回“”，如果我们想具体情况具体分析的话，那怎么办呢？ 使用OPTINAL
//    return "";
//}

std::optional<std::string> ReadFileAsString (const std::string & filePath){

    std::ifstream ifstream(filePath);
    if(ifstream){
        //读取文件
        std::string resultString;
        ifstream.close();
        return resultString;
    }
    return {};
}

//使用多线程来让程序运行地更快
// 共享资源
int sharedData = 0;
std::mutex mtx;
// 异步计算函数
void compute(int id, int value) {
    // 使用互斥锁保护共享数据
    std::lock_guard<std::mutex> lock(mtx);
    sharedData += value;
    std::cout << "Thread " << id << " computed and added " << value << std::endl;
}

//int main()
//{
//     SetConsoleOutputCP(CP_UTF8);
//     //dynamic_cast 做类型检测,主要用于多态类型之间相互转换
////     auto* tiger = new Monster();
////     Entity* e = tiger;
////     if(dynamic_cast<Monster*>(e)){
////         std::cout<<"e is a monster"<<std::endl;
////     }else if(dynamic_cast<Player*>(e)){
////         std::cout<<"e is a player"<<std::endl;
////     }else{
////         std::cout<<"e is just a entity"<<std::endl;
////     }
//
//     //基准测试
////    {
////        //作用域开头创建timer
////        Timer timer;
////        int i = 0;
////        for(int j = 0;j<100000000;j++){
////            i+=2;
////        }
////      //Debug - 185ms;  Release - 1us
////    }
//
//     //shared_pointer 和 unique_pointer
////    {
////        Timer timer;
////      std::array<std::shared_ptr<int>, 1000> sharedPtrs;
////      for(int i=0;i<1000;i++){
////          sharedPtrs[i] = std::make_shared<int>(i);
////      }
////    }
////    {
////        Timer timer;
////        std::array<std::unique_ptr<int>, 1000> uniquePtrs;
////        for(int i=0;i<1000;i++){
////            uniquePtrs[i] = std::make_unique<int>(i);
////        }
////    }
//
//
//     //结构化绑定用于返回多个类型不同的值
////     std::string name;
////     int age;
////     std::tie(name,age) = creatPerson();
//        //c++17下的结构化绑定
////     auto[name,age] = creatPerson();
////     std::cout<<name<<std::endl;
////     std::cout<<age<<std::endl;
//
//    //处理OPTIONAL数据，用于储存可能存在也可能不存在的数据
////    auto fileData = ReadFileAsString(R"(D:\C++\clionproject\code_2\process71-80\data.txt)");
////    std::string value = fileData.value_or("not present"); //如果文件字符串存在于optinal中，则返回那个字符串，反之返回我们传入的任何值
////    std::cout<<value<<std::endl;
////    if(fileData.has_value()){
////        //值已被正确设置
////        std::cout<<"fileData successfully read"<<std::endl;
////    }else{
////        std::cout<<"file could not be opened"<<std::endl;
////    }
//
//     //单一变量处理多种类型的数据,除了使用union，你还可以使用variant
////    std::variant<std::string,int> data ;
//    //和union不同，union申请最大的数据类型的内存空间，而variant的内存大小是其模板参数中最大类型大小的函数，加上可能的对齐填充
////    std::cout<<sizeof(std::string)<<std::endl;  //32
////    std::cout<<sizeof(int)<<std::endl;   //4
////    std::cout<<sizeof(data)<<std::endl;  //40
////    data = "vito258";
////
////    //数据类型索引，返回一个数据类型索引在这里0代表 std::string,1代表int
////    std::cout<< data.index()<<std::endl;
////    std::cout<< std::get<std::string>(data)<<std::endl;
////
////    data = 10;
////    //std::get_if()允许你在运行时检查std::variant中当前存储的是哪种类型，并安全地获取指向该类型值的指针
////    int * ptr = std::get_if<int>(&data);
////    if(ptr){
////        std::cout<<"现在的data是int 类型"<<std::endl;
////    }
////    std::cout<< std::get<int>(data)<<std::endl;
//
//    //如何储存任意变量的数据，使用std::any
////    std::any data;
////    data = "vito";
////    auto value = std::any_cast<const char*>(data);
////    std::cout<<value<<std::endl;
////    data = 26;
//
//    // 创建多个异步任务
//    std::vector<std::future<void>> futures;
//    for (int i = 0; i < 5; ++i) {
//        // 异步执行compute函数
//        futures.push_back(std::async(std::launch::async, compute, i, i * 10));
//    }
//
//    // 等待所有异步任务完成
//    for (auto& fut : futures) {
//        fut.wait();
//    }
//
//    // 输出最终的sharedData值
//    std::cout << "Final sharedData value is " << sharedData << std::endl;
//}
