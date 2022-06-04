#include "word_processing.hpp"

#include "olestem/stemming/english_stem.h"

#include <fstream>

void trimPunctuationRight(std::wstring &str) {
    static std::unordered_set<wchar_t> const punct = {L',', L'.'};
    while (!str.empty() && punct.contains(str.back())) {
        str.pop_back();
    }
}

void toLower(std::wstring &str) {
    std::transform(str.begin(), str.end(), str.begin(), towlower);
}

std::vector<std::wstring> splitOnPunctuation(std::wstring &str) {
    static auto punct = L"(),.-/";

    std::vector<std::wstring> ret;
    std::size_t i = 0, j = 0;
    while ((j = str.find_first_of(punct, i)) != std::string::npos) {
        if (j - i > 1) {
            ret.push_back(str.substr(i, j - i));
        }
        i = j + 1;
    }
    if (str.length() - i > 1) {
        ret.push_back(str.substr(i));
    }
    return ret;
}

static stemming::english_stem stemmer;

std::vector<std::wstring> normalize(std::wstring &str) {
    toLower(str);
    trimPunctuationRight(str);
    auto words = splitOnPunctuation(str);
    for (auto &word : words) {
        stemmer(word);
    }
    return words;
}

void stem(std::string &str) {
    std::wstring ws(str.begin(), str.end());
    stemmer(ws);
    str = std::string(ws.begin(), ws.end());
}

std::vector<std::string>
tokenize(std::string fname, std::unordered_set<std::string> const &stopwords) {
    std::vector<std::string> ret;
    std::wifstream file(fname);
    std::wstring word;
    while (file >> word) {
        for (auto const &ws : normalize(word)) {
            ret.emplace_back(ws.begin(), ws.end());
        }
    }
    std::erase_if(ret, [stopwords](std::string const &str) -> bool {
        return stopwords.contains(str);
    });
    return ret;
}
