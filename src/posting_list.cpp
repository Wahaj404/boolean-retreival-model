#include "posting_list.hpp"

PostingList::PostingList(std::string word) : word_(word), freq_(0) {}

void PostingList::addOccurrence(Occurrence const &occ) {
    occur.push_back(occ);
    freq_ += occ.size();
}

std::string const &PostingList::word() const {
    return word_;
}

std::size_t PostingList::freq() const {
    return freq_;
}

std::vector<Occurrence> const &PostingList::occurrences() const {
    return occur;
}

bool PostingList::operator<(std::string const &term) const {
    return word_ < term;
}

std::istream &operator>>(std::istream &in, PostingList &list) {
    std::size_t n;
    in >> list.word_ >> list.freq_ >> n;
    list.occur = std::vector<Occurrence>(n, 0);
    for (auto &occ : list.occur) {
        in >> occ;
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, PostingList const &list) {
    out << list.word_ << ' ' << list.freq_ << ' ' << list.occur.size() << ' ';
    for (auto const &occ : list.occur) {
        out << occ;
    }
    return out;
}