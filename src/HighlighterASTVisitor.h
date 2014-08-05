#ifndef HIGHLIGHTERASTVISITOR_H__
#define HIGHLIGHTERASTVISITOR_H__

#include "clang/AST/RecursiveASTVisitor.h"

namespace clang
{
    class ASTContext;
    class Rewriter;
    class IntegerLiteral;
    class TypeLoc;
    class DeclRefExpr;
    class SourceLocation;
}

namespace Highlighter
{

class HighlighterASTVisitor : public clang::RecursiveASTVisitor<HighlighterASTVisitor>
{
public:
    HighlighterASTVisitor(const clang::ASTContext &ctx, clang::Rewriter &rewriter);
    ~HighlighterASTVisitor();

    bool VisitIntegerLiteral(clang::IntegerLiteral *S);
    bool VisitTypeLoc(clang::TypeLoc TL);
    bool VisitDeclRefExpr(clang::DeclRefExpr *S);

private:
    bool isInMainFile(const clang::SourceLocation &loc);

    const clang::ASTContext &m_context;
    clang::Rewriter &m_rewriter;
};

}

#endif
