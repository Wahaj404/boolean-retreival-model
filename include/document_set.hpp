#ifndef __DOCUMENT_SET_HPP__
#define __DOCUMENT_SET_HPP__

#include <vector>

class DocumentSet {
    static DocumentSet universal;

    std::vector<std::size_t> docIDs;

public:
    static void setUniversal(DocumentSet const &set);

    DocumentSet() = default;
    DocumentSet(std::size_t i, std::size_t j);
    DocumentSet(std::vector<std::size_t> docIDs);

    void add(std::size_t id);

    DocumentSet operator!() const;

    DocumentSet operator&(DocumentSet const &other) const;
    DocumentSet operator|(DocumentSet const &other) const;
    DocumentSet operator-(DocumentSet const &other) const;

    std::vector<std::size_t> const &getIDs() const;
};

#endif // __DOCUMENT_SET_HPP__
