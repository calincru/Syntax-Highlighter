// Clang
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

// Highlighter specific
#include "HighlighterFrontendAction.h"


int main(int argc, const char **argv)
{
    clang::tooling::CommonOptionsParser OptionsParser(argc, argv);
    clang::tooling::ClangTool Tool(OptionsParser.getCompilations(),
                                   OptionsParser.getSourcePathList());

    return Tool.run(clang::tooling::newFrontendActionFactory<Highlighter::HighlighterFrontendAction>());
}
