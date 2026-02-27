CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -I../include

.PHONY: default
default: main

main: main.o tree.o node.o folder.o file.o
	$(CXX) $(CXXFLAGS) -o main main.o tree.o node.o folder.o file.o

main.o: ../src/main.cpp ../include/tree.h
	$(CXX) $(CXXFLAGS) -c ../src/main.cpp

tree.o: ../src/tree.cpp ../include/tree.h
	$(CXX) $(CXXFLAGS) -c ../src/tree.cpp

node.o: ../src/tree.cpp ../include/node.h
	$(CXX) $(CXXFLAGS) -c ../src/node.cpp

folder.o: ../src/folder.cpp ../include/folder.h ../include/node.h
	$(CXX) $(CXXFLAGS) -c ../src/folder.cpp

file.o: ../src/file.cpp ../include/file.h ../include/node.h
	$(CXX) $(CXXFLAGS) -c ../src/file.cpp

.PHONY: clean
clean:
	rm -f *.o main

.PHONY: all
all: clean main