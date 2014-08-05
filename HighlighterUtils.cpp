// Self
#include "HighlighterUtils.h"

// Clang
#include "clang/Rewrite/Core/Rewriter.h"

// Highlighter specific
#include "HTMLSupport.h"


namespace Highlighter
{

bool highlightArea(clang::Rewriter &rewriter,
                   const clang::SourceLocation &start,
                   const clang::SourceLocation &end,
                   const std::string &color)
{
    std::string startTag = html::HighlightingBeginTag(color);
    std::string endTag = html::HighlightingEndTag();

    if (rewriter.InsertTextBefore(start, startTag)) {
        return false;
    }

    if (rewriter.InsertTextAfterToken(end, endTag)) {
        return false;
    }

    return true;
}

bool highlightArea(clang::Rewriter &rewriter,
                   const clang::SourceRange &range,
                   const std::string &color)
{
    return highlightArea(rewriter, range.getBegin(), range.getEnd(), color);
}

}
