# # Compiler and flags
# CXX := g++
# CXXFLAGS := -Wall -O2 -std=c++17

# # Target library name
# TARGET := libpid.a

# # Source and object files
# SRCS := PID.cpp
# OBJS := $(SRCS:.cpp=.o)

# # Default target
# all: $(TARGET)

# # Create static library
# $(TARGET): $(OBJS)
# 	ar rcs $@ $^

# # Compile source files into object files
# %.o: %.cpp PID.h
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Clean build files
# clean:
# 	rm -f $(OBJS) $(TARGET)


CXX := g++
CXXFLAGS := -Wall -O2 -std=c++17

SRC := PID/PID.cpp
OBJ := build/PID.o
TARGET := build/libpid.a

all: $(TARGET)

$(TARGET): $(SRC) PID/PID.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)
	ar rcs $(TARGET) $(OBJ)
	rm -f $(OBJ)

clean:
	rm -rf build


