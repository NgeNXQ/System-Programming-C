CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -L. -llabwork2static

SRC = Database.cpp DatabaseIO.cpp Employee.cpp main.cpp

OBJ = $(SRC:.cpp=.o)

LIBRARY = liblabwork2static.a

EXECUTABLE = labwork2

all: $(LIBRARY) $(EXECUTABLE)

$(LIBRARY): $(OBJ)
	ar rcs $(LIBRARY) $(OBJ)

$(EXECUTABLE): $(LIBRARY) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) main.cpp $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(LIBRARY) $(OBJ) $(EXECUTABLE)
