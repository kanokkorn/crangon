# SPDX-License-Identifier: BSD-3-Clause

VERSION 	= 0
SUBVERSION 	= 2
PATCHLEVEL 	= 0

PREFIX = /usr/local/bin

# looking for `clang` first, then `gcc`
CXX= c++
CXXFLAGS= -std=c++11 -libstdc++ -Wall -Wextra -fno-common \
	-Wno-c11-extensions -Wno-unused-command-line-argument \
	-pedantic -g -v

INCLUDE_DIRS = -I/usr/local/include/opencv4/opencv2
LIBRARY_DIRS = -L/usr/local/lib/
	
LDFLAGS= -fuse-ld=lld
LDLIBS= -lm -lc -pthread -fopenmp -lopencv_core \
        -lopencv_imgproc -lopencv_highgui -lopencv_objdetect
CV = `pkg-config --cflags --libs opencv4`

.SUFFIXES: .cc

SRC != 	ls *.cc
OBJ	= 	crangc.o hw_check.o script.o
BIN = 	crangc

all: ${OBJ} ${BIN}

${OBJ} : ${SRC}
	${CXX} ${CXXFLAGS} -c $< ${LDLIBS} ${CV}

${BIN}: ${OBJ}
	${CXX} ${LDFLAGS} ${OBJ} -o $@ ${LDLIBS} ${CV}

install:
	cp ${BIN} /usr/local/bin/${BIN}
clean:
	rm -rf *.o ${BIN}

.PHONY: all clean
