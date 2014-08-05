#ifndef HIGHLIGHTERFRONTEDACTION_H__
#define HIGHLIGHTERFRONTEDACTION_H__

#include "clang/Tooling/Tooling.h"
#include "clang/Rewrite/Core/Rewriter.h"

namespace clang
{
    class ASTConsumer;
    class CompilerInstance;
    class StringRef;
}

namespace Highlighter
{

class HighlighterFrontendAction : public clang::ASTFrontendAction
{
    virtual bool BeginInvocation(clang::CompilerInstance &CI) LLVM_OVERRIDE;
    virtual clang::ASTConsumer *CreateASTConsumer(clang::CompilerInstance &CI,
                                                  llvm::StringRef InFile) LLVM_OVERRIDE;
private:
    clang::Rewriter m_rewriter;
};

}

#endif
