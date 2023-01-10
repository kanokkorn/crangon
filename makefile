CXX = clang++
CXXFLAGS = -std=c++14 -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic -g
LDFLAGS = -fuse-ld=lld
LDLIBS = -lm -lc -pthread -I /usr/local/include/opencv4/
CV = `shell pkg-config --cflags --libs opencv4`

.SUFFIXES: .cc

SRC = main.cc
OBJ = main.o
BIN = crangon

all: ${OBJ} ${BIN}

${OBJ} : ${SRC}
	${CXX} ${CXXFLAGS} -c $< ${LDLIBS} ${CV}

${BIN}: ${OBJ}
	${CXX} ${LDFLAGS} ${OBJ} -o $@ ${LDLIBS} ${CV}
clean:
	rm -rf *.o ${BIN}

.PHONY: all clean
