#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int KEY = 19, KEY_SECOND = 11, COLLISION_RESOLVE_TYPE = 1;

struct node {
    int val;
    node *nx;
};

int *mapNext;
int capacity, collision;
node **mapLink;

int ABS(int x) {
    if (x > 0) return x; else return x * -1;
}

int hashDiv(int x) {
    return ABS((int)x % capacity);
}

int hashMul(int x) {
    return (ABS(x) * KEY) % capacity;
}

int hashMulSecond(int x) {
    return (ABS(x) * KEY_SECOND) % capacity;
}

bool findByLink(int h, int x) {
    node *curr = mapLink[h];
    if (curr == nullptr) return false;
    while (curr->val != x) {
        if (curr->nx == nullptr) return false;
        curr = curr->nx;
    }
    return true;
}

void addByLink(int h, int x) {
    node *curr = mapLink[h];
    if (curr == nullptr) {
        node *nd = new node();
        nd->nx = nullptr;
        nd->val = x;
        mapLink[h] = nd;
        return;
    }
    collision++;
    while (curr->nx != nullptr) {
        curr = curr->nx;
        collision++;
    }

    node *nd = new node();
    nd->nx = nullptr;
    nd->val = x;

    curr->nx = nd;
}

bool findByNextLinear(int h, int x) {
    int pos = h, cnt = 0;
    while (mapNext[pos] != x) {
        if (cnt == capacity / 2) return false;
        cnt++;
        pos = (pos + 1) % capacity;
    }
    return true;
}

void addByNextLinear(int h, int x) {
    int pos = h, cnt = 0;
    while (mapNext[pos] != INT_MAX) {
        if (cnt == capacity / 2) return;
        cnt++;
        collision++;
        pos = (pos + 1) % capacity;
    }
    mapNext[pos] = x;
}

bool findByNextBinear(int h, int x) {
    int pos = h;
    int q = 0, cnt = 0;
    while (mapNext[pos] != x) {
        if (cnt == capacity / 2) return false;
        cnt++;
        pos = (pos + q * q) % capacity;
        q++;
    }
    return true;
}

void addByNextBinear(int h, int x) {
    int pos = h;
    int q = 0, cnt = 0;
    while (mapNext[pos] != INT_MAX) {
        if (cnt == capacity / 2) return;
        collision++;
        cnt++;
        pos = (pos + q * q) % capacity;
        q++;
    }
    mapNext[pos] = x;
}

bool findByNextDoubleHash(int h, int x) {
    int pos = h, cnt = 0, h2 = hashMulSecond(x);
    while (mapNext[pos] != x) {
        if (cnt == capacity / 2) return false;
        cnt++;
        pos = (pos + h2) % capacity;
    }
    return true;
}

void addByNextDoubleHash(int h, int x) {
    int pos = h, h2 = hashMulSecond(x), cnt = 0;
    while (mapNext[pos] != INT_MAX) {
        if (cnt == capacity / 2) return;
        collision++;
        cnt++;
        pos = (pos + h2) % capacity;
    }
    mapNext[pos] = x;
}


bool find(int x) {
    switch (COLLISION_RESOLVE_TYPE) {
        case 1: return findByLink(hashDiv(x), x);
        case 2: return findByLink(hashMul(x), x);
        case 3: return findByNextLinear(hashMul(x), x);
        case 4: return findByNextBinear(hashDiv(x), x);
        case 5: return findByNextDoubleHash(hashDiv(x), x);
    }
}

void add(int x) {
    switch (COLLISION_RESOLVE_TYPE) {
        case 1: return addByLink(hashDiv(x), x);
        case 2: return addByLink(hashMul(x), x);
        case 3: return addByNextLinear(hashDiv(x), x);
        case 4: return addByNextBinear(hashDiv(x), x);
        case 5: return addByNextDoubleHash(hashDiv(x), x);
    }
}

void init(int n) {
    capacity = n * 3;

    if (COLLISION_RESOLVE_TYPE >= 1 && COLLISION_RESOLVE_TYPE <= 2) {
        mapLink = new node*[capacity];
        for (int i = 0; i < capacity; i++) mapLink[i] = nullptr;
    } else {
        mapNext = new int[capacity];
        for (int i = 0; i < capacity; i++) mapNext[i] = INT_MAX;
    }
}

int main() {
    int n, m;
    vector<int> arr;

    cin>>n>>m;

    init(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin>>x;
        arr.push_back(x);
        add(x);
    }
    cout<<collision<<endl;
    for (int i = 0; i < m; i++) {
        int x, f = 0, s = 0;
        cin>>x;
        for (int j = 0; j < n; j++)
            if (find(x - arr[j])) {
                f = arr[j];
                s = (x - arr[j]);
                break;
            }
        cout<<f<<" "<<s<<endl;
    }
}
