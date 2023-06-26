PREFIX ?= /usr/local/bin

CXX = clang++
CXXFLAGS = -std=c++14 -libstdc++ -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic -g
LDFLAGS = -fuse-ld=lld
LDLIBS = -lm -lc -pthread -I /usr/local/include/opencv4/ -fopenmp
CV = `pkg-config --cflags --libs opencv4`

.SUFFIXES: .cc

SRC != ls *.cc
OBJ = ${SRC:.cc=.o}
BIN = crangon

all: ${OBJ} ${BIN}

${OBJ} : ${SRC}
	${CXX} ${CXXFLAGS} -c $< ${LDLIBS} ${CV}

${BIN}: ${OBJ}
	${CXX} ${LDFLAGS} ${OBJ} -o $@ ${LDLIBS} ${CV}

clean:
	rm -rf *.o ${BIN}

.PHONY: all clean
