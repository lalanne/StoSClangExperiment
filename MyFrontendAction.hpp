
#include "MyASTConsumer.hpp"

#include "clang/Frontend/FrontendAction.h"

class MyFrontendAction : public clang::ASTFrontendAction {
    public:
        MyFrontendAction() {}
        void EndSourceFileAction() override {
            clang::SourceManager &SM = myRewriter.getSourceMgr();
            llvm::errs() << "** EndSourceFileAction for: "
                 << SM.getFileEntryForID(SM.getMainFileID())->getName() << "\n";

            // Now emit the rewritten buffer.
            myRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
        } 

        /*std::unique_ptr<ASTConsumer>*/clang::ASTConsumer*  CreateASTConsumer(clang::CompilerInstance &CI,
                                                 clang::StringRef file) override {
            llvm::errs() << "** Creating AST consumer for: " << file << "\n";
            myRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
            //return llvm::make_unique<MyASTConsumer>(myRewriter);
            return new MyASTConsumer(myRewriter); //danger!!!! awful leak!!!!
        }

    private:
        clang::Rewriter myRewriter;
};


