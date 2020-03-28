#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

struct Triple {
    int first;
    int second;
    int third;
};

class Treap {
    int second, third, priority, min;
    Treap *left, *right;
public:
    Treap(int second, int third, int priority, Treap *left = nullptr, Treap *right = nullptr) :
            second(second), third(third), priority(priority), min(third), left(left), right(right) {};

    void updateMin() {
        int l = INT_MAX, r = INT_MAX;
        if (this->left) {
            l = this->left->min;
        }
        if (this->right) {
            r = this->right->min;
        }
        min = std::min({l, r, this->third});
    }

    void split(int val, Treap *&l, Treap *&r) {
        Treap *t = nullptr;
        if (this->second < val) {
            if (!this->right) {
                r = nullptr;
            } else {
                this->right->split(val, t, r);
            }
            //l = new Treap(this->second, this->third, this->priority, this->left, t);
            l = this;
            l->right = t;
            l->updateMin();
        } else {
            if (!this->left) {
                l = nullptr;
            } else {
                this->left->split(val, l, t);
            }
            //r = new Treap(this->second, this->third, this->priority, t, this->right);
            r = this;
            r->left = t;
            r->updateMin();
        }
    }

    static Treap *merge(Treap *&l, Treap *&r) {
        //Treap *ans = nullptr;
        if (!l) {
            return r;
        } else if (!r) {
            return l;
        } else if (l->priority > r->priority) {
            //ans = new Treap(l->second, l->third, l->priority, l->left, merge(l->right, r));
            l->right = merge(l->right, r);
            l->updateMin();
            return l;
        } else {
            //ans = new Treap(r->second, r->third, r->priority, merge(l, r->left), r->right);
            r->left = merge(l, r->left);
            r->updateMin();
            return r;
        }
        //ans->updateMin();
        //return ans;
    }

    Treap* add(int second, int third, int priority) {
        Treap *t = new Treap(second, third, priority), *l, *r;
        this->split(second, l, r);
//        t = merge(l, t);
//        t = merge(t, r);
//        *this = *t;
        //*this = *merge(t, r);
        t = merge(l,t);
        return merge(t,r);
    }

    Treap &operator=(const Treap &t) {
        this->second = t.second;
        this->third = t.third;
        this->min = t.min;
        this->left = t.left;
        this->right = t.right;
        return *this;
    }

    int getMin() {
        return this->min;
    }
};

//struct Node {
//    int second, third, priority, min;
//    Node *left, *right;
//
//    Node(int second, int third, int priority, Node *left = nullptr, Node *right = nullptr) :
//            second(second), third(third), priority(priority), min(third), left(left), right(right) {};
//
//    void updateMin() {
//        int l = INT_MAX, r = INT_MAX;
//        if (this->left) {
//            l = this->left->min;
//        }
//        if (this->right) {
//            r = this->right->min;
//        }
//        this->min = std::min({l, r, this->third});
//    }
//
//    int getMin() {
//        return this->min;
//    }
//};

//class Treap {
//    Node *root;
//public:
//    Treap() : root(nullptr) {};
//
//    static Node *merge(Node *l, Node *r) {
//        if (!l) {
//            return r;
//        } else if (!r) {
//            return l;
//        } else if (l->priority > r->priority) {
//            l->right = merge(l->right, r);
//            l->updateMin();
//            return l;
//        } else {
//            r->left = merge(l, r->left);
//            r->updateMin();
//            return r;
//        }
//    }
//
//    void split(int val, Node *&l, Node *&r) {
//        split(this->root, val, l, r);
//    }
//
//    void split(Node *&root, int val, Node *&l, Node *&r) {
//        if (!root) {
//            l = nullptr;
//            r = nullptr;
//        } else if (root->second < val) {
//            split(root->right, val, root->right, l);
//            l = root;
//            if (l) {
//                l->updateMin();
//            }
//        } else {
//            split(root->left, val, l, root->left);
//            r = root;
//            if (r) {
//                r->updateMin();
//            }
//        }
//    }
//
//    void add(int second, int third, int priority) {
//        if (!root) {
//            root = new Node(second, third, priority);
//        } else {
//            Node *l, *r, *t = new Node(second, third, priority);
//            split(root, second, l, r);
//            l = merge(l, t);
//            root = merge(l, r);
//        }
//    }
//
//
//
//};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed(time(0));
    std::uniform_int_distribution<> dis(0, INT_MAX);

    int N, x, y, z;
    fin >> N;
    vector<Triple> v(N);

    for (int i = 0; i < N; ++i) {
        fin >> x >> y >> z;
        v[i] = {x, y, z};
    }

    sort(v.begin(), v.end(), [](Triple t1, Triple t2) {
        return t1.first < t2.first;
    });

    int count = 1;

    Treap *treap = new Treap(v[0].second, v[0].third, dis(gen));
    for (unsigned i = 1; i < v.size(); ++i) {
        Treap *l, *r;
        //treap.split(v[i].second, l, r);
        treap->split(v[i].second, l, r);
        if (l == nullptr || l->getMin() > v[i].third) {
            ++count;
        }
        treap = Treap::merge(l, r);
        treap = treap->add(v[i].second, v[i].third, dis(gen));
    }
    fout << count;
    return 0;
}