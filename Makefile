# Declaration of variables
CC = g++
CC_FLAGS = -w -Wall -std=c11
 
# File names
EXEC = run
SRCDIRS := $(shell find . -name '*.cpp' -exec dirname {} \; | uniq)
SOURCES := $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
