USE_CAM = 0
USE_VID = 0
GUI_CLIENT = 0
SQDB = 0

CXX = clang++
CXXFLAGS = -std=c++0x -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic -O3 -g
LD = -fuse-ld=lld -rtlib=compiler-rt
LDLIBS = -lm -lzmq -pthread -ljsoncpp -lspdlog -lsqlite3
OPENCV = $(shell pkg-config --cflags --libs opencv4)

SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
BIN = crangon

all: $(OBJ) $(BIN)
.PHONY: all clean

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -c $(OPENCV)
$(BIN): $(OBJ)
	$(CXX) $^ -o $@ $(OPENCV) $(LDLIBS)
clean:
	$(RM) $(OBJ) $(BIN)
