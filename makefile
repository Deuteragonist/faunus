CC=gcc

CXXFLAGS=$(shell llvm-config --cxxflags) -c -g
LDFLAGS=-lstdc++ -lm\
 -lclang -lclangAnalysis -lclangARCMigrate -lclangAST\
 -lclangASTMatchers -lclangBasic -lclangCodeGen\
 -lclangDriver -lclangEdit -lclangFrontend -lclangFrontendTool\
 -lclangLex -lclangParse -lclangRewriteCore\
 -lclangRewriteFrontend -lclangSema -lclangSerialization\
 -lclangStaticAnalyzerCheckers -lclangStaticAnalyzerCore\
 -lclangStaticAnalyzerFrontend -lclangTooling\
 $(shell llvm-config --ldflags)\
 $(shell llvm-config --libs)

OBJS=faunus.o
OUT=faunus

.PHONY: clean

$(OUT): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(OUT)

.cpp.o:
	$(CC) $(CXXFLAGS) $< 

clean:
	rm -f $(OBJS) $(OUT)

