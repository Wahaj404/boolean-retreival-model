CXX=g++
CXXFLAGS=-std=c++20 -g -Wall -Werror -I./include

all: main test

out/document_set.o: include/document_set.hpp src/document_set.cpp
	$(CXX) $(CXXFLAGS) -c src/document_set.cpp -o out/document_set.o

out/expression_tree.o: include/expression_tree.hpp src/expression_tree.cpp include/document_set.hpp include/word_processing.hpp
	$(CXX) $(CXXFLAGS) -c src/expression_tree.cpp -o out/expression_tree.o

out/incidence.o: include/incidence.hpp src/incidence.cpp
	$(CXX) $(CXXFLAGS) -c src/incidence.cpp -o out/incidence.o

out/inverted_index.o: include/inverted_index.hpp src/inverted_index.cpp include/document_set.hpp include/expression_tree.hpp include/incidence.hpp include/occurrence.hpp include/posting_list.hpp include/word_processing.hpp
	$(CXX) $(CXXFLAGS) -c src/inverted_index.cpp -o out/inverted_index.o

out/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o out/main.o

out/occurrence.o: include/occurrence.hpp src/occurrence.cpp
	$(CXX) $(CXXFLAGS) -c src/occurrence.cpp -o out/occurrence.o

out/posting_list.o: include/posting_list.hpp src/posting_list.cpp include/occurrence.hpp
	$(CXX) $(CXXFLAGS) -c src/posting_list.cpp -o out/posting_list.o

out/test.o: src/test.cpp
	$(CXX) $(CXXFLAGS) -c src/test.cpp -o out/test.o

out/word_processing.o: include/word_processing.hpp src/word_processing.cpp
	$(CXX) $(CXXFLAGS) -c src/word_processing.cpp -o out/word_processing.o

main: out/main

out/main: out/document_set.o out/expression_tree.o out/incidence.o out/inverted_index.o out/main.o out/occurrence.o out/posting_list.o out/word_processing.o
	$(CXX) $(CXXFLAGS) out/document_set.o out/expression_tree.o out/incidence.o out/inverted_index.o out/main.o out/occurrence.o out/posting_list.o out/word_processing.o -o out/main

test: out/test

out/test: out/document_set.o out/expression_tree.o out/incidence.o out/inverted_index.o out/occurrence.o out/posting_list.o out/test.o out/word_processing.o
	$(CXX) $(CXXFLAGS) out/document_set.o out/expression_tree.o out/incidence.o out/inverted_index.o out/occurrence.o out/posting_list.o out/test.o out/word_processing.o -o out/test

clean:
	rm -f out/main out/test out/*.o