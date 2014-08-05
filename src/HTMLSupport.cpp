#include "HTMLSupport.h"

#include "clang/Lex/Token.h"
#include "llvm/Support/raw_ostream.h"

namespace html {

std::string Prologue(const std::string &title)
{
    return  "<html>\n"
            "\t<head>\n"
            "\t\t<title>" + title + "</title>\n"
            "\t</head>\n"
            "\t<body>\n"
            "\t\t<pre>\n";
}

std::string Epilogue(void)
{
    return  "\t\t</pre>\n"
            "\t</body>\n"
            "</html>\n";
}

std::string HighlightingBeginTag(const std::string &color)
{
    return "<span style=\"color: " + color + "\">";
}

std::string HighlightingEndTag(void)
{
    return "</span>";
}

std::string EscapeText(const std::string &text, bool &isDifferent)
{
    isDifferent = false;

    unsigned len = text.size();
    std::string Str;
    llvm::raw_string_ostream os(Str);

    for (unsigned i = 0 ; i < len; ++i) {
        char c = text[i];
        switch (c) {
        default:
            os << c;
            break;
        case '<':
            os << "&lt;";
            isDifferent = true;
            break;
        case '>':
            os << "&gt;";
            isDifferent = true;
            break;
        case '&':
            os << "&amp;";
            isDifferent = true;
            break;
        }
    }

    return os.str();
}

} // namespace html
