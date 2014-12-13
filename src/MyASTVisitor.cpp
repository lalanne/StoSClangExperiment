
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

void MyASTVisitor::process_omp_schedule_clause(OMPClause* const clause){
    OMPScheduleClause* const scheduleClause = cast<OMPScheduleClause>(clause);
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

unsigned int MyASTVisitor::compute_schedule_clause_position(const OMPParallelForDirective* const ompParallelForDirective){
    const unsigned int numberOfClauses = ompParallelForDirective->getNumClauses();
    for(unsigned int i=0; i<numberOfClauses; ++i){
        OMPClause* const tmp = ompParallelForDirective->getClause(i);
        if(tmp->getClauseKind() == OMPC_schedule) return i;
    }
}

unsigned int MyASTVisitor::compute_schedule_clause_position(const OMPForDirective* const ompForDirective){
    const unsigned int numberOfClauses = ompForDirective->getNumClauses();
    for(unsigned int i=0; i<numberOfClauses; ++i){
        OMPClause* const tmp = ompForDirective->getClause(i);
        if(tmp->getClauseKind() == OMPC_schedule) return i;
    }
}

void MyASTVisitor::process_omp_executable_directive(const Stmt* const s){
    if(ompDirectiveLineNumberCache != lineNumber){
        ompDirectiveLineNumberCache = lineNumber;

        if(isa<OMPForDirective>(s)){
            const OMPForDirective* const ompForDirective = cast<OMPForDirective>(s);
            const unsigned int schedulePosition = compute_schedule_clause_position(ompForDirective);

            OMPClause* const clause = ompForDirective->getClause(schedulePosition); 
            if(clause->getClauseKind() == OMPC_schedule) process_omp_schedule_clause(clause);
        }
        
        if(isa<OMPParallelForDirective>(s)){
            const OMPParallelForDirective* const ompParallelForDirective = cast<OMPParallelForDirective>(s);
            const unsigned int schedulePosition = compute_schedule_clause_position(ompParallelForDirective);

            OMPClause* const clause = ompParallelForDirective->getClause(schedulePosition); 
            if(clause->getClauseKind() == OMPC_schedule) process_omp_schedule_clause(clause);
        }
    }
}

bool MyASTVisitor::VisitStmt(Stmt *s){
    SourceLocation omp_loc = s->getLocStart();
    SourceManager &SM = myRewriter.getSourceMgr();
    lineNumber = SM.getSpellingLineNumber(omp_loc);

    if(isa<OMPExecutableDirective>(s)) process_omp_executable_directive(s);
    return true;
}

