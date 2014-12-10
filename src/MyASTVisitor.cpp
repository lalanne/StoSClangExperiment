
#include "MyASTVisitor.hpp"

using namespace clang;
using namespace std;

const unsigned int NUMBER_OF_CHARACTERS_STATIC_SCHEDULE = 6;
const unsigned int NUMBER_OF_CHARACTERS_DYNAMIC_SCHEDULE = 7;
const unsigned int NUMBER_OF_CHARACTERS_GUIDED_SCHEDULE = 6;
const unsigned int NUMBER_OF_CHARACTERS_AUTO_SCHEDULE = 4;

MyASTVisitor::MyASTVisitor(Rewriter &R) : lineNumber{0},
                                        ompDirectiveLineNumberCache{0},
                                        myRewriter{R}{}

bool MyASTVisitor::VisitStmt(Stmt *s){
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

                        case OMPC_SCHEDULE_dynamic:
                        {
                            myRewriter.RemoveText(scheduleClause->getScheduleKindLoc(), 
                                                NUMBER_OF_CHARACTERS_DYNAMIC_SCHEDULE);
                            myRewriter.InsertText(scheduleClause->getScheduleKindLoc(), 
                                                "runtime", 
                                                true,
                                                true);
                        }
                        break;

                        case OMPC_SCHEDULE_guided:
                        {
                            myRewriter.RemoveText(scheduleClause->getScheduleKindLoc(), 
                                                NUMBER_OF_CHARACTERS_GUIDED_SCHEDULE);
                            myRewriter.InsertText(scheduleClause->getScheduleKindLoc(), 
                                                "runtime", 
                                                true,
                                                true);
                        }
                        break;

                        case OMPC_SCHEDULE_auto:
                        {
                            myRewriter.RemoveText(scheduleClause->getScheduleKindLoc(), 
                                                NUMBER_OF_CHARACTERS_AUTO_SCHEDULE);
                            myRewriter.InsertText(scheduleClause->getScheduleKindLoc(), 
                                                "runtime", 
                                                true,
                                                true);
                        }
                        break;
                    
                    }
                }
            }
        }
    }
    
    return true;
}

