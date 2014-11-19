
cmake_minimum_required (VERSION 2.6) 
project (sts) 

add_definitions(-std=c++11)
add_definitions(-Wall)

include_directories("/Users/lalanne/clang-llvm/build/include")  
#include_directories("/Users/lalanne/LLVM/llvm/include")  
#include_directories("/Users/lalanne/LLVM/llvm/build/include")  

link_directories("/Users/lalanne/clang-llvm/build/lib")

add_executable(sts 
        sts.cpp)

target_link_libraries(sts 
                    clangTooling
                    clangBasic
                    clangASTMatchers
                    )  
