# written by Lior Trachtman: 211791041
# EMAIL: lior16122000@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
SFML_INCLUDE_DIR = /usr/local/include
SFML_LIB_DIR = /usr/local/lib
LDFLAGS = -L$(SFML_LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=99

SRCS = Demo.cpp Test.cpp
HDRS = Node.hpp Tree.hpp Complex.hpp Iterator.hpp TreeDrawer.hpp

all: tree test

tree: Demo.o
	$(CXX) $(CXXFLAGS) -o tree Demo.o $(LDFLAGS)

test: Test.o
	$(CXX) $(CXXFLAGS) -o test Test.o $(LDFLAGS)

Demo.o: Demo.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE_DIR) -c Demo.cpp

Test.o: Test.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -I$(SFML_INCLUDE_DIR) -c Test.cpp

clean:
	rm -f *.o tree test

tidy:
	clang-tidy $(SRCS) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind_test: test
	valgrind $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

valgrind_tree: tree
	valgrind $(VALGRIND_FLAGS) ./tree

.PHONY: all clean tidy valgrind_test valgrind_tree
