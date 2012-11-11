#include <iostream>
#include <cstring>
#include <cassert>

#include <clang/Basic/FileSystemOptions.h>
#include <clang/Basic/SourceManager.h>

using namespace clang;

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

   FileSystemOptions fsOpts;
   FileManager fm(fsOpts);
   //DiagnosticsEngine de;
   //SourceManager sm;

   if(isDebugBuild()) {
      std::cout << "attempting to open <" << argv[1] << "> ..." << std::endl;
   }

   return EXIT_SUCCESS;
}
