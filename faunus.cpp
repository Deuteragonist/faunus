#include <iostream>
#include <cstring>
#include <cassert>

#include <clang-c/Index.h>

const char* clangOpts[] = {"-x", "c++"};

static const inline bool isDebugBuild() { 
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

   if(isDebugBuild()) {
      std::cout << "got unitResult @" << unitResult << std::endl;
   }

   /* TODO: traverse like a boss */

   clang_disposeIndex(testIndex);
   return EXIT_SUCCESS;
}
