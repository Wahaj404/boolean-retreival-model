#include "occurrence.hpp"

Occurrence::Occurrence(std::size_t docID) : docID_(docID) {}

void Occurrence::addPosition(std::size_t pos) {
    positions.push_back(pos);
}

std::size_t Occurrence::docID() const {
    return docID_;
}

std::size_t Occurrence::size() const {
    return positions.size();
}
std::size_t Occurrence::operator[](std::size_t pos) const {
    return positions[pos];
}

std::istream &operator>>(std::istream &in, Occurrence &occ) {
    std::size_t n;
    in >> occ.docID_ >> n;
    occ.positions = std::vector<std::size_t>(n);
    for (auto &i : occ.positions) {
        in >> i;
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, Occurrence const &occ) {
    out << occ.docID_ << ' ' << occ.size() << ' ';
    for (auto i : occ.positions) {
        out << i << ' ';
    }
    out.flush();
    return out;
}
