###############################################################################
# PID/PID.cpp

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


################################################################################

# Navigator/Navigator.cpp

# CXX := g++
# CXXFLAGS := -Wall -O2 -std=c++17

# SRC := Navigator/Navigator.cpp
# OBJ := build/nav.o
# TARGET := build/libnav.a

# all: $(TARGET)

# $(TARGET): $(SRC) Navigator/Navigator.h
# 	@mkdir -p build
# 	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)
# 	ar rcs $(TARGET) $(OBJ)
# 	rm -f $(OBJ)

# clean:
# 	rm -rf build

################################################################################


