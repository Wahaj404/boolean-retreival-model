#ifndef __OCCURRENCE_HPP__
#define __OCCURRENCE_HPP__

#include <iostream>
#include <vector>

class Occurrence {
    std::size_t docID_;
    std::vector<std::size_t> positions;

public:
    Occurrence(std::size_t docID);

    void addPosition(std::size_t pos);

    std::size_t docID() const;

    std::size_t size() const;

    std::size_t operator[](std::size_t pos) const;

    friend std::istream &operator>>(std::istream &in, Occurrence &occ);
    friend std::ostream &operator<<(std::ostream &out, Occurrence const &occ);
};

#endif // __OCCURRENCE_HPP__
