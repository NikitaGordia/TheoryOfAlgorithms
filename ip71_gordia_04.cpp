#include <iostream>
#include <vector>

using namespace std;

class heap {

private:

    static const int N = 10005, INF = 10000000;

    int h[N], size;
    bool is_max = true;

    void up(int pos) {
        if (pos == 0) return;
        int to = ((pos - 1) >> 1);
        if ((is_max && h[pos] > h[to]) || (!is_max && h[pos] < h[to])) {
            swap(h[pos], h[to]);
            up(to);
        }
    }

    void down(int pos) {
        int left = (pos << 1) + 1, rigth = left + 1, to = left;

        if (left >= size) return;
        if (rigth >= size) to = left; else {
            if ((is_max && h[rigth] > h[left]) || (!is_max && h[rigth] < h[left])) to = rigth;
        }
        if ((is_max && h[pos] < h[to]) || (!is_max && h[pos] > h[to])) {
            swap(h[pos], h[to]);
            down(to);
        }
    }

public:

    heap(bool max): is_max(max) {
        for (int i = 0; i < 10000; i++)
            if (is_max) h[i] = -INF; else h[i] = INF;
        size = 1;
    }

    void add(int x) {
        h[size++] = x;
        up(size - 1);
    }

    void pop() {
        if (is_max) h[0] = -INF; else h[0] = INF;
        swap(h[0], h[--size]);
        down(0);
    }

    string show() {
        string result = "[";
        for (int i = 0; i < size - 1; i++)
            result += to_string(h[i]) + ", ";
        return result + to_string(h[size - 1]) + "]";
    }

    int peek() {
        return h[0];
    }

    int get_size() {
        return size;
    }

};

int main() {

    int n, x;
    heap l(true), r(false);

    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>x;
        if (l.get_size() == r.get_size()) {
            if (x < r.peek()) l.add(x); else {
                l.add(r.peek());
                r.pop();
                r.add(x);
            }
            cout<<l.peek()<<endl;
        } else {
            if (x > l.peek()) r.add(x); else {
                r.add(l.peek());
                l.pop();
                l.add(x);
            }
            cout<<l.peek()<<" "<<r.peek()<<endl;
        }
    }
}