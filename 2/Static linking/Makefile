CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -L. -lmylibrary

# List of source files
SRC = Database.cpp DatabaseIO.cpp Employee.cpp main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# The name of your static library
LIBRARY = libmylibrary.a

# The name of the final executable
EXECUTABLE = labwork2

.PHONY: all clean

all: $(LIBRARY) $(EXECUTABLE)

$(LIBRARY): $(OBJ)
	ar rcs $(LIBRARY) $(OBJ)

$(EXECUTABLE): $(LIBRARY) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) main.cpp $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(LIBRARY) $(OBJ) $(EXECUTABLE)
