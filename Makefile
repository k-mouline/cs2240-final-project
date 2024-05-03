# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iheaders -IEigen -Ibuild_alembic/install/include

# Linker settings
LDFLAGS = -Lbuild_alembic/install/lib
LDLIBS = -lAlembic

# Build directory
BUILD_DIR = build

# Target executable name
TARGET = letitsnow

# Source files
SRC = $(wildcard src/*.cc)

# Object files
OBJ = $(SRC:src/%.cc=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Linking the target executable
$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)

# Compiling every source file
$(BUILD_DIR)/%.o: src/%.cc
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleaning up
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Include dependencies
-include $(OBJ:.o=.d)

# Calculating dependencies
%.d: %.cc
	@set -e; rm -f $@; \
	 $(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$
