set(LLVM_LINK_COMPONENTS support)
set(LLVM_USED_LIBS clangTooling clangBasic clangAST)

add_clang_executable(sts
  sts.cpp
  )
target_link_libraries(sts
  clangTooling
  clangBasic
  clangASTMatchers
  )
