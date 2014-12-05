
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Basic/SourceManager.h"

class MyFrontendAction : public clang::ASTFrontendAction {
    public:
        MyFrontendAction();

        void EndSourceFileAction() override;

        /*std::unique_ptr<ASTConsumer>*/
        clang::ASTConsumer*  CreateASTConsumer(clang::CompilerInstance &CI,
                                            llvm::StringRef file) override;

    private:
        clang::Rewriter myRewriter;
};


