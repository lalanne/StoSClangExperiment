
#include "SwapToRuntime.hpp"

using namespace clang;

const unsigned int NUMBER_OF_CHARACTERS_STATIC_SCHEDULE = 6;
const unsigned int NUMBER_OF_CHARACTERS_DYNAMIC_SCHEDULE = 7;
const unsigned int NUMBER_OF_CHARACTERS_GUIDED_SCHEDULE = 6;
const unsigned int NUMBER_OF_CHARACTERS_AUTO_SCHEDULE = 4;

void SwapToRuntime::from_static(Rewriter& rewriter, OMPScheduleClause* const clause){
    rewriter.RemoveText(clause->getScheduleKindLoc(), 
                        NUMBER_OF_CHARACTERS_STATIC_SCHEDULE);
    rewriter.InsertText(clause->getScheduleKindLoc(), 
                        "runtime", 
                        true,
                        true);
}

void SwapToRuntime::from_dynamic(Rewriter& rewriter, OMPScheduleClause* const clause){
    rewriter.RemoveText(clause->getScheduleKindLoc(), 
                        NUMBER_OF_CHARACTERS_DYNAMIC_SCHEDULE);
    rewriter.InsertText(clause->getScheduleKindLoc(), 
                        "runtime", 
                        true,
                        true);
}

void SwapToRuntime::from_guided(Rewriter& rewriter, OMPScheduleClause* const clause){
    rewriter.RemoveText(clause->getScheduleKindLoc(), 
                        NUMBER_OF_CHARACTERS_GUIDED_SCHEDULE);
    rewriter.InsertText(clause->getScheduleKindLoc(), 
                        "runtime", 
                        true,
                        true);
}

void SwapToRuntime::from_auto(Rewriter& rewriter, OMPScheduleClause* const clause){
    rewriter.RemoveText(clause->getScheduleKindLoc(), 
                        NUMBER_OF_CHARACTERS_AUTO_SCHEDULE);
    rewriter.InsertText(clause->getScheduleKindLoc(), 
                        "runtime", 
                        true,
                        true);
}

