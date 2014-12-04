
#include "MyASTVisitor.hpp"

#include "clang/AST/ASTConsumer.h"                                                        
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace clang;
using namespace clang::tooling;

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");

/*chooses which AST Parsing events to handle*/
class MyASTConsumer : public ASTConsumer {
    public:
        MyASTConsumer(Rewriter &R) : visitor(R) {}

        /*override the method that gets called for each parsed top-level
        declaration.*/
        bool HandleTopLevelDecl(DeclGroupRef DR) override {
            cout<<"top level function declaration"<<endl;
            for (DeclGroupRef::iterator b = DR.begin(), e = DR.end(); b != e; ++b) {
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

class MyFrontendAction : public ASTFrontendAction {
    public:
        MyFrontendAction() {}
        void EndSourceFileAction() override {
            SourceManager &SM = myRewriter.getSourceMgr();
            llvm::errs() << "** EndSourceFileAction for: "
                 << SM.getFileEntryForID(SM.getMainFileID())->getName() << "\n";

            // Now emit the rewritten buffer.
            myRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
        } 

        /*std::unique_ptr<ASTConsumer>*/ASTConsumer*  CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef file) override {
            llvm::errs() << "** Creating AST consumer for: " << file << "\n";
            myRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
            //return llvm::make_unique<MyASTConsumer>(myRewriter);
            return new MyASTConsumer(myRewriter); //danger!!!! awful leak!!!!
        }

    private:
        Rewriter myRewriter;
};


int main(int argc, const char **argv){
    cout<<"Hello World!"<<endl;
    CommonOptionsParser op(argc, argv, ToolingSampleCategory);
    ClangTool Tool(op.getCompilations(), op.getSourcePathList());

    return Tool.run(newFrontendActionFactory<MyFrontendAction>().get());
}
