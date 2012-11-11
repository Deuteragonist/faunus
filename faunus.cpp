#include <iostream>
#include <cstring>
#include <clang-c/Index.h>
#include <cassert>

const inline bool isDebugBuild() { 
   #ifndef NDEBUG
      return true;
   #else
      return false;
   #endif
}

int main(int argc, char** argv) {
   if( argc != 2 ) {
      std::cerr << "usage: " << argv[0] << " <filename.cpp>" << std::endl;
      return EXIT_FAILURE;
   }

   if(isDebugBuild()) {
      std::cout << "attempting to open <" << argv[1] << "> ..." << std::endl;
   }

   CXIndex index = 0;
   CXIndexAction indexAction = clang_IndexAction_create(index);
   CXTranslationUnit thisUnit = clang_createTranslationUnitFromSourceFile(
      index,
      (const char*) argv[1],
      0,
      NULL,
      0,
      NULL 
   );  

   if(isDebugBuild()) {
      std::cout << "created translation unit @" << thisUnit << std::endl;
   }

   return EXIT_SUCCESS;
}
