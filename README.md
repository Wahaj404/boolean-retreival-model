# brief

Information Retrieval (CS4051) assignment #01, Spring 2022

Implements a boolean retrieval model capable of serving complex boolean queries (supports NOT, AND, OR, alongwith complex nested queries) on a free-text corpus.

# compilation

**requires a compiler that supports C++20 or higher**

`make test` to build tests

`make main` to build main

`make` to build both

# execution

Both the main executable and the test suite take the source dataset as command line arguments.
For example, `out/main Abstracts/*.txt` would run the program with the entire Abstracts dataset.

The main executable prompts the user for a boolean query. To terminate, enter EOF (Ctrl + D on most systems).

See Gold Query-Set Boolean Queries.txt for query examples, or below for complex nested queries.

```
((deep OR learning) AND (classified or temporal))
((NOT (use AND deep)) OR (NOT classified AND NOT temporal))
```

# directory structure

| Folder    | Purpose                                                           |
| --------- | ----------------------------------------------------------------- |
| .vscode   | vscode debugging configurations I used while developing           |
| Abstracts | the main free text dataset this program was built around          |
| out       | compilation output - executables and object files (\*.o)          |
| include   | header files (_h or _.hpp) - my own as well as external libraries |
| src       | the implementation source files (\*.cpp) for the program          |

| File                               | Purpose                                                                                                                                          |
| ---------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------ |
| .clang-format                      | my custom c++ formatting rules                                                                                                                   |
| CS4051- IR-A1-Spring 2022.pdf      | the assignment problem statement                                                                                                                 |
| Gold Query-Set Boolean Queries.txt | set of example queries with expected outputs (#2 expected output is wrong - see test.cpp::gold2)                                                 |
| Makefile                           | compilation rules for the program                                                                                                                |
| Stopword-List.txt                  | list of stopwords to be excluded when conducting information retrieval                                                                           |
| random numerically named text file | the serialization file of the positional index, the name of the file is a collective hash of the filenames from the corpus it was generated from |

# external dependencies

uses the [Oleander Stemming Library](https://github.com/OleanderSoftware/OleanderStemmingLibrary) for stemming
