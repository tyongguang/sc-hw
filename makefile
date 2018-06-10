CXX			= g++

SOURCES 	= $(wildcard *.cpp)

OBJECTS		= $(SOURCES:%.cc=%.o)

EXECUTABLE 	= test

CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic -ldl -g -ljsoncpp

all:
	$(CXX) $(SOURCES) $(CXXLIB) $(CXXFLAGS)

%.o:
	$(CXX) $(CXXFLAGS) -c $*.cpp

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(SUBMIT_FILE)
