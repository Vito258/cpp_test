#include <iostream>
#include <windows.h>
using namespace std;


//自定义Array 类
template<typename T,size_t size>
class Array{
public:
    Array(){

    }
private:
    T m_data[size];
};

//自定义vector类
template<typename T>
class Vector{
public:
    Vector(){
        ReAlloc(m_capacity);
    }
    //移动构造函数
    Vector(Vector&& other){
        if(this != other){
            this->m_size = other.m_size;
            this->m_data = other.m_data;
            other.m_size = 0;
            other.m_data = nullptr;
        }
    }
    //只用来返回索引处数据
    const T& operator[](size_t index) const{
        return m_data[index];
    };
    //可以通过这里来修改索引处数据
    T& operator[](size_t index){
        return m_data[index];
    }
    //新增数据
    void push_back(T&& item)
    {
        if(m_size>m_capacity/2){
            ReAlloc(m_capacity*2);
        }
        m_data[m_size] = std::move(item);
        m_size++;
    }

    template<typename... Args>
    //自动创建根据传入的可变数量的参数集args自动创建 T类，并新增到Vector
    T& emplace_back(Args&&... args){
        if(m_size>m_capacity/2){
            ReAlloc(m_capacity*2);
        }
        //1、在堆栈中构造并将数据移动到m_data
//        m_data[m_size] = T(std::forward<Args>(args)...);
        //2、直接在m_data中构造
        new(&m_data[m_size]) T(std::forward<Args>(args)...);
        return m_data[m_size++];
    }
    //获得长度
    [[nodiscard]] size_t size() const {
        return m_size;
    }

    //删除最后的数据
    void pop_back(){
        if(m_size > 0){
            m_size--;
            m_data[m_size].~T();
        }
    }

    //删除全部数据
    void clear(){
        for(size_t i=0;i<m_size;i++){
            m_data[i].~T();
        }
        m_size = 0;
    }
    //打印全部数据
    void print_all(){
        if(m_size > 0){
            for(size_t i=0;i<m_size;i++)
                std::cout<<m_data[i]<<std::endl;
            std::cout<<"------------------------------------"<<std::endl;
        }else{
            std::cout<<"vector is empty"<<std::endl;
        }
    }
    ~Vector(){
        clear();
        delete [] m_data;
        m_size = 0;
    }
private:
    T* m_data = nullptr;
    //size 是实际的容纳的数据长度
    size_t m_size = 0;
    //capacity 是数组的容量
    size_t m_capacity = 2;

    //重新分配内存的方法
    void ReAlloc(size_t newCapacity){
        //创建新数组
//        T* t_block = new T [newCapacity];
        //防止撞车事故，使用::operator new 和 ::operator delete
        T* t_block =(T*) ::operator new (newCapacity * sizeof(T));
        if(m_size > newCapacity)
            //缩小数组
            m_size = newCapacity;
        //复制数据
        for(size_t i=0;i<m_size;i++){
            t_block[i] = std::move(m_data[i]);
        }

        for(size_t i=0;i<m_size;i++){
            m_data[i].~T();
        }
//        delete [] m_data;
        ::operator delete (m_data,m_capacity * sizeof(T));
        m_data = t_block;
        m_capacity = newCapacity;
        std::cout<<"capacity has renewed: "<<newCapacity<<std::endl;
    }
};
int main()
{
//     std::vector<int> vector1;
//     vector1.push_back(1);
//     vector1.push_back(2);


//       Vector<int> vector2;
//       vector2.push_back(1);
//       vector2.push_back(2);

       Vector<std::string> vector2;
       vector2.push_back("hello");
       vector2.push_back("world");
       vector2.push_back("!");
       std::cout<<"Vector's size is "<< vector2.size()<<std::endl;
       vector2.print_all();
       vector2.pop_back();
       vector2.print_all();
       vector2.clear();
       vector2.print_all();
}
