# SPDX-License-Identifier: BSD-3-Clause

VERSION 	= 0
SUBVERSION 	= 2
PATCHLEVEL 	= 0

PREFIX = /usr/local/bin

# looking for `clang` first, then `gcc`
CXX= c++
CXXFLAGS= -std=c++17 -libstdc++ -Wall -Wextra -fno-common \
	-Wno-c11-extensions -Wno-unused-command-line-argument \
	-pedantic -g -v

INCLUDE_DIRS = -I/usr/local/include/opencv4/opencv2\
               -I /usr/include/fmt\
               -I/usr/include/spdlog\

LIBRARY_DIRS = -L/usr/local/lib/\
	
LDFLAGS= -fuse-ld=lld
LDLIBS= -lm -lc -pthread -fopenmp -lopencv_core \
        -lopencv_imgproc -lopencv_highgui -lopencv_objdetect
CV = `pkg-config --cflags --libs opencv4`

.SUFFIXES: .cc

SRC != 	ls src/*.cc
OBJ	= 	crangc.o
BIN = 	crangc

all: ${OBJ} ${BIN}

${OBJ} : ${SRC}
	${CXX} ${CXXFLAGS} -c $< ${LDLIBS} ${CV} ${INCLUDE_DIRS}

${BIN}: ${OBJ}
	${CXX} ${LDFLAGS} ${OBJ} -o $@ ${LDLIBS} ${CV} ${INCLUDE_DIRS}

install:
	cp ${BIN} /usr/local/bin/${BIN}
clean:
	rm -rf *.o ${BIN}

.PHONY: all clean
