#include <fstream>
#include <stack>

std::ifstream fin("in.txt");
std::ofstream fout("out.txt");

struct Node;

struct Info {
    Node *leftNode = nullptr;
    Node *rightNode = nullptr;
};

struct Node {
    int value;
    int depth;
    Node *left;
    Node *right;
};

class BinaryTree {
private:
    Node *root;
    int height = -1;
    Node *left = nullptr, *right = nullptr;
    long long length = -1;

    void updateMaxWay(Node *leftNode, Node *rightNode, Node *rootNode) {
        long long currentLength = leftNode->depth - rootNode->depth + rightNode->depth - rootNode->depth;
        if (currentLength > length ||
            ((currentLength == length) && (leftNode->value + rightNode->value) < (left->value + right->value))) {
            left = leftNode;
            right = rightNode;
            length = currentLength;
        }
    }

    Info findFarthestNodes(Node *node) {
        if (!node->left && !node->right) {
            return {node, nullptr};
        } else if (!node->right) {
            Info leftInfo = findFarthestNodes(node->left);
            if (!leftInfo.rightNode) {
                updateMaxWay(leftInfo.leftNode, node, node);
                return {leftInfo.leftNode, node};
            } else {
                updateMaxWay(leftInfo.leftNode, node, node);
                updateMaxWay(leftInfo.rightNode, node, node);
                return leftInfo;
            }
        } else if (!node->left) {
            Info rightInfo = findFarthestNodes(node->right);
            if (!rightInfo.rightNode) {
                updateMaxWay(node, rightInfo.leftNode, node);
                return {node, rightInfo.leftNode};
            } else {
                updateMaxWay(node, rightInfo.leftNode, node);
                updateMaxWay(node, rightInfo.rightNode, node);
                return rightInfo;
            }
        } else {
            Info leftInfo = findFarthestNodes(node->left);
            Info rightInfo = findFarthestNodes(node->right);

            if (!leftInfo.rightNode && !rightInfo.rightNode) {
                updateMaxWay(leftInfo.leftNode, node, node);
                return {leftInfo.leftNode, node};
            } else if (!leftInfo.rightNode) {
                if ((rightInfo.leftNode->depth > leftInfo.leftNode->depth) &&
                    (rightInfo.rightNode->depth > leftInfo.leftNode->depth)) {
                    updateMaxWay(leftInfo.leftNode, rightInfo.leftNode, node);
                    updateMaxWay(leftInfo.leftNode, rightInfo.rightNode, node);
                    return rightInfo;
                } else if ((rightInfo.leftNode->depth > rightInfo.rightNode->depth) &&
                           (rightInfo.leftNode->depth != leftInfo.leftNode->depth)) {
                    updateMaxWay(leftInfo.leftNode, rightInfo.leftNode, node);
                    return {leftInfo.leftNode, rightInfo.leftNode};
                } else {
                    updateMaxWay(leftInfo.leftNode, rightInfo.rightNode, node);
                    return {leftInfo.leftNode, rightInfo.rightNode};
                }
            } else if (!rightInfo.rightNode) {
                if ((leftInfo.leftNode->depth >= rightInfo.leftNode->depth) &&
                    (leftInfo.rightNode->depth >= rightInfo.leftNode->depth)) {
                    updateMaxWay(leftInfo.leftNode, rightInfo.leftNode, node);
                    updateMaxWay(leftInfo.rightNode, rightInfo.leftNode, node);
                    return leftInfo;
                } else if ((leftInfo.leftNode->depth > leftInfo.rightNode->depth) &&
                           (leftInfo.leftNode->depth != rightInfo.leftNode->depth)) {
                    updateMaxWay(leftInfo.leftNode, rightInfo.leftNode, node);
                    return {leftInfo.leftNode, rightInfo.leftNode};
                } else {
                    updateMaxWay(leftInfo.rightNode, rightInfo.leftNode, node);
                    return {leftInfo.rightNode, rightInfo.leftNode};
                }
            } else {
                Node tm = {INT_MAX, -1, nullptr, nullptr};
                Node *maxLeft = &tm, *maxRight = &tm;
                long long maxLength = -1;

                Node *nodes[4] = {leftInfo.leftNode, leftInfo.rightNode, rightInfo.leftNode, rightInfo.rightNode};
                for (int i = 0; i < 2; ++i) {
                    for (int j = 2; j < 4; ++j) {
                        long long wayLength = 0;
                        wayLength = nodes[i]->depth - node->depth + nodes[j]->depth - node->depth;
                        long long sum1 = nodes[i]->value + nodes[j]->value;
                        long long sum2 = maxLeft->value + maxRight->value;
                        if ((nodes[i]->depth != nodes[j]->depth) &&
                            ((wayLength > maxLength) || ((wayLength == maxLength) && (sum1 < sum2)))) {
                            maxLeft = nodes[i];
                            maxRight = nodes[j];
                            maxLength = wayLength;
                        }
                    }
                }

                updateMaxWay(maxLeft, maxRight, node);
                maxLeft = &tm;
                maxRight = &tm;
                int firstMax = INT_MIN, secondMax = INT_MIN;
                for (int i = 0; i < 4; ++i) {
                    if (nodes[i]->depth > firstMax ||
                        ((nodes[i]->depth == firstMax) && (nodes[i]->value < maxLeft->value))) {
                        firstMax = nodes[i]->depth;
                        maxLeft = nodes[i];
                    }
                }
                for (int i = 0; i < 4; ++i) {
                    if ((nodes[i]->depth < firstMax) && ((nodes[i]->depth > secondMax) ||
                                                         ((nodes[i]->depth == secondMax) &&
                                                          (nodes[i]->value < maxRight->value)))) {
                        secondMax = nodes[i]->depth;
                        maxRight = nodes[i];
                    }
                }
                if (maxLeft->value > maxRight->value) {
                    std::swap(maxLeft, maxRight);
                }
                return {maxLeft, maxRight};
            }
        }
    }

    int lengthBetweenNodes(Node *start, Node *end) {
        Node *node = start;
        int count = 0;
        while (node && node != end) {
            ++count;
            if (node->value > end->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        if (node) {
            return count;
        } else {
            return -1;
        }
    }

    void raisingCenter() {
        if (length % 2 == 0) {
            Node *node = root;
            std::stack<Node *> previous;

            while (true) {
                if ((node->value < right->value && node->value > left->value) || node->value == left->value ||
                    node->value == right->value) {
                    break;
                } else {
                    previous.push(node);
                    if (node->value > left->value && node->value > right->value) {
                        node = node->left;
                    } else {
                        node = node->right;
                    }
                }
            }

            int leftLength = lengthBetweenNodes(node, left);
            int rightLength = lengthBetweenNodes(node, right);

            if (rightLength > leftLength) {
                while (rightLength != leftLength) {
                    previous.push(node);
                    --rightLength;
                    ++leftLength;
                    if (node->value > right->value) {
                        node = node->left;
                    } else {
                        node = node->right;
                    }
                }
            } else {
                while (rightLength != leftLength) {
                    previous.push(node);
                    ++rightLength;
                    --leftLength;
                    if (node->value > left->value) {
                        node = node->left;
                    } else {
                        node = node->right;
                    }
                }
            }

            while (!previous.empty()) {
                Node *prev = previous.top(), *t;
                previous.pop();
                std::swap(node->value, prev->value);
                if (node == prev->left) {
                    prev->left = node->left;
                    node->left = node->right;
                    node->right = prev->right;
                    prev->right = node;
                } else {
                    prev->right = node->right;
                    node->right = node->left;
                    node->left = prev->left;
                    prev->left = node;
                }
                node = prev;
            }
        }
    }

public:
    BinaryTree() : root(nullptr) {}

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

    void task() {
        left = right = nullptr;
        length = -1;
        findFarthestNodes(root);
        fout << left->value + right->value << '\n';
        raisingCenter();
        preOrder();
    }

};

int main() {
    BinaryTree tree;
    int x;
    while (fin >> x) {
        tree.add(x);
    }
    tree.task();
    return 0;
}