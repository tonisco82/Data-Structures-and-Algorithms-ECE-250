all:		openhtdriver orderedhtdriver

openhtdriver:	openhttest.cpp
		g++ -o openhtdriver -std=c++11 openhttest.cpp

orderedhtdriver:orderedhttest.cpp
		g++ -o orderedhtdriver -std=c++11 orderedhttest.cpp

run:		./openhtdriver
		./orderedhtdriver

clean:
		rm -f openhtdriver
		rm -f orderedhtdriver
