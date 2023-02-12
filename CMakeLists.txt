project(RB_Tree)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(node RB_Tree_Node.cpp)   #根据提供的源文件生成库，默认静态库
add_library(tree RB_Tree.cpp)   #根据提供的源文件生成库，默认静态库
add_executable(test main.cpp)    #生成目标可执行文件
target_link_libraries(test node tree)   #指定链接给定目标和/或其依赖项时要使用的库或标志。

