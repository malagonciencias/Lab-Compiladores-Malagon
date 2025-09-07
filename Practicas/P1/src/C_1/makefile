# Compiler
CXX = g++
FLEX = flex++

# Lexer flex file
LEXER = lexer.ll
# Lexer++ result file
LEXER_CPP = Lexer.cpp
# Source files
SRCS = $(LEXER_CPP) main.cpp
# Target executable
OBJECTS = $(SRCS:.cpp=.o)
TARGET = compiler




all: $(TARGET) 

# Rule to link object files into the target executable
$(LEXER_CPP): $(LEXER)
	$(FLEX) -o $(LEXER_CPP) $(LEXER)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJECTS) $(LEXER_CPP) $(TARGET)