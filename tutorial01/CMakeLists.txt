cmake_minimum_required(VERSION 3.1)
project(leptjson_test CXX)  # 修改1：指定 C++ 语言

# 设置 C++ 标准和编译选项
set(CMAKE_CXX_STANDARD 11)  # 修改2：强制 C++11 标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")  # 修改3：C++ 编译选项

# 如果是 GNU 或 Clang 编译器，添加额外优化选项（可选）
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wno-gnu-anonymous-struct -Wno-c99-extensions)  # 修改4：抑制 C++ 对 C 扩展的警告
endif()

# 添加库（假设 leptjson 是 C 源代码）
add_library(leptjson STATIC leptjson.cpp ../tutorial02/leptjson.cpp ../tutorial01_answer/leptjson.h ../tutorial02/test.cpp ../tutorial01_answer/test.cpp)  # 修改5：显式声明为静态库

# 添加测试可执行文件（注意：源文件改为 .cpp 后缀）
add_executable(leptjson_test test.cpp)  # 修改6：C++ 源文件
target_link_libraries(leptjson_test leptjson)  # 修改7：链接库