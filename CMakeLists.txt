
cmake_minimum_required (VERSION 2.6) 
project (sts) 

add_definitions(-std=c++11)
add_definitions(-Wall)

include_directories("/Users/lalanne/LLVM/llvm/tools/clang/include")  
include_directories("/Users/lalanne/LLVM/llvm/include")  
#link_directories("${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2-master/")

add_executable(sts 
        sts.cpp)

#target_link_libraries(generator tinyxml2)  
