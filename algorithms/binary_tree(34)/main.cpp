#include <fstream>

std::ifstream fin("tst.in");
std::ofstream fout("tst.out");


struct Node {
    int value;
    int depth;
    Node *left;
    Node *right;
    std::pair<Node *, Node *> way = {nullptr, nullptr};
    int wayLength = 0;
};


class BinaryTree {
private:
    Node *root;
    int height = -1;
    Node *maxNode;

    void maxWayFromBelow(Node *node) {
        if (!node->left && !node->right) {
            node->way = {node, node};
            node->wayLength = 0;
        } else if (!node->left) {
            maxWayFromBelow(node->right);
            node->way.first = node;
            if (node->right->way.first->depth > node->right->way.second->depth) {
                node->way.second = node->right->way.first;
                node->wayLength = node->right->way.first->depth - node->depth;
            } else {
                node->way.second = node->right->way.second;
                node->wayLength = node->right->way.second->depth - node->depth;
            }
        } else if (!node->right) {
            maxWayFromBelow(node->left);
            node->way.second = node;
            if (node->left->way.first->depth > node->left->way.second->depth) {
                node->way.first = node->left->way.first;
                node->wayLength = node->left->way.first->depth - node->depth;
            } else {
                node->way.first = node->left->way.second;
                node->wayLength = node->left->way.second->depth - node->depth;
            }
        } else {
            maxWayFromBelow(node->left);
            maxWayFromBelow(node->right);
            Node *left = node->left->way.first->depth > node->left->way.second->depth ?
                         node->left->way.first : node->left->way.second;
            Node *right = node->right->way.first->depth > node->right->way.second->depth ?
                          node->right->way.first : node->right->way.second;
            node->way = {left, right};
            node->wayLength = left->depth - node->depth + right->depth - node->depth;
        }
    }

    void maxWayFromAbove(Node *node, int maxTopWay) {
        if (node) {
            Node *max = node->way.first->depth > node->way.second->depth ?
                        node->way.first : node->way.second;
            int maxLength = max->depth - node->depth + maxTopWay;
            if (maxLength > node->wayLength) {
                node->wayLength = maxLength;
            }

            int toSend = std::max(node->way.second->depth - node->depth, maxTopWay);
            maxWayFromAbove(node->left, toSend + 1);
            toSend = std::max(node->way.first->depth - node->depth, maxTopWay);
            maxWayFromAbove(node->right, toSend + 1);
        }
    }

    void findMax(Node *node, int k) {
        if (node) {
            if (node->wayLength < k && (!maxNode || node->value > maxNode->value))
                maxNode = node;
            findMax(node->left, k);
            findMax(node->right, k);
        }
    }

    bool deleteNode(int key) {
        Node *ptr = root, *prev = nullptr;
        bool isLeft = false;
        while (ptr) {
            if (ptr->value == key) {
                deleteNodeByPtr(ptr, prev, isLeft);
                return true;
            } else if (ptr->value > key) {
                prev = ptr;
                ptr = ptr->left;
                isLeft = true;
            } else {
                prev = ptr;
                ptr = ptr->right;
                isLeft = false;
            }
        }
        return false;
    }

    void deleteNodeByPtr(Node *ptr, Node *prev, bool isLeft) {
        if (ptr->right && ptr->left) {
            Node *min = ptr->right;
            prev = ptr;
            bool isLeft = false;
            while (min->left) {
                prev = min;
                min = min->left;
                isLeft = true;
            }
            int minValue = min->value;
            deleteNodeByPtr(min, prev, isLeft);
            ptr->value = minValue;
        } else {
            Node *newNode;
            if (ptr->left)
                newNode = ptr->left;
            else if (ptr->right)
                newNode = ptr->right;
            else
                newNode = nullptr;
            if (ptr == root) {
                root = newNode;
            } else {
                if (isLeft) {
                    prev->left = newNode;
                } else {
                    prev->right = newNode;
                }
            }
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    bool isEmpty() {
        return root == nullptr;
    }

    void add(int x) {
        Node *node = new Node;
        node->value = x;
        node->right = node->left = nullptr;
        int count = 0;
        if (!root) {
            root = node;
        } else {
            Node *cur = root;
            Node *prev = nullptr;
            while (cur) {
                prev = cur;
                if (cur->value > x) {
                    cur = cur->left;
                    if (!cur) {
                        prev->left = node;
                    }
                } else if (cur->value < x) {
                    cur = cur->right;
                    if (!cur) {
                        prev->right = node;
                    }
                } else {
                    return;
                }
                ++count;
            }
        }
        if (count > height) {
            height = count;
        }
        node->depth = count;
    }

    void preOrder() {
        preOrder(root);
    }

    void preOrder(Node *node) {
        if (node) {
            fout << node->value << '\n';
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void task(int k) {
        maxWayFromBelow(root);
        maxWayFromAbove(root->left, root->way.second->depth + 1);
        maxWayFromAbove(root->right, root->way.first->depth + 1);
        maxNode = nullptr;
        findMax(root, k);
        if (maxNode) {
            deleteNode(maxNode->value);
        }
        if (root) {
            preOrder();
        } else {
            fout << "No tree";
        }
    }

};

int main() {
    BinaryTree tree;
    int k, x;
    fin >> k;
    while (fin >> x) {
        tree.add(x);
    }
    if (!tree.isEmpty()) {
        tree.task(k);
    } else {
        fout << "No tree";
    }
    return 0;
}