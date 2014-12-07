
#include "MyASTVisitor.hpp"

using namespace clang;
using namespace std;

const unsigned int NUMBER_OF_CHARACTERS_STATIC_SCHEDULE = 6;

MyASTVisitor::MyASTVisitor(Rewriter &R) : lineNumber{0},
                                        ompDirectiveLineNumberCache{0},
                                        myRewriter{R}{}

bool MyASTVisitor::VisitStmt(Stmt *s){
    // Only care about If statements.

    SourceLocation omp_loc = s->getLocStart();
    SourceManager &SM = myRewriter.getSourceMgr();
    lineNumber = SM.getSpellingLineNumber(omp_loc);

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
        ForStmt *forStatement = cast<ForStmt>(s);
        Stmt *body = forStatement->getBody();
        myRewriter.InsertText(body->getLocStart(), 
                            "// 'for' loop detected!!\n", 
                            true,
                            true);
    }

    if(isa<OMPExecutableDirective>(s)){

        if(ompDirectiveLineNumberCache != lineNumber){
            ompDirectiveLineNumberCache = lineNumber;
            OMPExecutableDirective* ompExecutableDirective = cast<OMPExecutableDirective>(s);


            if(isa<OMPParallelDirective>(s)){
            }
            
            if(isa<OMPParallelForDirective>(s)){
                OMPParallelForDirective* ompParallelForDirective = cast<OMPParallelForDirective>(s);

                OMPClause* clause = ompParallelForDirective->getClause(0); 
                if(clause->getClauseKind() == OMPC_schedule){
                    OMPScheduleClause* scheduleClause = cast<OMPScheduleClause>(clause);

                    switch(scheduleClause->getScheduleKind()){
                        case OMPC_SCHEDULE_static:
                        {
                            myRewriter.RemoveText(scheduleClause->getScheduleKindLoc(), 
                                                NUMBER_OF_CHARACTERS_STATIC_SCHEDULE);
                            myRewriter.InsertText(scheduleClause->getScheduleKindLoc(), 
                                                "runtime", 
                                                true,
                                                true);
                        }
                        break;

                        case OMPC_SCHEDULE_runtime:
                        {
                        }
                        break;
                    
                    }
                }
            }
        }
    }
    
    return true;
}

bool MyASTVisitor::VisitFunctionDecl(FunctionDecl *f){
    // Only function definitions (with bodies), not declarations.
    if (f->hasBody()) {
        Stmt *FuncBody = f->getBody();

        // Type name as string
        QualType QT = f->getReturnType();
        string TypeStr = QT.getAsString();

        // Function name
        DeclarationName DeclName = f->getNameInfo().getName();
        string FuncName = DeclName.getAsString();

        // Add comment before
        stringstream SSBefore;
        SSBefore << "// Begin function " << FuncName << " returning " << TypeStr
           << "\n";
        SourceLocation ST = f->getSourceRange().getBegin();
        myRewriter.InsertText(ST, SSBefore.str(), true, true);

        // And after
        stringstream SSAfter;
        SSAfter << "\n// End function " << FuncName;
        ST = FuncBody->getLocEnd().getLocWithOffset(1);
        myRewriter.InsertText(ST, SSAfter.str(), true, true);
    }

    return true;
}

