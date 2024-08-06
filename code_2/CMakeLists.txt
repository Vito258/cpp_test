cmake_minimum_required(VERSION 3.26.4)
project(code_2)

set(CMAKE_CXX_STANDARD 17)

#设置预编译头文件
add_library(pch  ${CMAKE_CURRENT_SOURCE_DIR}/includes/pch.cpp)
#指定某个目标的头文件搜索路径
target_include_directories(pch PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
# 替换为你的预编译头文件名
target_precompile_headers(pch
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes/pch.h
)

# 设置 GLFW 库和头文件路径
set(GLFW_LIB_DIR "Dependencies/GLFW/lib-mingw-w64") # 更改为你的库文件所在目录
set(GLFW_INCLUDE_DIR "Dependencies/GLFW/include") # 更改为你的头文件所在目录

# 添加 GLFW 库路径
link_directories(${GLFW_LIB_DIR})
## 包含 GLFW 头文件路径
include_directories(${GLFW_INCLUDE_DIR})

set(ENGINE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Engine")
set(ENGINE_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine")
add_subdirectory(${ENGINE_SRC_DIR} ${ENGINE_BIN_DIR}) # 如果不在同一级目录，请提供相对或绝对路径

#进行预处理器定义
#全局定义，编译时定义一个名为DEBUG的宏，其值为1。
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()
#更细粒度的划分，针对特定构建目标的宏，这里的my_target 可以是任何其他可执行文件或库
#定义一个MY_MACRO的宏其值为1
#target_compile_definitions(my_target PRIVATE MY_MACRO=1)

#set(MY_MACRO OFF)
#if(CMAKE_BUILD_TYPE MATCHES Debug)
#    set(MY_MACRO ON)
#endif()
#
#target_compile_definitions(my_executable PRIVATE
#        $<$<CONFIG:Debug>:MY_MACRO=1>
#        $<$<CONFIG:Release>:MY_MACRO=0>
#)





add_executable(code_2
        process1-20/main.cpp
        process21-30/Main.cpp
        process21-30/Log.cpp
        process21-30/static.cpp
        process21-30/enum.cpp
        process31-40/Main.cpp
        process41-50/main.cpp
        process51-60/main.cpp
        template.cpp
        process61-70/main.cpp
        process71-80/main.cpp
        process81-90/main.cpp
        process91-94/main.cpp
)


## 对于每个需要使用预编译头的目标，添加如下命令
target_link_libraries(code_2 pch)

# 链接 GLFW 库
if(WIN32)
    if(BUILD_SHARED_LIBS)
        target_link_libraries(code_2 glfw3dll)
    else()
        target_link_libraries(code_2 glfw3)
    endif()
else()
    target_link_libraries(code_2 glfw)
endif()

# 将自定义编译库链接到本项目
target_link_libraries(code_2 Engine) # 假设 Engine 已经被正确添加为子目录并构建为库




