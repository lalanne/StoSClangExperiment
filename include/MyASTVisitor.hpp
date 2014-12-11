
#ifndef MY_AST_VISITOR_98U9EW8FU9QW8UEF
#define MY_AST_VISITOR_98U9EW8FU9QW8UEF

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include <iostream>
#include <sstream>

class MyASTVisitor : public clang::RecursiveASTVisitor<MyASTVisitor> {
    public:
        MyASTVisitor(clang::Rewriter &R);

        bool VisitStmt(clang::Stmt *s);

    private:
        void swap_static_to_runtime(clang::OMPScheduleClause* const clause);
        void swap_dynamic_to_runtime(clang::OMPScheduleClause* const clause);
        void swap_guided_to_runtime(clang::OMPScheduleClause* const clause);
        void swap_auto_to_runtime(clang::OMPScheduleClause* const clause);

    private:
        /*This 2 fields are used for controlling the visit to OMP directives
         * that for some reason clang is visiting twice*/
        unsigned int lineNumber;
        unsigned int ompDirectiveLineNumberCache;
        /*Handles Rewriting of the source code*/
        clang::Rewriter &myRewriter;
};

#endif //MY_AST_VISITOR_98U9EW8FU9QW8UEF
