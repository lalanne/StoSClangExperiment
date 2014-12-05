
#include "MyASTVisitor.hpp"

using namespace clang;
using namespace std;

MyASTVisitor::MyASTVisitor(Rewriter &R) : lineNumber{0},
                                        ompDirectiveLineNumberCache{0},
                                        myRewriter{R}{}

bool MyASTVisitor::VisitStmt(Stmt *s){
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

bool MyASTVisitor::VisitFunctionDecl(FunctionDecl *f){
    // Only function definitions (with bodies), not declarations.
    if (f->hasBody()) {
        cout<<"function with a real body"<<endl<<endl;
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

