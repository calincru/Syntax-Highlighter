// Self
#include "HighlighterPPCallbacks.h"

// Clang
#include "clang/Tooling/Tooling.h"


namespace Highlighter
{

HighlighterPPCallbacks::HighlighterPPCallbacks(clang::Rewriter &rewriter) :
    m_rewriter(rewriter)
{
    // nothing to do
}

void HighlighterPPCallbacks::MacroExpands(const clang::Token &MacroNameTok,
                                          const clang::MacroDirective *MD,
                                          clang::SourceRange Range,
                                          const clang::MacroArgs *Args)
{
    // not implemented so far
}

void HighlighterPPCallbacks::SourceRangeSkipped(clang::SourceRange Range)
{
    // not implemented so far
}


}
