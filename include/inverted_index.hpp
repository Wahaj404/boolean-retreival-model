#ifndef __INVERTED_INDEX_HPP__
#define __INVERTED_INDEX_HPP__

#include "document_set.hpp"
#include "incidence.hpp"
#include "occurrence.hpp"
#include "posting_list.hpp"

#include <string>
#include <unordered_set>
#include <vector>

class InvertedIndex {
    static std::size_t hash(std::vector<std::string> const &fnames);

    static std::unordered_set<std::string> const stopwords;

    static std::vector<std::string> parseQuery(std::string const &str);

    std::vector<std::string> docIDS;
    std::vector<PostingList> posts;

    std::size_t nextDocID(std::string const &fname);

    std::vector<Incidence>
    incidenceIndex(std::vector<std::string> const &fnames);

    bool read(std::string const &fname);
    void write(std::string const &fname) const;
    static std::string filename(std::vector<std::string> const &fnames);

public:
    InvertedIndex(std::vector<std::string> const &fnames);

    DocumentSet documentSetOf(std::string const &term) const;
    PostingList postingListOf(std::string const &term) const;

    DocumentSet positionalIntersect(std::string const &t1,
                                    std::string const &t2,
                                    std::size_t prox) const;

    std::vector<std::string> answer(std::string const &query) const;

    DocumentSet answerAsDocIDs(std::string const &query) const;
};

#endif // __INVERTED_INDEX_HPP__
