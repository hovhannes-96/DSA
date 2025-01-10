#include <iostream>
#include <limits>

struct Node {
    int val;
    Node* left;
    Node* right;
    Node* parent;
    explicit Node(int v) : val(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root_;
public:
    explicit BinarySearchTree(Node* root) : root_(root) {}
    void insert(int val) {
        if (!root_) {
            root_ = new Node(val);
            return;
        }
        Node* curr = root_;
        while (curr) {
            if (val == curr->val) {
                return;
            }
            if (val < curr->val) {
                if (!curr->left) {
                    curr->left = new Node(val);
                    curr->left->parent = curr;
                    return;
                }
                curr = curr->left;
            } else {
                if (!curr->right) {
                    curr->right = new Node(val);
                    curr->right->parent = curr;
                    return;
                }
                curr = curr->right;
            }
        }
    }
    [[nodiscard]] Node* search(int val) const {
        if (!root_) {
            return nullptr;
        }
        Node* curr = root_;
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
    [[nodiscard]] Node* min() const {
        if (!root_) {
            return nullptr;
        }
        auto curr = root_;
        while (curr->left) {
            curr = curr->left;
        }
        return curr;
    }
    [[nodiscard]] Node* max() const {
        if (!root_) {
            return nullptr;
        }
        auto curr = root_;
        while (curr->right) {
            curr = curr->right;
        }
        return curr;
    }

    void erase(Node* node) {
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
                root_ = node->left;
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
                root_ = node->right;
            }
            delete node;
        } else {
            Node* curr = node->left;
            while (curr->right) {
                curr = curr->right;
            }
            node->val = curr->val;
            erase(curr);
        }
    }

    ~BinarySearchTree() {
        if (!root_) {
            return;
        }
        traversal(root_->left);
        traversal(root_->right);
        delete root_;
    }
    void traversal(Node* root) {
        if (!root) {
            return;
        }
        traversal(root->left);
        std::cout << root->val << " ";
        traversal(root->right);
    }
    void print() {
        traversal(root_);
        std::cout << std::endl;
    }
    [[nodiscard]] Node* get_root() const {
        return root_;
    }
};

bool is_BST(Node* root, int min, int max) {
    if (!root) {
        return true;
    }
    if (!(root->val > min && root->val < max)) {
        return false;
    }
    return is_BST(root->left, min, root->val) && is_BST(root->right, root->val, max);
}

int main() {
    BinarySearchTree tree(nullptr);
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(9);
    tree.insert(6);
    tree.insert(1);
    tree.insert(4);

    // tree.erase(tree.search(6));
    tree.erase(tree.search(5));
    // tree.erase(tree.search(5));
    tree.print();

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