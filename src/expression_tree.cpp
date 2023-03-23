#include "expression_tree.hpp"

ExpressionTree::Node::Node(std::string const &val, std::shared_ptr<Node> left,
                           std::shared_ptr<Node> right) :
    val(val),
    left(left), right(right) {}

std::string ExpressionTree::pop(std::stack<std::string> &s) {
    auto ret = s.top();
    s.pop();
    return ret;
}

std::shared_ptr<ExpressionTree::Node>
ExpressionTree::pop(std::stack<std::shared_ptr<Node>> &s) {
    auto ret = s.top();
    s.pop();
    return ret;
}

int ExpressionTree::priority(std::string const &op) {
    if (op == "NOT") {
        return 3;
    }
    if (op == "AND") {
        return 2;
    }
    if (op == "OR") {
        return 1;
    }
    if (op.front() == '/') {
        return 0;
    }
    return -1;
}

ExpressionTree::ExpressionTree(std::vector<std::string> const &terms) {
    std::stack<std::shared_ptr<Node>> nodes;
    std::stack<std::string> ops;

    for (auto const &term : terms) {
        int prio = priority(term);
        if (prio == -1) {
            if (term == "(") {
                ops.push("(");
            } else if (term == ")") {
                while (!ops.empty() && ops.top() != "(") {
                    auto op = pop(ops);
                    auto right = op == "NOT" ? nullptr : pop(nodes);
                    auto left = pop(nodes);
                    nodes.push(make_shared<Node>(op, left, right));
                }
                ops.pop();
            } else {
                auto str = term;
                stem(str);
                nodes.push(
                    make_shared<Node>(std::string(str.begin(), str.end())));
            }
        } else {
            while (!ops.empty() && ops.top() != "(" &&
                   ((term != "NOT" && prio <= priority(ops.top())) ||
                    (term == "NOT" && prio < priority(ops.top())))) {
                auto op = pop(ops);
                auto right = op == "NOT" ? nullptr : pop(nodes);
                auto left = pop(nodes);
                nodes.push(make_shared<Node>(op, left, right));
            }
            ops.push(term);
        }
    }
    while (!ops.empty()) {
        auto op = pop(ops);
        auto right = op == "NOT" ? nullptr : pop(nodes);
        auto left = pop(nodes);
        nodes.push(make_shared<Node>(op, left, right));
    }
    root = pop(nodes);
}

DocumentSet ExpressionTree::evaluate(std::shared_ptr<Node> const &cur,
                                     InvertedIndex const &index) const {
    if (cur != nullptr) {
        if (cur->val == "NOT") {
            return !evaluate(cur->left, index);
        }
        if (cur->val == "AND") {
            return evaluate(cur->left, index) & evaluate(cur->right, index);
        }
        if (cur->val == "OR") {
            return evaluate(cur->left, index) | evaluate(cur->right, index);
        }
        if (cur->val.front() == '/') {
            return index.positionalIntersect(cur->left->val, cur->right->val,
                                             std::stoi(cur->val.substr(1)) + 1);
        }
        return index.documentSetOf(cur->val);
    }
    return {};
}

DocumentSet ExpressionTree::evaluate(InvertedIndex const &index) const {
    return evaluate(root, index);
}