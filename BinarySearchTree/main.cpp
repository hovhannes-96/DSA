#include <iostream>
#include <limits>
#include <queue>
#include <stack>

struct Node {
    int val;
    Node *left;
    Node *right;
    Node *parent;

    explicit Node(int v) : val(v), left(nullptr), right(nullptr), parent(nullptr) {
    }
};

class BinarySearchTree {
private:
    Node *_root;

public:
    explicit BinarySearchTree(Node *root) : _root(root) {
    }

    bool insert(const int val) {
        if (!_root) {
            _root = new Node(val);
            return true;
        }
        Node *curr = _root;
        while (curr) {
            if (val == curr->val) {
                return false;
            }
            if (val < curr->val) {
                if (!curr->left) {
                    curr->left = new Node(val);
                    curr->left->parent = curr;
                    return true;
                }
                curr = curr->left;
            } else {
                if (!curr->right) {
                    curr->right = new Node(val);
                    curr->right->parent = curr;
                    return true;
                }
                curr = curr->right;
            }
        }
    }

    [[nodiscard]] Node *search(const int val) const {
        if (!_root) {
            return nullptr;
        }
        Node *curr = _root;
        while (curr) {
            if (val == curr->val) {
                return curr;
            }
            if (val < curr->val) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return nullptr;
    }

    [[nodiscard]] Node *min() const {
        if (!_root) {
            return nullptr;
        }
        auto curr = _root;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }

    [[nodiscard]] Node *max() const {
        if (!_root) {
            return nullptr;
        }
        auto curr = _root;
        while (curr->right) {
            curr = curr->right;
        }
        return curr;
    }

    void erase(Node *node) {
        if (!node) {
            return;
        }

        if (!node->left && !node->right) {
            if (node->parent) {
                if (node == node->parent->left) {
                    node->parent->left = nullptr;
                } else {
                    node->parent->right = nullptr;
                }
            }
            delete node;
        } else if (node->left && !node->right) {
            if (node->parent) {
                if (node == node->parent->left) {
                    node->parent->left = node->left;
                } else {
                    node->parent->right = node->left;
                }
            } else {
                _root = node->left;
            }
            delete node;
        } else if (!node->left && node->right) {
            if (node->parent) {
                if (node == node->parent->left) {
                    node->parent->left = node->right;
                } else {
                    node->parent->right = node->right;
                }
            } else {
                _root = node->right;
            }
            delete node;
        } else {
            Node *curr = node->left;
            while (curr->right) {
                curr = curr->right;
            }
            node->val = curr->val;
            erase(curr);
        }
    }

    void mirror_recursive() {
        mirror_recursive_helper(_root);
    }

    void mirror_recursive_helper(Node *node) {
        if (!node) {
            return;
        }
        mirror_recursive_helper(node->left);
        mirror_recursive_helper(node->right);
        std::swap(node->left, node->right);
    }

    void mirror_iterative() {
        mirror_iterative_helper(_root);
    }

    static void mirror_iterative_helper(Node *node) {
        if (!node) {
            return;
        }
        std::queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            Node *curr = q.front();
            std::swap(curr->left, curr->right);
            q.pop();
            if (curr->left) {
                q.push(curr->left);
            }
            if (curr->right) {
                q.push(curr->right);
            }
        }
    }

    ~BinarySearchTree() {
        clean(_root);
    }

    static void clean(const Node *node) {
        if (!node) {
            return;
        }
        clean(node->left);
        clean(node->right);
        delete node;
    }

    [[nodiscard]] double balanceness() const {
        if (!_root) return 1;
        unsigned closest = 0;
        unsigned depth = 0;
        Node *curr = _root;
        std::queue<Node *> q;
        q.push(curr);
        while (!q.empty()) {
            depth++;
            size_t len = q.size();
            while (len) {
                curr = q.front();
                q.pop();
                if (!closest && !curr->left && !curr->right) {
                    closest = depth;
                }
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
                len--;
            }
        }
        return static_cast<double>(closest) / depth;
    }

    [[nodiscard]] Node *predecessor(Node *node) const {
        if (!node) {
            return nullptr;
        }
        if (node->left) {
            node = node->left;
            while (node->right) {
                node = node->right;
            }
            return node;
        }

        if (!node->parent) {
            return nullptr;
        }

        if (node == node->parent->right) {
            return node->parent;
        }

        while (node->parent && node == node->parent->left) {
            node = node->parent;
        }
        if (node->parent) {
            return node->parent;
        }

        return nullptr;
    }

    void printBFS() {
        if (!_root) return;
        Node *curr = _root;
        std::queue<Node *> q;
        q.push(curr);
        while (!q.empty()) {
            curr = q.front();
            q.pop();
            std::cout << curr->val << " ";
        }
    }

    void printPreOrder() const {
        if (!_root) return;
        std::stack<Node *> s;
        Node *curr = _root;
        while (curr || !s.empty()) {
            while (curr) {
                std::cout << curr->val << " ";
                s.push(curr->right);
                curr = curr->left;
            }
            if (!s.empty()) {
                curr = s.top();
                s.pop();
            }
        }
    }
};

bool is_BST(Node *root, int min, int max) {
    if (!root) {
        return true;
    }
    if (!(root->val > min && root->val < max)) {
        return false;
    }
    return is_BST(root->left, min, root->val) && is_BST(root->right, root->val, max);
}

void batchConstructionByInserts(BinarySearchTree &tree, const std::vector<int> &values, int start, int end) {
    if (start > end) {
        return;
    }
    int mid = start + (end - start) / 2;
    tree.insert(values[mid]);
    batchConstructionByInserts(tree, values, start, mid - 1);
    batchConstructionByInserts(tree, values, mid + 1, end);
}


int main() {
    BinarySearchTree tree(nullptr);
    std::cout << tree.balanceness() << std::endl;

    tree.insert(5);
    std::cout << tree.balanceness() << std::endl;
    tree.insert(7);
    std::cout << tree.balanceness() << std::endl;
    tree.insert(3);
    std::cout << tree.balanceness() << std::endl;
    tree.insert(9);
    std::cout << tree.balanceness() << std::endl;
    tree.insert(6);
    std::cout << tree.balanceness() << std::endl;
    tree.insert(1);
    std::cout << tree.balanceness() << std::endl;
    tree.insert(4);
    std::cout << tree.balanceness() << std::endl;
    std::cout << "\n";
    // tree.printPreOrder();
    // Node* x = tree.predecessor(tree.search(3));
    // if (x) {
    //     std::cout << x->val;
    // } else {
    //     std::cout << "null";
    // }

    // tree.mirror_recursive();
    // tree.print();
    // tree.mirror_iterative();
    // tree.print();

    // tree.erase(tree.search(6));
    // tree.erase(tree.search(5));
    // tree.erase(tree.search(5));
    // tree.print();

    // std::cout << tree.search(5) << std::endl;
    // std::cout << tree.search(50) << std::endl;
    //
    // std::cout << tree.min() << std::endl;
    // std::cout << tree.max() << std::endl;

    // std::cout << is_BST(tree.get_root(), INT32_MIN, INT32_MAX) << std::endl;
    // tree.get_root()->val = 10;
    // std::cout << is_BST(tree.get_root(), INT32_MIN, INT32_MAX) << std::endl;
    return 0;
}
