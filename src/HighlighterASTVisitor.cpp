// Self
#include "HighlighterASTVisitor.h"

// Clang
#include "clang/AST/ASTContext.h"
#include "clang/Rewrite/Core/Rewriter.h"

// Highlighter specific
#include "HighlighterUtils.h"


namespace Highlighter
{

HighlighterASTVisitor::HighlighterASTVisitor(const clang::ASTContext &ctx,
                                             clang::Rewriter &rewriter) :
    m_context(ctx),
    m_rewriter(rewriter)
{
    // nothing to do
}

HighlighterASTVisitor::~HighlighterASTVisitor()
{
    // nothing to do
}

bool HighlighterASTVisitor::VisitIntegerLiteral(clang::IntegerLiteral *S)
{
    // This check is very important - a translation unit consists of several
    // files: the main file (the source that we provided as input) and all
    // the files #include'd by it.
    // We are only interested in the main file, so there is no point in
    // processing all the included headers (which are in many cases way
    // larger than the main file).
    if (!isInMainFile(S->getLocStart())) {
        return true;
    }

    highlightArea(m_rewriter, S->getSourceRange(), std::string("red"));
    return true;
}

bool HighlighterASTVisitor::VisitTypeLoc(clang::TypeLoc TL)
{
    if (!isInMainFile(TL.getLocStart())) {
        return true;
    }

    // TODO: Skip function types - this means FunctionProto and
    // FunctionNoProto. Can be used the getTypeLocClass method to
    // find out what type we're dealing with.
    highlightArea(m_rewriter, TL.getSourceRange(), std::string("red"));
    return true;

}

bool HighlighterASTVisitor::VisitDeclRefExpr(clang::DeclRefExpr *S)
{
    if (!isInMainFile(S->getLocStart())) {
        return true;
    }

    // TODO: Highlight the range only if this references a parameter. We
    // can get this information by first getting the declaration
    // referenced by this expression, and then checking its kind.
    return true;
}

bool HighlighterASTVisitor::isInMainFile(const clang::SourceLocation &loc)
{
    const clang::SourceManager &SM = m_context.getSourceManager();
    return SM.getFileID(loc) == SM.getMainFileID();
}

}
