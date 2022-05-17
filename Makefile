DEBUG = 0
USE_VID = 0
USE_ZMQ = 0
USE_SQL = 0

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

ifeq ($(DEBUG), 1)
	CXXFLAGS += -DDEBUG -O3 -g
endif

ifeq ($(USE_VID), 1)
	CXXFLAGS += -DUSE_VID
endif

ifeq ($(USE_ZMQ), 1)
	CXXFLAGS += -DUSE_ZMQ
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
