#ifndef HIGHLIGHTERUTILS_H__
#define HIGHLIGHTERUTILS_H__

#include <string>


namespace clang
{
    class Rewriter;
    class SourceLocation;
    class SourceRange;
}

namespace Highlighter
{

// Use a rewriter to surround a certain range in the original source code with
// the tags needed for highlighting.
bool highlightArea(clang::Rewriter &rewriter,
                   const clang::SourceLocation &start,
                   const clang::SourceLocation &end,
                   const std::string &color);

bool highlightArea(clang::Rewriter &rewriter,
                   const clang::SourceRange &range,
                   const std::string &color);

}

#endif
