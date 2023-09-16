# CPP Compiler
COMPILER = g++

# Debugging
FLAG_DEBUG = -g -Wall

# Optimized execution
FLAG_OPTIMIZE = -O2

# File to Compile
LIBRARY_FILE = LibraryCode.cpp

#OutPut File
DEBUG_LIBRARY = Library_Debug_File
OPTIMIZE_LIBRARY = Library_Optimize_File

# Compile for Debugging
Debug_LIBRARY:
	$(COMPILER) $(FLAG_DEBUG) $(LIBRARY_FILE) -o $(DEBUG_LIBRARY)

# Compile for optimization
Optimize_LIBRARY:
	$(COMPILER) $(FLAG_OPTIMIZE) $(LIBRARY_FILE) -o $(OPTIMIZE_LIBRARY)
