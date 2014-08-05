#ifndef HTMLSUPPORT_H
#define HTMLSUPPORT_H

#include <string>

namespace clang
{
    class Token;
}

namespace html
{

// Get the HTML code that needs to appear before and respectively after the
// highlighted source code (you can provide your own title)
std::string Prologue(const std::string &title);
std::string Epilogue(void);

// Get the tags needed for highlighting with a given color
std::string HighlightingBeginTag(const std::string &color);
std::string HighlightingEndTag(void);

// Escape problematic HTML characters (such as '<').
// <isDifferent> is set to false if there was nothing to escape.
std::string EscapeText(const std::string &text, bool &isDifferent);

} // namespace html

#endif // HTMLSUPPORT_H
