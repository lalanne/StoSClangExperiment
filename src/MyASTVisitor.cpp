
#include "MyASTVisitor.hpp"

using namespace clang;
using namespace std;

MyASTVisitor::MyASTVisitor(Rewriter &R) : lineNumber{0},
                                        ompDirectiveLineNumberCache{0},
                                        myRewriter{R}{}

void MyASTVisitor::process_omp_schedule_clause(OMPClause* const clause){
    OMPScheduleClause* const scheduleClause = cast<OMPScheduleClause>(clause);
    switch(scheduleClause->getScheduleKind()){
        case OMPC_SCHEDULE_static:
        {
            swapToRuntime.from_static(myRewriter, scheduleClause);
        }
        break;

        case OMPC_SCHEDULE_dynamic:
        {
            swapToRuntime.from_dynamic(myRewriter, scheduleClause);
        }
        break;

        case OMPC_SCHEDULE_guided:
        {
            swapToRuntime.from_guided(myRewriter, scheduleClause);
        }
        break;

        case OMPC_SCHEDULE_auto:
        {
            swapToRuntime.from_auto(myRewriter, scheduleClause);
        }
        break;

        case OMPC_SCHEDULE_unknown: //should throw here!
        case OMPC_SCHEDULE_runtime: //no action needed!
        case NUM_OPENMP_SCHEDULE_KINDS: //to avoid warning!
        break;
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

