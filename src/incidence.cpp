#include "incidence.hpp"

#include <compare>

Incidence::Incidence(std::string const &word, std::size_t const docID,
                     std::size_t const pos) :
    word_(word),
    docID_(docID), pos_(pos) {}

bool Incidence::operator<(Incidence const &other) const {
    auto res = word_ <=> other.word_;
    if (res == std::strong_ordering::equal) {
        return docID_ < other.docID_ ||
               (docID_ == other.docID_ && pos_ < other.pos_);
    }
    return res == std::strong_ordering::less;
}

std::string const &Incidence::word() const {
    return word_;
}

std::size_t Incidence::docID() const {
    return docID_;
}

std::size_t Incidence::pos() const {
    return pos_;
}