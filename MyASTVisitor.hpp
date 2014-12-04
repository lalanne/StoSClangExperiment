
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include <iostream>
#include <sstream>

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
    public:
        MyASTVisitor(clang::Rewriter &R) : lineNumber{0},
                                    ompDirectiveLineNumberCache{0},
                                    myRewriter{R}{}

        bool VisitStmt(clang::Stmt *s) {
            // Only care about If statements.
            std::cout<<"name: "<<s->getStmtClassName()<<std::endl; 
            clang::SourceLocation omp_loc = s->getLocStart();
            clang::SourceManager &SM = myRewriter.getSourceMgr();
            lineNumber = SM.getSpellingLineNumber(omp_loc);
            std::cout<<"line: "<<lineNumber<<std::endl;
            
            
            if (clang::isa<clang::IfStmt>(s)) {
                clang::IfStmt *ifStatement = clang::cast<clang::IfStmt>(s);
                clang::Stmt *Then = ifStatement->getThen();

                myRewriter.InsertText(Then->getLocStart(), "// the 'if' part\n", true,
                             true);

                clang::Stmt *elseStatement = ifStatement->getElse();

                if(elseStatement){
                    myRewriter.InsertText(elseStatement->getLocStart(), 
                                        "// the 'else' part\n",
                                        true, 
                                        true);

                }
            }

            if(clang::isa<clang::ForStmt>(s)){
                std::cout<<"for loop found!!!!"<<std::endl;
                clang::ForStmt *forStatement = clang::cast<clang::ForStmt>(s);
                clang::Stmt *body = forStatement->getBody();
                myRewriter.InsertText(body->getLocStart(), 
                                    "// 'for' loop detected!!\n", 
                                    true,
                                    true);
            }

            std::cout<<"asking for omp!"<<std::endl;

            if(clang::isa<clang::OMPExecutableDirective>(s)){
                std::cout<<"OMP Executable Directive!!!!!  "<<std::endl;

                if(ompDirectiveLineNumberCache != lineNumber){
                    ompDirectiveLineNumberCache = lineNumber;
                    clang::OMPExecutableDirective* ompExecutableDirective = clang::cast<clang::OMPExecutableDirective>(s);


                    if(clang::isa<clang::OMPParallelDirective>(s)){
                        std::cout<<"OMP Parallel Directive"<<std::endl;
                    }
                    
                    if(clang::isa<clang::OMPParallelForDirective>(s)){
                        std::cout<<"OMP Parallel For Directive"<<std::endl;
                        clang::OMPParallelForDirective* ompParallelForDirective = clang::cast<clang::OMPParallelForDirective>(s);

                        clang::OMPClause* clause = ompParallelForDirective->getClause(0); 
                        if(clause->getClauseKind() == clang::OMPC_schedule){
                            std::cout<<"Schedule clause recognized!!!!"<<std::endl;
                            clang::OMPScheduleClause* scheduleClause = clang::cast<clang::OMPScheduleClause>(clause);

                            switch(scheduleClause->getScheduleKind()){
                                case clang::OMPC_SCHEDULE_static:
                                {
                                    std::cout<<"static scheduling..."<<std::endl;
                                    myRewriter.RemoveText(scheduleClause->getScheduleKindLoc(), 
                                                        6);
                                    myRewriter.InsertText(scheduleClause->getScheduleKindLoc(), 
                                                        "runtime", 
                                                        true,
                                                        true);
                                }
                                break;

                                case clang::OMPC_SCHEDULE_runtime:
                                {
                                    std::cout<<"runtime scheduling..."<<std::endl;
                                }
                                break;
                            
                            }
                        }
                    }
                }
            }
            
            std::cout<<"end visit"<<std::endl<<std::endl;
            return true;
        }

        bool VisitFunctionDecl(clang::FunctionDecl *f) {
            // Only function definitions (with bodies), not declarations.
            if (f->hasBody()) {
                std::cout<<"function with a real body"<<std::endl<<std::endl;
                clang::Stmt *FuncBody = f->getBody();

                // Type name as string
                clang::QualType QT = f->getReturnType();
                std::string TypeStr = QT.getAsString();

                // Function name
                clang::DeclarationName DeclName = f->getNameInfo().getName();
                std::string FuncName = DeclName.getAsString();

                // Add comment before
                std::stringstream SSBefore;
                SSBefore << "// Begin function " << FuncName << " returning " << TypeStr
                   << "\n";
                clang::SourceLocation ST = f->getSourceRange().getBegin();
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
        clang::Rewriter &myRewriter;
};

