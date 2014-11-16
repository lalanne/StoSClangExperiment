#include "clang/AST/ASTConsumer.h"

#include <iostream>

using namespace std;
using namespace clang;

class MyASTConsumer : public ASTConsumer{
    
};

int main(){
    cout<<"Hello World!"<<endl;
    return 0;
}
