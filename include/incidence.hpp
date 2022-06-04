#ifndef __INCIDENCE_HPP__
#define __INCIDENCE_HPP__

#include <string>

class Incidence {
    std::string word_;
    std::size_t docID_;
    std::size_t pos_;

public:
    Incidence(std::string const &word, std::size_t docID, std::size_t pos);

    bool operator<(Incidence const &other) const;

    std::string const &word() const;

    std::size_t docID() const;

    std::size_t pos() const;
};

#endif // __INCIDENCE_HPP__
