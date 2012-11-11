#include <iostream>
#include <cstring>
#include <cassert>

#include <clang-c/Index.h>

const char* clangOpts[] = {"-x", "c++"};

static const bool isDebugBuild(); 
static unsigned getDefaultParsingOptions();
enum CXChildVisitResult ASTWalker(CXCursor cursor, CXCursor parent, CXClientData client_data);

int main(int argc, char** argv) {
   if( argc != 2 ) {
      std::cerr << "usage: " << argv[0] << " <filename.cpp>" << std::endl;
      return EXIT_FAILURE;
   }

   CXIndex testIndex = clang_createIndex(1, 1);

   if(isDebugBuild()) {
      std::cout << "attempting to open <" << argv[1] << "> ..." << std::endl;
   }

   CXTranslationUnit unitResult = clang_parseTranslationUnit( testIndex,
      argv[1],
      (const char *const *) clangOpts,
      2,
      0,
      0,
      getDefaultParsingOptions()
   );

   CXCursor unitCursor = clang_getTranslationUnitCursor(unitResult);

   if(isDebugBuild()) {
      std::cout << "got unitResult @" << unitResult << std::endl;
   }

   clang_visitChildren( unitCursor, ASTWalker, NULL);

   clang_disposeTranslationUnit(unitResult);
   clang_disposeIndex(testIndex);
   return EXIT_SUCCESS;
}

static const bool isDebugBuild() { 
   #ifndef NDEBUG
      return true;
   #else
      return false;
   #endif
}

static unsigned getDefaultParsingOptions() {
   unsigned options = CXTranslationUnit_DetailedPreprocessingRecord;

   if (getenv("CINDEXTEST_EDITING")) {
      options |= clang_defaultEditingTranslationUnitOptions();
   }

   if (getenv("CINDEXTEST_COMPLETION_CACHING")) {
      options |= CXTranslationUnit_CacheCompletionResults;
   }
  
  return options;
}

enum CXChildVisitResult ASTWalker(CXCursor cursor, CXCursor parent, CXClientData client_data) {
   std::cout << cursor.kind << " " << cursor.data << " " << cursor.data << std::endl;

   return CXChildVisit_Recurse;
}


