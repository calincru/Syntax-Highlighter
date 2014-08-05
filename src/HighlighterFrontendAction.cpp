// Self
#include "HighlighterFrontendAction.h"

// Clang
#include "clang/Frontend/CompilerInstance.h"

// Highlighter Specific
#include "HighlighterPPCallbacks.h"
#include "HighlighterASTConsumer.h"


namespace Highlighter
{

bool HighlighterFrontendAction::BeginInvocation(clang::CompilerInstance &CI) LLVM_OVERRIDE
{
    m_rewriter = clang::Rewriter(CI.getSourceManager(), CI.getLangOpts());
    return true;
}

clang::ASTConsumer *HighlighterFrontendAction::CreateASTConsumer(clang::CompilerInstance &CI,
                                                                 llvm::StringRef InFile) LLVM_OVERRIDE
{
    CI.getPreprocessor().addPPCallbacks(new HighlighterPPCallbacks(m_rewriter));
    return new HighlighterASTConsumer(CI.getASTContext(), m_rewriter);
}

}
