# Compiler settings
CXX = g++-11
CXXFLAGS = -std=c++17 -Wall -Iheaders -IEigen -fopenmp -MMD -MP

# Linker settings
LDFLAGS = -L$(shell brew --prefix llvm)/lib -fopenmp
CPPFLAGS = -I$(shell brew --prefix llvm)/include
# LDLIBS = -lAlembic -lImath

# Build directory
BUILD_DIR = build

# Target executable name
TARGET = letitsnow

# Set number of threads
OMP_NUM_THREADS = 8
# LDFLAGS="-L/opt/homebrew/opt/llvm/lib" "-Lbuild_alembic/install/lib" "-Lexternal/Imath/lib" -fopenmp
# CPPFLAGS="-I/opt/homebrew/opt/llvm/include"

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
