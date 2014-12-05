
#ifndef MY_AST_VISITOR_WIUHFEIQUWHFE
#define MY_AST_VISITOR_WIUHFEIQUWHFE

#include "MyASTVisitor.hpp"

#include "clang/AST/ASTConsumer.h"
#include "clang/Rewrite/Core/Rewriter.h"

/*chooses which AST Parsing events to handle*/
class MyASTConsumer : public clang::ASTConsumer{
    public:
        MyASTConsumer(clang::Rewriter &R);

        /*override the method that gets called for each parsed top-level
        declaration.*/
        bool HandleTopLevelDecl(clang::DeclGroupRef DR) override;

    private:
        MyASTVisitor visitor;
};

#endif //MY_AST_VISITOR_WIUHFEIQUWHFE


