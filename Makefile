CXX = clang++
CXXFLAGS = -std=c++14 -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic
LD = -fuse-ld=lld -rtlib=compiler-rt
LDLIBS = -lm -pthread -ljsoncpp -lspdlog
OPENCV = $(shell pkg-config --cflags --libs opencv4)

SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
BIN = crangon

all: $(OBJ) $(BIN)
.PHONY: all clean

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -c $(OPENCV)
$(BIN): $(OBJ)
	$(CXX) $(LD) $^ -o $@ $(OPENCV) $(LDLIBS)
clean:
	$(RM) $(OBJ) $(BIN)
