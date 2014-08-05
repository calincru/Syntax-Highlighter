#ifndef HIGHLIGHTERPPCALLBACKS_H__
#define HIGHLIGHTERPPCALLBACKS_H__

#include "clang/Lex/Preprocessor.h"
#include "clang/Rewrite/Core/Rewriter.h"


namespace clang
{
    class Token;
    class MacroDirective;
    class SourceRange;
    class MacroExpands;
}

namespace Highlighter
{

class HighlighterPPCallbacks : public clang::PPCallbacks
{
public:
    HighlighterPPCallbacks(clang::Rewriter &rewriter);

    virtual void MacroExpands(const clang::Token &MacroNameTok, const clang::MacroDirective *MD,
                              clang::SourceRange Range, const clang::MacroArgs *Args);
    virtual void SourceRangeSkipped(clang::SourceRange Range);

private:
    clang::Rewriter &m_rewriter;
};

}

#endif
