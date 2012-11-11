CC=gcc
CLANG_INSTALL_DIR=/gpfs/home/tbs5065/local
CLANG_INCLUDE_DIR=$(CLANG_INSTALL_DIR)/include
CLANG_LIB_DIR=$(CLANG_INSTALL_DIR)/lib

CXXFLAGS=-I $(CLANG_INCLUDE_DIR) -c -g
LDFLAGS=-lstdc++ -lm -L $(CLANG_LIB_DIR) -lclang

OBJS=faunus.o
OUT=faunus

.PHONY: clean

$(OUT): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(OUT)

.cpp.o:
	$(CC) $(CXXFLAGS) $< 

clean:
	rm -f $(OBJS) $(OUT)
