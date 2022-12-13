CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic -g
LDFLAGS = -fuse-ld=lld
LDLIBS = -lm -pthread -I/usr/local/include/opencv4

.SUFFIXES: .cc

SRC != ls *.cc
OBJ = ${SRC:.cc=.o}
BIN = crangon

all: ${OBJ} ${BIN}

${OBJ} : ${SRC}
	${CXX} ${CXXFLAGS} -c $< ${LDLIBS}

${BIN}: ${OBJ}
	${CXX} ${LDFLAGS} ${OBJ} -o $@ ${LDLIBS}
clean:
	rm -rf *.o ${BIN}

.PHONY: all clean
