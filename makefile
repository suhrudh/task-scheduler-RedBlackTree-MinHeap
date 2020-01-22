

CXX = g++
CXXFLAGS = -Wall -g

risingCity: risingCity.o structure.o
        $(CXX) $(CXXFLAGS) -o risingCity risingCity.o structure.o

#creating objects from cpp and header files

risingCity.o: risingCity.cpp  Nodes.h Building.h
        $(CXX) $(CXXFLAGS) -c risingCity.cpp


structure.o: structure.cpp structure.h Nodes.h Building.h
        $(CXX) $(CXXFLAGS) -c structure.cpp