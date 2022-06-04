#include "inverted_index.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<std::string> fnames(argv + 1, argv + argc);
    auto docnum = [](std::string const &str) -> int {
        auto i = str.find_first_of("/") + 1;
        return std::stoi(str.substr(i, str.find_last_of(".") - i));
    };
    std::sort(fnames.begin(), fnames.end(),
              [docnum](std::string const &a, std::string const &b) -> bool {
                  return docnum(a) < docnum(b);
              });

    InvertedIndex index(fnames);
    std::cout << "> ";
    for (std::string line; std::getline(std::cin, line); std::cout << "> ") {
        for (auto i : index.answer(line)) {
            std::cout << '\t' << i << '\n';
        }
    }
}