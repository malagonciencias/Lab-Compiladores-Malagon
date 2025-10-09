CXX?=clang++
CXX = g++
CXXDEBUG = -g -Wall
CXXSTD =-std=c++14
CXXFLAGS = -Wno-deprecated-register -O0 $(CXXDEBUG) $(CXXSTD)
EXE = analyzer

CPPOBJ= main Parser ./AL/Lexer

LEXER = lexer.ll
SRCS = Lexer.cpp Parser.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

# FILES= $(addsuffix .cpp, $(CPPOBJ))
# OBJS = $(addsuffix .o, $(CPPOBJ))

CLEANLIST = $(OBJS) $(EXE)

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJS)

$(EXE): $(LEXER) $(SRCS)
	flex++ $(LEXER)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXE)

.PHONY: clean
clean:
	rm -rf $(CLEANLIST)
