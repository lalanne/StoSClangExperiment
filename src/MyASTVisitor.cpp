
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

    if(isa<OMPExecutableDirective>(s)){

        if(ompDirectiveLineNumberCache != lineNumber){
            ompDirectiveLineNumberCache = lineNumber;

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

