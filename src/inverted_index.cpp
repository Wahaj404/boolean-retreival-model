#include "inverted_index.hpp"

#include "expression_tree.hpp"
#include "word_processing.hpp"

#include <fstream>
#include <set>
#include <sstream>

std::size_t InvertedIndex::hash(std::vector<std::string> const &fnames) {
    constexpr auto prime = 31UL;
    auto result = 1UL;
    std::hash<std::string> hasher;
    for (auto const &fname : fnames) {
        result = result * prime + hasher(fname);
    }
    return result;
}

std::unordered_set<std::string> const InvertedIndex::stopwords = []() {
    auto tokens = tokenize("Stopword-List.txt", {});
    return std::unordered_set<std::string>(tokens.begin(), tokens.end());
}();

std::vector<std::string> InvertedIndex::parseQuery(std::string const &str) {
    std::vector<std::string> ret;
    std::stringstream ss(str);
    std::string token;
    while (ss >> token) {
        auto c = 0UL, d = 0UL;
        // count opening brackets
        while (c < token.length() && token.at(c) == '(') {
            ++c;
        }
        // count closing brackets
        while (d < token.length() && token.at(token.length() - d - 1) == ')') {
            ++d;
        }
        // add opening brackets to list
        ret.resize(ret.size() + c, "(");
        // add the token to the list - after removing any brackets
        ret.push_back(token.substr(c, token.length() - d));
        // add closing brackets to list
        ret.resize(ret.size() + d, "(");
    }
    return ret;
}

std::size_t InvertedIndex::nextDocID(std::string const &fname) {
    docIDS.push_back(fname);
    return docIDS.size() - 1;
}

std::vector<Incidence>
InvertedIndex::incidenceIndex(std::vector<std::string> const &fnames) {
    std::vector<Incidence> incs;
    for (auto const &fname : fnames) {
        auto const docID = nextDocID(fname);
        auto tokens = tokenize(fname, stopwords);
        for (auto i = 0UL; i < tokens.size(); ++i) {
            incs.emplace_back(tokens[i], docID, i);
        }
    }
    std::sort(incs.begin(), incs.end());
    DocumentSet::setUniversal(DocumentSet(0, docIDS.size() - 1));
    return incs;
}

bool InvertedIndex::read(std::string const &fname) {
    std::ifstream file(fname);
    if (!file.is_open()) {
        return false;
    }
    std::size_t n;
    file >> n;
    docIDS.assign(n, {});
    for (auto &docname : docIDS) {
        file >> docname;
    }
    file >> n;
    posts.assign(n, {});
    for (auto &pl : posts) {
        file >> pl;
    }
    return true;
}

void InvertedIndex::write(std::string const &fname) const {
    std::ofstream file(fname);
    file << docIDS.size() << ' ';
    for (auto const &docname : docIDS) {
        file << docname << ' ';
    }
    file << posts.size() << ' ';
    for (auto const &pl : posts) {
        file << pl;
    }
}

std::string InvertedIndex::filename(std::vector<std::string> const &fnames) {
    return std::to_string(hash(fnames)) + ".txt";
}

InvertedIndex::InvertedIndex(std::vector<std::string> const &fnames) {
    if (read(filename(fnames))) {
        return;
    }

    auto incs = incidenceIndex(fnames);
    for (auto i = 0UL; i < incs.size();) {
        PostingList pl(incs[i].word());
        while (i < incs.size() && pl.word() == incs[i].word()) {
            Occurrence occ(incs[i].docID());
            while (i < incs.size() && pl.word() == incs[i].word() &&
                   occ.docID() == incs[i].docID()) {
                occ.addPosition(incs[i++].pos());
            }
            pl.addOccurrence(occ);
        }
        posts.push_back(pl);
    }
    write(filename(fnames));
}

DocumentSet InvertedIndex::documentSetOf(std::string const &term) const {
    DocumentSet res;
    if (auto it = std::lower_bound(posts.begin(), posts.end(), term);
        it != posts.end()) {
        for (auto const &occur : it->occurrences()) {
            res.add(occur.docID());
        }
    }
    return res;
}

PostingList InvertedIndex::postingListOf(std::string const &term) const {
    auto it = std::lower_bound(posts.begin(), posts.end(), term);
    return it == posts.end() ? PostingList(term) : *it;
}

DocumentSet InvertedIndex::positionalIntersect(std::string const &t1,
                                               std::string const &t2,
                                               std::size_t prox) const {
    static auto absDiff = [](std::size_t a, std::size_t b) -> std::size_t {
        return std::max(a, b) - std::min(a, b);
    };

    auto left = postingListOf(t1).occurrences(),
         right = postingListOf(t2).occurrences();
    auto i = 0UL, j = 0UL;
    std::set<std::size_t> ans;
    while (i < left.size() && j < right.size()) {
        if (left[i].docID() < right[j].docID()) {
            ++i;
        } else if (left[i].docID() > right[j].docID()) {
            ++j;
        } else {
            auto &p1 = left[i], &p2 = right[j];
            auto ii = 0UL, jj = 0UL;
            std::vector<std::size_t> L;
            while (ii < p1.size()) {
                while (jj < p2.size()) {
                    if (absDiff(p1[ii], p2[jj]) <= prox) {
                        L.push_back(p2[jj]);
                    } else if (p2[jj] > p1[ii]) {
                        break;
                    }
                    ++jj;
                }
                while (!L.empty() && absDiff(p1[ii], L.front()) > prox) {
                    L.erase(L.begin());
                }
                if (!L.empty()) {
                    ans.insert(left[i].docID());
                }
                ++ii;
            }
            ++i;
            ++j;
        }
    }
    return std::vector<std::size_t>(ans.begin(), ans.end());
}

DocumentSet InvertedIndex::answerAsDocIDs(std::string const &query) const {
    return ExpressionTree(parseQuery(query)).evaluate(*this);
}

std::vector<std::string> InvertedIndex::answer(std::string const &query) const {
    auto res = ExpressionTree(parseQuery(query)).evaluate(*this);
    std::vector<std::string> ret;
    for (auto const &doc : res.getIDs()) {
        ret.push_back(docIDS[doc]);
    }
    return ret;
}