CXX = clang++
CXXFLAGS = -std=c++14 -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic
LD = -fuse-ld=lld -rtlib=compiler-rt
LDLIBS = -lm -pthread -ljsoncpp -lspdlog
OPENCV = pkg-config --cflags --libs opencv4

.SUFFIXES: .cc

SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
BIN = crangon

all: $(OBJ) $(BIN)

$(OBJ): $(SRC)
	${CXX} ${CXXFLAGS} $< -c ${OPENCV}
${BIN}: main.o
	${CXX} ${LD} $^ -o $@ ${OPENCV} ${LDLIBS}
clean:
	rm -rf ${OBJ} ${BIN}

.PHONY: all clean
