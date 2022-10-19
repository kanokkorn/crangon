CXX = clang++
CXXFLAGS = -std=c++17 -nostdlib -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic -g
LDFLAGS = -rtlib=compiler-rt -fuse-ld=lld
LDLIBS = -lm -pthread -I/usr/local/include/opencv4

.SUFFIXES: .cc

OBJ = process.o
BIN = crangon

all: ${OBJ} ${BIN}

#main.o : main.cc
#	${CXX} ${CXXFLAGS} -c $< ${LDLIBS}
process.o : process.cc
	${CXX} ${CXXFLAGS} -c $< ${LDLIBS}

${BIN}: process.o
	${CXX} ${LDFLAGS} ${OBJ} -o $@ ${LDLIBS}
clean:
	rm -rf *.o ${BIN}

.PHONY: all clean
