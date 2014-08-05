#ifndef HIGHLIGHTERASTCONSUMER_H__
#define HIGHLIGHTERASTCONSUMER_H__

#include "clang/AST/ASTConsumer.h"
#include "HighlighterASTVisitor.h"

namespace clang
{
    class ASTContext;
    class Rewriter;
    class SourceManager;
}

namespace Highlighter
{

class HighlighterASTConsumer : public clang::ASTConsumer
{
public:
    HighlighterASTConsumer(clang::ASTContext &ctx, clang::Rewriter &rewriter);
    ~HighlighterASTConsumer();

    virtual void HandleTranslationUnit(clang::ASTContext &ctx);

private:
    std::string getMainFilename(const clang::SourceManager &SM);
    void dumpHighlightedTranslationUnit(clang::ASTContext &ctx);
    void highlightTranslationUnit(clang::ASTContext &ctx);
    void escapeHTML(clang::ASTContext &ctx);

    const clang::ASTContext &m_context;
    clang::Rewriter &m_rewriter;
    HighlighterASTVisitor m_visitor;
};

}

#endif
