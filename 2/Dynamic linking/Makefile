CXX := g++
CXXFLAGS := -Wall -std=c++11

LIB_DIR := /usr/local/lib64

SOURCES := Database.cpp DatabaseIO.cpp Employee.cpp
OBJS := $(SOURCES:.cpp=.o)

LIB_NAME := liblabwork2dynamic.so
LDFLAGS := -shared

EXECUTABLE := labwork2

all: $(LIB_NAME) $(EXECUTABLE)

$(LIB_NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(LIB_NAME) $(OBJS)
	mv $(LIB_NAME) $(LIB_DIR)

$(EXECUTABLE): main.o $(LIB_NAME)
	$(CXX) main.o -o $(EXECUTABLE) -L$(LIB_DIR) -llabwork2dynamic

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB_DIR)/$(LIB_NAME) $(EXECUTABLE)
