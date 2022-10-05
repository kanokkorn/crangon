CXX = clang++
CXXFLAGS = -std=c++17 -nostdlib -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic -g
LDFLAGS = -fuse-ld=lld -rtlib=compiler-rt
LDLIBS = -lm -pthread -ljsoncpp -lspdlog

# pkg-config will be remove when we know how to build on FreeBSD
OPENCV = `pkg-config --cflags --libs opencv4`
#OPENCV = -I/include

.SUFFIXES: .cc

SRC = main.cc process.cc
OBJ = main.o process.o
BIN = crangon

all: ${OBJ} ${BIN}

${OBJ}: ${SRC}
	${CXX} ${CXXFLAGS} -c $< ${OPENCV}
${BIN}: ${OBJ}
	${CXX} ${LDFLAGS} ${OBJ} -o $@ ${OPENCV} ${LDLIBS}
clean:
	rm -rf *.o ${BIN}

.PHONY: all clean
