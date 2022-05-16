USE_CAM = 0
USE_VID = 0
USE_ZMQ = 0
USE_SQL = 0

CXX = clang++
CXXFLAGS = -std=c++0x -Wall -Wextra -fno-common\
					 -Wno-c11-extensions -Wno-unused-command-line-argument\
					 -pedantic -O3 -g
LD = -fuse-ld=lld -rtlib=compiler-rt
LDLIBS = -lm -pthread -ljsoncpp -lspdlog
OPENCV = $(shell pkg-config --cflags --libs opencv4)

SRC = $(wildcard *.cc)
OBJ = $(SRC:.cc=.o)
BIN = crangon

ifeq ($(USE_CAM), 1)
	CXXFLAGS += -DUSE_CAM
endif

ifeq ($(USE_VID), 1)
	CXXFLAGS += -DUSE_VID
endif

ifeq ($(USE_ZMQ), 1)
	CXXFLAGS += -DUSE_SRV
	LDLIBS += -lzmq
endif

ifeq ($(USE_SQL), 1)
	CXXFLAGS += -DUSE_SQL
	LDLIBS += -lsqlite3
endif

all: $(OBJ) $(BIN)
.PHONY: all clean

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -c $(OPENCV)
$(BIN): $(OBJ)
	$(CXX) $(LD) $^ -o $@ $(OPENCV) $(LDLIBS)
clean:
	$(RM) $(OBJ) $(BIN)
