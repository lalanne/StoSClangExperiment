
#include "MyASTConsumer.hpp"
#include "MyFrontendAction.hpp"

using namespace clang;
using namespace std;

MyFrontendAction::MyFrontendAction(){}

void MyFrontendAction::EndSourceFileAction(){
    SourceManager &SM = myRewriter.getSourceMgr();
    llvm::errs() << "** EndSourceFileAction for: "
         << SM.getFileEntryForID(SM.getMainFileID())->getName() << "\n";

    // Now emit the rewritten buffer.
    myRewriter.getEditBuffer(SM.getMainFileID()).write(llvm::outs());
} 

ASTConsumer*  MyFrontendAction::CreateASTConsumer(CompilerInstance &CI,
                                                StringRef file){
    llvm::errs() << "** Creating AST consumer for: " << file << "\n";
    myRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
    //return llvm::make_unique<MyASTConsumer>(myRewriter);
    return new MyASTConsumer(myRewriter); //danger!!!! awful leak!!!!
}


