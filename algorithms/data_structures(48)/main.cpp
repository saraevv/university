    #include <fstream>
#include <vector>
#include <numeric>
#include <random>
#include <ctime>

using namespace std;


class Treap {
    int key, priority, size;
    Treap *left, *right;
public:
    Treap(int key, int priority, Treap *left = nullptr, Treap *right = nullptr) :
            key(key), priority(priority), size(1), left(left), right(right) {};

    Treap(vector<int> &v, vector<int> &p) : Treap(v[0], p[0]) {
        for (unsigned i = 1; i < v.size(); ++i) {
            this->add(v[i], p[i], i);
        }
    }

    void calculateSize() {
        int l = 0, r = 0;
        if (this->left) {
            l += this->left->size;
        }
        if (this->right) {
            r += right->size;
        }
        this->size = l + r + 1;
    }

    void split(int pos, Treap *&l, Treap *&r) {
        Treap *t = nullptr;
        int leftSize = this->left ? this->left->size : 0;
        //if (this->key < val) {
        if (pos >= leftSize + 1) {
            if (!this->right) {
                r = nullptr;
            } else {
                this->right->split(pos - leftSize - 1, t, r);
            }
            l = new Treap(this->key, this->priority, this->left, t);
            l->calculateSize();
        } else {
            if (!this->left) {
                l = nullptr;
            } else {
                this->left->split(pos, l, t);
            }
            r = new Treap(this->key, this->priority, t, this->right);
            r->calculateSize();
        }
    }

    static Treap *merge(Treap *&l, Treap *&r) {
        Treap *ans;
        if (!l) {
            return r;
        } else if (!r) {
            return l;
        } else if (l->priority > r->priority) {
            ans = new Treap(l->key, l->priority, l->left, merge(l->right, r));
        } else {
            ans = new Treap(r->key, r->priority, merge(l, r->left), r->right);
        }
        ans->calculateSize();
        return ans;
    }

    void add(int key, int priority, int pos) {
        Treap *t = new Treap(key, priority), *l, *r;
        this->split(pos, l, r);
        t = merge(l, t);
        *this = *merge(t, r);
    }

    void replace(int x, int y) {
        Treap *t1, *t2, *t3, *t4;
        this->split(x - 1, t1, t2);
        t2->split(y - x + 1, t3, t4);
        t1 = merge(t3, t1);
        *this = *merge(t1, t4);
    }

    void order(ofstream &fout) {
        order(this, fout);
    }

    void order(Treap *t, ofstream &fout) {
        if (t->left) {
            order(t->left, fout);
        }
        fout << t->key << ' ';
        if (t->right) {
            order(t->right, fout);
        }
    }
};


int main() {
    ifstream fin("archive.in");
    ofstream fout("archive.out");

    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed(time(0));
    std::uniform_int_distribution<> dis(0, INT_MAX);

    int N, Q, x, y;
    fin >> N >> Q;
    vector<int> v(N);
    iota(v.begin(), v.end(), 1);
    vector<int> p(N);
    for (int i = 0; i < N; ++i) {
        p[i] = dis(gen);
    }

    vector<int> out;
    Treap treap(v, p);
    for (int i = 0; i < Q; ++i) {
        fin >> x >> y;
        treap.replace(x, y);
    }
    treap.order(fout);
    return 0;
}
