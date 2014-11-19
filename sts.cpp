#include "clang/AST/ASTConsumer.h"                                                        
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace clang;
using namespace clang::tooling;

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
    public:
        MyASTVisitor(Rewriter &R) : myRewriter(R) {}

        bool VisitStmt(Stmt *s) {
            cout<<"statement found!!!"<<endl;
            // Only care about If statements.
            if (isa<IfStmt>(s)) {
                IfStmt *ifStatement = cast<IfStmt>(s);
                Stmt *Then = ifStatement->getThen();

                myRewriter.InsertText(Then->getLocStart(), "// the 'if' part\n", true,
                             true);

                Stmt *elseStatement = ifStatement->getElse();

                if(elseStatement){
                    myRewriter.InsertText(elseStatement->getLocStart(), 
                                        "// the 'else' part\n",
                                        true, 
                                        true);
                }
            }

            if(isa<ForStmt>(s)){
                cout<<"for loop found!!!!"<<endl;
                ForStmt *forStatement = cast<ForStmt>(s);
                Stmt *body = forStatement->getBody();
                myRewriter.InsertText(body->getLocStart(), 
                                    "// 'for' loop detected!!\n", 
                                    true,
                                    true);
            }

            return true;
        }

        bool VisitFunctionDecl(FunctionDecl *f) {
            // Only function definitions (with bodies), not declarations.
            if (f->hasBody()) {
                cout<<"function with a real body"<<endl;
                Stmt *FuncBody = f->getBody();

                // Type name as string
                QualType QT = f->getReturnType();
                std::string TypeStr = QT.getAsString();

                // Function name
                DeclarationName DeclName = f->getNameInfo().getName();
                std::string FuncName = DeclName.getAsString();

                // Add comment before
                std::stringstream SSBefore;
                SSBefore << "// Begin function " << FuncName << " returning " << TypeStr
                   << "\n";
                SourceLocation ST = f->getSourceRange().getBegin();
                myRewriter.InsertText(ST, SSBefore.str(), true, true);

                // And after
                std::stringstream SSAfter;
                SSAfter << "\n// End function " << FuncName;
                ST = FuncBody->getLocEnd().getLocWithOffset(1);
                myRewriter.InsertText(ST, SSAfter.str(), true, true);
            }

            return true;
        }

    private:
        /*Handles Rewriting of the source code*/
        Rewriter &myRewriter;
};

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

        std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef file) override {
            llvm::errs() << "** Creating AST consumer for: " << file << "\n";
            myRewriter.setSourceMgr(CI.getSourceManager(), CI.getLangOpts());
            return llvm::make_unique<MyASTConsumer>(myRewriter);
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
