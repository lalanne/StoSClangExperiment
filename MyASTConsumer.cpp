
#include "MyASTConsumer.hpp"

#include <iostream>

using namespace clang;
using namespace std;

MyASTConsumer::MyASTConsumer(Rewriter &R) : visitor(R){}

bool MyASTConsumer::HandleTopLevelDecl(DeclGroupRef DR){
    cout<<"top level function declaration"<<endl;

    for(DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
        /* Traverse the declaration using our AST visitor.
         Go inside every function and apply visitor*/
        visitor.TraverseDecl(*b);
        (*b)->dump();
    }
    return true;
}



