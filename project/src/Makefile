CXX_DIR = ../lib/cxxtest
CXXTEST = $(CXX_DIR)/cxxtestgen.pl
CXXFLAGS = --error-printer --abort-on-fail --have-eh

FLAGS = -Wall -g

# Program files.
readInput.o:	readInput.cpp readInput.h
	g++ $(FLAGS) -c readInput.cpp 

regex.o:	regex.cpp regex.h
	g++ $(FLAGS) -c regex.cpp 

scanner.o:	scanner.cpp scanner.h regex.h
	g++ $(FLAGS) -c scanner.cpp 

parser.o:	parser.cpp parser.h scanner.h parseResult.h extToken.h AST.h
	g++ $(FLAGS) -c parser.cpp 

parseResult.o:  parseResult.cpp parseResult.h AST.h
	g++ $(FLAGS) -c parseResult.cpp

extToken.o:     extToken.cpp parser.h
	g++ $(FLAGS) -c extToken.cpp


# Testing files and targets.
run-tests:  regex_tests scanner_tests parser_tests ast_tests codegeneration_tests
	./regex_tests
	./scanner_tests
	./parser_tests
	./ast_tests
	./codegeneration_tests

run-ast_tests:	ast_tests
	./ast_tests

regex_tests:	regex_tests.cpp regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -o regex_tests regex.o regex_tests.cpp

regex_tests.cpp:	regex.h regex_tests.h
	$(CXXTEST) $(CXXFLAGS) -o regex_tests.cpp regex_tests.h

scanner_tests:	scanner_tests.cpp scanner.o regex.o readInput.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o scanner_tests scanner.o regex.o \
		readInput.o scanner_tests.cpp

scanner_tests.cpp:	scanner.o scanner_tests.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o scanner_tests.cpp scanner_tests.h

parser_tests:	parser_tests.cpp parser.o scanner.o extToken.o parseResult.o 
	g++ $(FLAGS) -I$(CXX_DIR)  -o parser_tests \
		parser.o scanner.o regex.o readInput.o extToken.o \
		parseResult.o parser_tests.cpp

parser_tests.cpp:	parser_tests.h parser.o scanner.o regex.o \
			readInput.o extToken.o parseResult.o
	$(CXXTEST) $(CXXFLAGS) -o parser_tests.cpp parser_tests.h

ast_tests:	ast_tests.cpp readInput.o regex.o scanner.o parser.o parseResult.o extToken.o 
	g++ $(FLAGS) -I$(CXX_DIR)  -o ast_tests \
		ast_tests.cpp readInput.o regex.o scanner.o parser.o parseResult.o extToken.o  

ast_tests.cpp:	ast_tests.h parser.o readInput.h
	$(CXXTEST) $(CXXFLAGS) -o ast_tests.cpp ast_tests.h

codegeneration_tests:	codegeneration_tests.cpp 
	g++ $(FLAGS) -I$(CXX_DIR) -o codegeneration_tests \
		codegeneration_tests.cpp readInput.o regex.o scanner.o parser.o parseResult.o extToken.o

codegeneration_tests.cpp:	codegeneration_tests.h parser.o readInput.o scanner.o regex.o extToken.o parseResult.o 
	$(CXXTEST) --error-printer -o codegeneration_tests.cpp codegeneration_tests.h

clean:
	rm -Rf *.o \
		regex_tests regex_tests.cpp \
		scanner_tests scanner_tests.cpp \
		parser_tests parser_tests.cpp \
		ast_tests ast_tests.cpp \
		codegeneration_tests codegeneration_tests.cpp \

