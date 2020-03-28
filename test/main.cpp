#include <iostream>
#include <vector>

using namespace std;

class Treap {
    int val, priority;
    Treap *left, *right;
public:
    Treap(int val, int priority, Treap *left = nullptr, Treap *right = nullptr) :
            val(val), priority(priority), left(left), right(right) {};

    void split(int val, Treap *l, Treap *r) {
        Treap *tl, *tr;
        if (this->val < val) {
            l->left = this->left;
            if (!this->right) {
                r = nullptr;
            } else {
                this->right->split(val, tl, r);
            }
            l->right = tl;
        } else {
            r->right = this->right;
            if (!this->left) {
                l = nullptr;
            } else {
                this->left->split(val, tl, l);
            }
            r->left = tr;
        }
    }

    static void merge(Treap *l, Treap *r, Treap *ans) {
        if (l == nullptr) {
            ans = r;
        } else if (r == nullptr) {
            ans = l;
        } else if (l->priority > r->priority) {
            ans = l;
            merge(l->right, r, ans->right);
        } else {
            ans = r;
            merge(l, r->left, ans->left);
        }
    }

    void add(int val, int priority) {
        Treap *l, *r;
        this->split(val, l, r);
        Treap *tm = new Treap(val,priority);
        merge(l, tm, tm);
        merge(tm, r, tm);
        *this = *tm;
    }

};


int main() {
    int N, x, y;
    cin >> N >> x >> y;
    Treap treap(x, y);
    for (int i = 0; i < N - 1; ++i) {
        cin >> x >> y;
        treap.add(x, y);
    }
    return 0;
}
