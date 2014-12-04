
#include "clang/AST/ASTConsumer.h"                                                        

#include <iostream>

/*chooses which AST Parsing events to handle*/
class MyASTConsumer : public clang::ASTConsumer {
    public:
        MyASTConsumer(clang::Rewriter &R) : visitor(R) {}

        /*override the method that gets called for each parsed top-level
        declaration.*/
        bool HandleTopLevelDecl(clang::DeclGroupRef DR) override {
            std::cout<<"top level function declaration"<<std::endl;
            for (clang::DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
                /* Traverse the declaration using our AST visitor.
                 Go inside every function and apply visitor*/
                visitor.TraverseDecl(*b);
                (*b)->dump();
            }
             return true;
        }

    private:
        MyASTVisitor visitor;
};

