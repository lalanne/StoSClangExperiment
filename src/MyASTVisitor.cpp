
#include "MyASTVisitor.hpp"

#include <iostream>

using namespace clang;
using namespace std;

const unsigned int NUMBER_OF_CHARACTERS_STATIC_SCHEDULE = 6;
const unsigned int NUMBER_OF_CHARACTERS_DYNAMIC_SCHEDULE = 7;
const unsigned int NUMBER_OF_CHARACTERS_GUIDED_SCHEDULE = 6;
const unsigned int NUMBER_OF_CHARACTERS_AUTO_SCHEDULE = 4;

MyASTVisitor::MyASTVisitor(Rewriter &R) : lineNumber{0},
                                        ompDirectiveLineNumberCache{0},
                                        myRewriter{R}{}

void MyASTVisitor::swap_static_to_runtime(OMPScheduleClause* const clause){
    myRewriter.RemoveText(clause->getScheduleKindLoc(), 
                        NUMBER_OF_CHARACTERS_STATIC_SCHEDULE);
    myRewriter.InsertText(clause->getScheduleKindLoc(), 
                        "runtime", 
                        true,
                        true);
}

void MyASTVisitor::swap_dynamic_to_runtime(OMPScheduleClause* const clause){
    myRewriter.RemoveText(clause->getScheduleKindLoc(), 
                        NUMBER_OF_CHARACTERS_DYNAMIC_SCHEDULE);
    myRewriter.InsertText(clause->getScheduleKindLoc(), 
                        "runtime", 
                        true,
                        true);
}

void MyASTVisitor::swap_guided_to_runtime(OMPScheduleClause* const clause){
    myRewriter.RemoveText(clause->getScheduleKindLoc(), 
                        NUMBER_OF_CHARACTERS_GUIDED_SCHEDULE);
    myRewriter.InsertText(clause->getScheduleKindLoc(), 
                        "runtime", 
                        true,
                        true);
}

void MyASTVisitor::swap_auto_to_runtime(OMPScheduleClause* const clause){
    myRewriter.RemoveText(clause->getScheduleKindLoc(), 
                        NUMBER_OF_CHARACTERS_AUTO_SCHEDULE);
    myRewriter.InsertText(clause->getScheduleKindLoc(), 
                        "runtime", 
                        true,
                        true);
}

bool MyASTVisitor::VisitStmt(Stmt *s){
    SourceLocation omp_loc = s->getLocStart();
    SourceManager &SM = myRewriter.getSourceMgr();
    lineNumber = SM.getSpellingLineNumber(omp_loc);

    if(isa<OMPExecutableDirective>(s)){

        if(ompDirectiveLineNumberCache != lineNumber){
            ompDirectiveLineNumberCache = lineNumber;

            if(isa<OMPParallelDirective>(s)){
            }

            if(isa<OMPForDirective>(s)){
                OMPForDirective* ompForDirective = cast<OMPForDirective>(s);

                OMPClause* clause = ompForDirective->getClause(0); 
                if(clause->getClauseKind() == OMPC_schedule){
                    OMPScheduleClause* scheduleClause = cast<OMPScheduleClause>(clause);

                    switch(scheduleClause->getScheduleKind()){
                        case OMPC_SCHEDULE_static:
                        {
                            swap_static_to_runtime(scheduleClause);
                        }
                        break;

                        case OMPC_SCHEDULE_dynamic:
                        {
                            swap_dynamic_to_runtime(scheduleClause);
                        }
                        break;

                        case OMPC_SCHEDULE_guided:
                        {
                            swap_guided_to_runtime(scheduleClause);
                        }
                        break;

                        case OMPC_SCHEDULE_auto:
                        {
                            swap_auto_to_runtime(scheduleClause);
                        }
                        break;

                        case OMPC_SCHEDULE_unknown: //should throw here!
                        case OMPC_SCHEDULE_runtime: //no action needed!
                        case NUM_OPENMP_SCHEDULE_KINDS: //to avoid warning!
                        break;
                    }
                }
            }
            
            if(isa<OMPParallelForDirective>(s)){
                OMPParallelForDirective* ompParallelForDirective = cast<OMPParallelForDirective>(s);

                OMPClause* clause = ompParallelForDirective->getClause(0); 
                if(clause->getClauseKind() == OMPC_schedule){
                    OMPScheduleClause* scheduleClause = cast<OMPScheduleClause>(clause);

                    switch(scheduleClause->getScheduleKind()){
                        case OMPC_SCHEDULE_static:
                        {
                            swap_static_to_runtime(scheduleClause);
                        }
                        break;

                        case OMPC_SCHEDULE_dynamic:
                        {
                            swap_dynamic_to_runtime(scheduleClause);
                        }
                        break;

                        case OMPC_SCHEDULE_guided:
                        {
                            swap_guided_to_runtime(scheduleClause);
                        }
                        break;

                        case OMPC_SCHEDULE_auto:
                        {
                            swap_auto_to_runtime(scheduleClause);
                        }
                        break;

                        case OMPC_SCHEDULE_unknown: //should throw here!
                        case OMPC_SCHEDULE_runtime: //no action needed!
                        case NUM_OPENMP_SCHEDULE_KINDS: //to avoid warning!
                        break;
                    }
                }
            }
        }
    }
    return true;
}

