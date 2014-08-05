// Self
#include "HighlighterASTConsumer.h"

// Clang
#include "clang/AST/ASTContext.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Lex/Preprocessor.h"

// Highlighter specific
#include "HighlighterASTVisitor.h"
#include "HTMLSupport.h"

#include <iostream>

namespace Highlighter
{

HighlighterASTConsumer::HighlighterASTConsumer(clang::ASTContext &ctx,
                                               clang::Rewriter &rewriter) :
    m_context(ctx),
    m_rewriter(rewriter),
    m_visitor(HighlighterASTVisitor(ctx, rewriter))
{
    // nothing to do
}

HighlighterASTConsumer::~HighlighterASTConsumer()
{
    // nothing to do
}

void HighlighterASTConsumer::HandleTranslationUnit(clang::ASTContext &ctx)
{
    escapeHTML(ctx);
    highlightTranslationUnit(ctx);
    dumpHighlightedTranslationUnit(ctx);
}

std::string HighlighterASTConsumer::getMainFilename(const clang::SourceManager &SM)
{
    return SM.getFilename(SM.getLocForStartOfFile(SM.getMainFileID()));
}

void HighlighterASTConsumer::dumpHighlightedTranslationUnit(clang::ASTContext &ctx)
{
    clang::SourceManager &SM = ctx.getSourceManager();

    std::string errors;
    std::string filename = getMainFilename(SM) + ".html";
    llvm::raw_fd_ostream output(filename.c_str(), errors);

    // Add HTML prologue
    output << html::Prologue(filename);

    // Add highlighted code
    const clang::RewriteBuffer *rewritten = m_rewriter.getRewriteBufferFor(SM.getMainFileID());
    if (rewritten)
        output << std::string(rewritten->begin(), rewritten->end());
    else
        output << SM.getBufferData(SM.getMainFileID());

    // Add HTML epilogue
    output << html::Epilogue();

    output.close();
    // Error-checking would be nice...
}

void HighlighterASTConsumer::highlightTranslationUnit(clang::ASTContext &ctx)
{
    m_visitor.TraverseTranslationUnitDecl(ctx.getTranslationUnitDecl());
}

void HighlighterASTConsumer::escapeHTML(clang::ASTContext &ctx)
{
    const clang::SourceManager &SM = ctx.getSourceManager();
    const clang::LangOptions &LOpts = ctx.getLangOpts();
    const clang::FileID fileID = SM.getMainFileID();
    const llvm::MemoryBuffer *fileBuffer = SM.getBuffer(fileID);

    // This creates a "raw" lexer (one that doesn't have a preprocessor associated with it).
    // It will not enter #include'd files and it will not perform macro expansion.
    // We will use LexFromRawLexer to get tokens one by one from it.
    clang::Lexer L(fileID, fileBuffer, SM, LOpts);

    clang::Token Tok;
    std::string escaped;
    bool isDifferent;
    for (L.LexFromRawLexer(Tok); Tok.isNot(clang::tok::eof); L.LexFromRawLexer(Tok)) {
        escaped = html::EscapeText(clang::Lexer::getSpelling(Tok, SM, LOpts), isDifferent);
        if (isDifferent)
            m_rewriter.ReplaceText(Tok.getLocation(), Tok.getLength(), escaped);
    }
}

}
