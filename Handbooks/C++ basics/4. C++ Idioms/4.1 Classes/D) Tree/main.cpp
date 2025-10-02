#include <map>
#include <string>
#include <vector>

struct Node {
    std::map<std::string, Node> children;
};

class Tree {
private:
    Node root;

public:
    bool Has(const std::vector<std::string>& node) const;
    void Insert(const std::vector<std::string>& node);
    void Delete(const std::vector<std::string>& node);
};

// My code
bool Tree::Has(const std::vector<std::string>& node) const {
    const Node * current = &root;
    for (const std::string & part : node) {
        if (!current->children.contains(part)) {
            return false;
        }

        current = &current->children.at(part);
    }

    return true;
}

void Tree::Insert(const std::vector<std::string> & node) {
    Node * current = &root;

    for (const std::string& part : node) {
        current = &current->children[part];
    }
    return;
}

void Tree::Delete(const std::vector<std::string>& node) {
    if (!Has(node)) {
        return;
    }

    Node * current = &root;

    for (size_t i = 0; i < node.size() - 1; ++i) {
        current = &current->children.at(node[i]);
    }

    current->children.erase(node.back());
}

#include <iostream>

int main() {
    // Node tmp;
    // tmp.children["a"] = Node();

    Tree cur;
    cur.Insert({"a", "b", "c"});

    std::cout << std::boolalpha << cur.Has({"a"}) << " " << cur.Has({"a", "b"}) << " " << cur.Has({"a", "b", "c"}) << '\n';
    cur.Insert({"a", "b", "d"});
    std::cout << std::boolalpha << cur.Has({"a", "b", "d"}) << '\n' << '\n';
    cur.Delete({"a", "b", "c"});
    std::cout << std::boolalpha << cur.Has({"a"}) << " " << cur.Has({"a", "b"}) << " " << cur.Has({"a", "b", "c"}) << '\n';
    std::cout << std::boolalpha << cur.Has({"a", "b", "d"}) << '\n';
    return 0;
}