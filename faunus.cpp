#include <iostream>
#include <cstring>
#include <cassert>

#include <clang-c/Index.h>

const char* clangOpts[] = {"-x", "c++", NULL};

static const bool isDebugBuild(); 
static unsigned getDefaultParsingOptions();
enum CXChildVisitResult ASTWalker(CXCursor cursor, CXCursor parent, CXClientData client_data);

int main(int argc, char** argv) {
   if( argc != 2 ) {
      std::cerr << "usage: " << argv[0] << " <filename.cpp>" << std::endl;
      return EXIT_FAILURE;
   }

   int clangOptsCount = 0;
   while(clangOpts[++clangOptsCount]);

   CXIndex testIndex = clang_createIndex(1, 1);

   if(isDebugBuild()) {
      std::cout << "attempting to open <" << argv[1] << "> ..." << std::endl;
   }

   CXTranslationUnit unitResult = clang_parseTranslationUnit( testIndex,
      argv[1],
      (const char *const *) clangOpts,
      clangOptsCount,
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
   CXString cursorDisplayName = clang_getCursorDisplayName(cursor);
   CXString cursorSpelling = clang_getCursorSpelling(cursor);

   /* review http://clang.llvm.org/doxygen/group__CINDEX.html#gaaccc432245b4cd9f2d470913f9ef0013 */

   std::cout 
      << clang_getCString(cursorDisplayName) << " "
      << clang_getCString(cursorSpelling) << std::endl
      << cursor.kind << " " << cursor.data << " " << cursor.data << std::endl;

   clang_disposeString(cursorSpelling);
   clang_disposeString(cursorDisplayName);

   return CXChildVisit_Recurse;
}

