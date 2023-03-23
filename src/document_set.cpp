#include "document_set.hpp"

std::vector<std::size_t> const &DocumentSet::getIDs() const {
    return docIDs;
}

DocumentSet DocumentSet::universal;

void DocumentSet::setUniversal(DocumentSet const &set) {
    universal = set;
}

DocumentSet::DocumentSet(std::size_t i, std::size_t j) {
    for (auto k = i; k <= j; ++k) {
        add(k);
    }
}

DocumentSet::DocumentSet(std::vector<std::size_t> docIDs) : docIDs(docIDs) {}

void DocumentSet::add(std::size_t id) {
    docIDs.push_back(id);
}

DocumentSet DocumentSet::operator!() const {
    return universal - *this;
}

DocumentSet DocumentSet::operator&(DocumentSet const &other) const {
    DocumentSet res;
    auto &left = docIDs, &right = other.docIDs;
    for (auto i = 0UL, j = 0UL; i < left.size() && j < right.size();) {
        if (left[i] < right[j]) {
            ++i;
        } else if (left[i] > right[j]) {
            ++j;
        } else {
            res.add(left[i]);
            ++i;
            ++j;
        }
    }
    return res;
}

DocumentSet DocumentSet::operator|(DocumentSet const &other) const {
    DocumentSet res;
    auto &left = docIDs, &right = other.docIDs;
    auto i = 0UL, j = 0UL;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            res.add(left[i++]);
        } else if (left[i] > right[j]) {
            res.add(right[j++]);
        } else {
            res.add(left[i]);
            ++i;
            ++j;
        }
    }
    res.docIDs.insert(res.docIDs.end(), left.begin() + i, left.end());
    res.docIDs.insert(res.docIDs.end(), right.begin() + j, right.end());
    return res;
}

DocumentSet DocumentSet::operator-(DocumentSet const &other) const {
    DocumentSet res;
    auto &left = docIDs, &right = other.docIDs;
    auto i = 0UL, j = 0UL;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            res.add(left[i++]);
        } else if (left[i] > right[j]) {
            ++j;
        } else {
            ++i;
            ++j;
        }
    }
    res.docIDs.insert(res.docIDs.end(), left.begin() + i, left.end());
    return res;
}
