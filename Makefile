# Makefile written by Rosa Vitiello
# Compiles SixDegrees for HW 5
# Last Modified: Nov. 15, 2018

CXX      = clang++
CXXFLAGS = -g -Wall -Wextra -std=c++11
LDFLAGS  = -g

sixdegrees: main.o LinkedList.o Actor.o Stack.o Queue.o Graph.o SixDegrees.o
	${CXX} ${CXXFLAGS} -o sixdegrees main.o LinkedList.o Actor.o Stack.o Queue.o Graph.o SixDegrees.o

LinkedList.o: LinkedList.cpp LinkedList.h
	${CXX} ${CXXFLAGS} -c -o LinkedList.o LinkedList.cpp

Actor.o: Actor.cpp Actor.h
	${CXX} ${CXXFLAGS} -c -o Actor.o Actor.cpp

Stack.o: Stack.cpp Stack.h
	${CXX} ${CXXFLAGS} -c -o Stack.o Stack.cpp

Queue.o: Queue.cpp Queue.h
	${CXX} ${CXXFLAGS} -c -o Queue.o Queue.cpp

Graph.o: Graph.cpp Graph.h
	${CXX} ${CXXFLAGS} -c -o Graph.o Graph.cpp

SixDegrees.o: SixDegrees.cpp SixDegrees.h
	${CXX} ${CXXFLAGS} -c -o SixDegrees.o SixDegrees.cpp

clean:
	rm -rf sixdegrees *.o *.dSYM