CXX = g++
CXXFLAGS = -Wall -std=c++11 -fPIC
LDFLAGS = -L. -lmylibrary

# List of source files
SRC = Database.cpp DatabaseIO.cpp Employee.cpp main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# The name of your dynamic library
LIBRARY = libmylibrary.so

# The name of the final executable
EXECUTABLE = labwork2

.PHONY: all clean

all: $(LIBRARY) $(EXECUTABLE)

$(LIBRARY): $(OBJ)
	$(CXX) -shared -o $(LIBRARY) $(OBJ)

$(EXECUTABLE): $(LIBRARY) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) main.cpp $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Copy the shared library to the program's directory
copy_library:
	cp $(LIBRARY) $(EXECUTABLE)

clean:
	rm -f $(LIBRARY) $(OBJ) $(EXECUTABLE)

.PHONY: copy_library
