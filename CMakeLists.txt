project(Highlighter)

cmake_minimum_required(VERSION 2.8)

# YouCompleteMe vim plugin needs this in order to generate its
# compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Variables that describe the LLVM we're working with
set(LLVM_CFLAGS CACHE STRING "Additional compilation flags needed by LLVM (you can get them with llvm-config --cxxflags)")
set(LLVM_LDFLAGS CACHE STRING "Additional link flags needed by LLVM (you can get them with llvm-config --ldflags)")

if (NOT LLVM_CFLAGS OR NOT LLVM_LDFLAGS)
    message(WARNING "Are you sure you shouldn't pass any LLVM flags?")
endif ()

# The libraries that we need
set(LLVM_LIBS
    clangFrontend clangParse clangRewriteCore clangSema
    clangEdit clangLex clangSerialization clangAnalysis clangDriver clangAST clangBasic
    clangTooling LLVMTransformUtils LLVMCore LLVMMCParser LLVMMC LLVMBitReader
    LLVMOption LLVMSupport)

# C flags
add_definitions(${LLVM_CFLAGS})
add_definitions( -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS )

# Define our executable
add_executable(Highlighter
    HighlighterASTConsumer.cpp
    HighlighterASTVisitor.cpp
    HighlighterFrontendAction.cpp
    HighlighterPPCallbacks.cpp
    HighlighterUtils.cpp
    HTMLSupport.cpp
    HTMLSupport.h
    main.cpp
    )

# Specify libraries that need to be linked into our executable + additional
# linker flags
target_link_libraries(Highlighter ${LLVM_LIBS} ${LLVM_LDFLAGS})
