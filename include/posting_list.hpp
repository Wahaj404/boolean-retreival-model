#ifndef __POSTING_LIST_HPP__
#define __POSTING_LIST_HPP__

#include "occurrence.hpp"

#include <string>
#include <vector>

class PostingList {
    std::string word_;
    std::size_t freq_;
    std::vector<Occurrence> occur;

public:
    PostingList(std::string word = "");

    void addOccurrence(Occurrence const &occ);

    std::string const &word() const;

    std::size_t freq() const;

    std::vector<Occurrence> const &occurrences() const;

    bool operator<(std::string const &term) const;

    friend std::istream &operator>>(std::istream &in, PostingList &list);
    friend std::ostream &operator<<(std::ostream &out, PostingList const &list);
};

#endif // __POSTING_LIST_HPP__
