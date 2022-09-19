EXE = main
TEST = test

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# add objects needed to compile both main and test

OBJS = src/data.o  src/metadata.o src/graph.o src/DFS.o src/dijkstra.o src/IDDFS.o src/product_util.o

EXE_OBJS = $(OBJS) main.o

all: $(EXE)

SRC_DIR = src
$(EXE): $(EXE_OBJS)
	$(LD) $(EXE_OBJS) $(LDFLAGS) -o $(EXE)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

driver.o : driver.cpp
	$(CXX) $(CXXFLAGS) driver.cpp

# rules for making test suite
CPP_TEST = $(wildcard tests/*.cpp)
CPP_TEST += catch/catchmain.cpp
TEST_OBJS = $(OBJS) $(CPP_TEST:.cpp=.o)

$(TEST): $(TEST_OBJS)
	$(LD) $(TEST_OBJS) $(LDFLAGS) -o $(TEST)

catchmain.o: catch/catchmain.cpp
	$(CXX) $(CXXFLAGS) catch/catchmain.cpp

# Making other cpp files
$(SRC_DIR)/%.o: %.cpp | $(SRC_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	$(RM) $(EXE) *.o tests/*.o src/*.o