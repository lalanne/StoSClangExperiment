
#include "clang/AST/ASTContext.h"
#include "clang/AST/StmtOpenMP.h"
#include "clang/Basic/OpenMPKinds.h"
#include "clang/AST/ASTConsumer.h"                                                        
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/StmtOpenMP.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
using namespace clang;
using namespace clang::tooling;

static llvm::cl::OptionCategory ToolingSampleCategory("Tooling Sample");

class MyASTVisitor : public RecursiveASTVisitor<MyASTVisitor> {
    public:
        MyASTVisitor(Rewriter &R) : lineNumber{0},
                                    ompDirectiveLineNumberCache{0},
                                    myRewriter{R}{}

        bool VisitStmt(Stmt *s) {
            // Only care about If statements.
            cout<<"name: "<<s->getStmtClassName()<<endl; 
            SourceLocation omp_loc = s->getLocStart();
            SourceManager &SM = myRewriter.getSourceMgr();
            lineNumber = SM.getSpellingLineNumber(omp_loc);
            cout<<"line: "<<lineNumber<<endl;
            
            
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

            cout<<"asking for omp!"<<endl;

            if(isa<OMPExecutableDirective>(s)){
                cout<<"OMP Executable Directive!!!!!  "<<endl;

                if(ompDirectiveLineNumberCache != lineNumber){
                    ompDirectiveLineNumberCache = lineNumber;
                    OMPExecutableDirective* ompExecutableDirective = cast<OMPExecutableDirective>(s);


                    if(isa<OMPParallelDirective>(s)){
                        cout<<"OMP Parallel Directive"<<endl;
                    }
                    
                    if(isa<OMPParallelForDirective>(s)){
                        cout<<"OMP Parallel For Directive"<<endl;
                        OMPParallelForDirective* ompParallelForDirective = cast<OMPParallelForDirective>(s);

                        OMPClause* clause = ompParallelForDirective->getClause(0); 
                        if(clause->getClauseKind() == OMPC_schedule){
                            cout<<"Schedule clause recognized!!!!"<<endl;
                            OMPScheduleClause* scheduleClause = cast<OMPScheduleClause>(clause);

                            switch(scheduleClause->getScheduleKind()){
                                case OMPC_SCHEDULE_static:
                                {
                                    cout<<"static scheduling..."<<endl;
                                    myRewriter.RemoveText(scheduleClause->getScheduleKindLoc(), 
                                                        6);
                                    myRewriter.InsertText(scheduleClause->getScheduleKindLoc(), 
                                                        "runtime", 
                                                        true,
                                                        true);
                                }
                                break;

                                case OMPC_SCHEDULE_runtime:
                                {
                                    cout<<"runtime scheduling..."<<endl;
                                }
                                break;
                            
                            }
                        }
                    }
                }
            }
            
            cout<<"end visit"<<endl<<endl;
            return true;
        }

        bool VisitFunctionDecl(FunctionDecl *f) {
            // Only function definitions (with bodies), not declarations.
            if (f->hasBody()) {
                cout<<"function with a real body"<<endl<<endl;
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
        /*This 2 fields are used for controlling the visit to OMP directives
         * that for some reason clang is visiting twice*/
        unsigned int lineNumber;
        unsigned int ompDirectiveLineNumberCache;
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
