CXX			= g++

SOURCES 	= test_main.cpp ../Dynamic_List.cpp ../Dynamic_Map.cpp ../Dynamic_Object_Builder.cpp ../Dynamic_String.cpp

OBJECTS		= $(SOURCES:%.cc=%.o)

EXECUTABLE 	= test

CXXFLAGS = -std=c++11 -Wall -Werror -Wextra -pedantic -ldl -g -lpthread -ljsoncpp -lgtest -lgtest_main 

all:
	$(CXX) $(SOURCES) $(CXXLIB) $(CXXFLAGS)

%.o:
	$(CXX) $(CXXFLAGS) -c $*.cpp

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(SUBMIT_FILE)
