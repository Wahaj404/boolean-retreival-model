#ifndef __WORD_PROCESSING_HPP__
#define __WORD_PROCESSING_HPP__

#include <string>
#include <unordered_set>
#include <vector>

constexpr char sep = ':';
constexpr char newl = '\n';

void stem(std::string &str);

std::vector<std::string>
tokenize(std::string fname, std::unordered_set<std::string> const &stopwords);

#endif // __WORD_PROCESSING_HPP__
