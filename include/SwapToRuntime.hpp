#ifndef SWAP_TO_RUNTIME_HFIWUEHF9W8HF98WHF
#define SWAP_TO_RUNTIME_HFIWUEHF9W8HF98WHF

#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/AST/RecursiveASTVisitor.h"

class SwapToRuntime{
    public:
        void from_static(clang::Rewriter& rewriter, clang::OMPScheduleClause* const clause);
        void from_dynamic(clang::Rewriter& rewriter, clang::OMPScheduleClause* const clause);
        void from_guided(clang::Rewriter& rewriter, clang::OMPScheduleClause* const clause);
        void from_auto(clang::Rewriter& rewriter, clang::OMPScheduleClause* const clause);
};

#endif //SWAP_TO_RUNTIME_HFIWUEHF9W8HF98WHF
