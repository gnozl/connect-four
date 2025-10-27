CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Target executable
TARGET = tournament

# Source files
SOURCES = ConnectFour.cpp Player.cpp strategies.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Rebuild everything
rebuild: clean all

.PHONY: all clean rebuild
