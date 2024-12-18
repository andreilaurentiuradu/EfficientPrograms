# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Source file and output binary
SRC = implementations/3.2_loop_unrolling.cpp
OUT = 3.2_loop_unrolling

# Input CSV files
INPUTS = a.csv b.csv c.csv d.csv

# Default target: compile and run
all: $(OUT)
	./$(OUT) $(INPUTS)

# Target to compile the source file
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Clean up the generated files
clean:
	rm -f $(OUT)
