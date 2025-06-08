# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -g

# Executables
MAIN_TARGET = main
TEST_TARGET = test

# Object files
MAIN_OBJS = main.o MyContainer.o
TEST_OBJS = test.o MyContainer.o

# Header files
HEADERS = Iterator.hpp MyContainer.hpp AscendingOrder.hpp DescendingOrder.hpp \
          SideCrossOrder.hpp ReverseOrder.hpp Order.hpp MiddleOutOrder.hpp

# Default target
all: Main

# Build and run main program
Main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Build and run tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run valgrind memory check on main program
valgrind: $(MAIN_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(MAIN_TARGET)

# Clean all generated files
clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(MAIN_TARGET) $(TEST_TARGET)

# Build main executable
$(MAIN_TARGET): $(MAIN_OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_TARGET) $(MAIN_OBJS)

# Build test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Compile main.cpp
main.o: main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile test.cpp
test.o: test.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c test.cpp

# Compile MyContainer.cpp
MyContainer.o: MyContainer.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c MyContainer.cpp

# Phony targets
.PHONY: all Main test valgrind clean