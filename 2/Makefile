# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Target executable
TARGET = labwork2

# Source files
SRCS = main.cpp Employee.cpp Database.cpp

# Header files
HDRS = Employee.h Database.h Flags.h

# Object files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean

# Default target
all: $(TARGET)

# Linking step - create the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compilation step - create object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the object files and the executable
clean: rm -f $(OBJS) $(TARGET)