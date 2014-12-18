set(LLVM_LINK_COMPONENTS support)
set(LLVM_USED_LIBS clangTooling clangBasic clangAST)

include_directories(include)

add_clang_executable(sts
    src/sts.cpp
    src/MyASTConsumer.cpp
    src/MyFrontendAction.cpp
    src/MyASTVisitor.cpp
    src/SwapToRuntime.cpp
  )

target_link_libraries(sts
                      clangTooling
                      clangBasic
                      clangASTMatchers
                    )
