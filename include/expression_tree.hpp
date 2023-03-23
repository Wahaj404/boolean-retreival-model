#ifndef __EXPRESSION_TREE_HPP__
#define __EXPRESSION_TREE_HPP__

#include "document_set.hpp"
#include "inverted_index.hpp"
#include "word_processing.hpp"

#include <memory>
#include <stack>
#include <string>
#include <vector>

class ExpressionTree {
    struct Node {
        std::string val;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(std::string const &val, std::shared_ptr<Node> left = nullptr,
             std::shared_ptr<Node> right = nullptr);
    };

    static std::string pop(std::stack<std::string> &s);
    static std::shared_ptr<Node> pop(std::stack<std::shared_ptr<Node>> &s);

    static int priority(std::string const &op);

    std::shared_ptr<Node> root;

public:
    ExpressionTree(std::vector<std::string> const &terms);

    DocumentSet evaluate(std::shared_ptr<Node> const &cur,
                         InvertedIndex const &index) const;

    DocumentSet evaluate(InvertedIndex const &index) const;
};

#endif // __EXPRESSION_TREE_HPP__
