#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

const int N = 1000;

struct point {
    float x, y;
};

int n, a, b;
float x, y, d, **v;
vector< point > p, ans;
vector< pair<float, pair<int, int> > > ostov;
int *vertexCount;
bool *used;
int parent[N * N], rang[N * N];

template<typename T> inline T sqr(T t) { return t * t; }

inline float dist(point a, point b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

inline void removeVertex(int a, int b) {
    v[a][b] = v[b][a] = -1;
    vertexCount[a]--;
    vertexCount[b]--;
}

inline void addVertex(int a, int b) {
    v[a][b] = v[b][a] = dist(p[a], p[b]);
    vertexCount[a]++;
    vertexCount[b]++;
}

int find_unity(int x) {
    if (x == parent[x]) return x;
    return parent[x] = find_unity(parent[x]);
}

inline void marge_unity(int a, int b) {
    a = find_unity(a);
    b = find_unity(b);
    if (a != b) {
        if (rang[a] < rang[b]) swap(a, b);
        parent[b] = a;
        rang[a] += rang[b];
    } else {
        rang[a] = 1;
        parent[a] = a;
    }
}

void unionDfs(int pos, int par) {
    for (int i = 0; i < n; i++)
        if (v[pos][i] != -1 && parent[i] == i) {
            marge_unity(pos, i);
            unionDfs(i, par);
        }
}

inline void initDSU() {
    for (int i = 0; i < n; i++) parent[i] = i, rang[i] = 1;
    for (int i = 0; i < n; i++)
        if (parent[i] == i) unionDfs(i, i);
}

inline void buildOstov() {
    ostov.clear();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (vertexCount[i] < 2 && vertexCount[j] < 2) ostov.push_back({ dist(p[i], p[j]), { i, j }});
    sort(ostov.begin(), ostov.begin() + ostov.size());
    initDSU();
    for (int i = 0; i < ostov.size(); i++) {
        a = ostov[i].second.first;
        b = ostov[i].second.second;
        if (find_unity(a) != find_unity(b)) {
            marge_unity(a, b);
            addVertex(a, b);
        }
    }
}

void destructRec(int pos, int pred) {
    used[pos] = true;
    float mnDist = -1;
    int mnTo;
    for (int i = 0; i < n; i++)
        if (!used[i] && v[pos][i] != -1 && (mnDist == -1 || mnDist > v[pos][i])) {
            mnTo = i;
            mnDist = v[pos][i];
        }
    if (mnDist == -1) return;
    for (int i = 0; i < n; i++)
        if (i != mnTo && i != pred && v[pos][i] != -1) removeVertex(pos, i);
    destructRec(mnTo, pos);
}

inline void destruction() {
    for (int i = 0; i < n; i++) used[i] = false;
    for (int i = 0; i < n; i++)
        if (vertexCount[i] < 2 && !used[i]) destructRec(i, -1);
}

inline void show() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (v[i][j] != -1) cout<<j<<", ";
        cout<<endl;
    }
}

inline bool check() {
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (vertexCount[i] == 1) cnt++; else if (vertexCount[i] != 2) return true;
    return (cnt != 2);
}

inline void createAndDestruct() {
    used = new bool[n];
    vertexCount = new int[n];
    v = new float*[n];
    for (int i = 0; i < n; i++) v[i] = new float[n];

    for (int i = 0; i < n; i++) {
        vertexCount[i] = 0;
        for (int j = 0; j < n; j++) v[i][j] = -1;
    }

    while (check()) {
        buildOstov();
        destruction();
    }
}

inline void relax() {
    point a, b, e, d;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            b = ans[i];
            d = ans[j];
            if (i > 0 && j < n - 1) {
                a = ans[i - 1];
                e = ans[j + 1];
                if (dist(a, d) + dist(b, e) < dist(a, b) + dist(b, e)) swap(ans[i], ans[j]);
            } else if (i == 0 && j < n - 1) {
                e = ans[j + 1];
                if (dist(b, e) < dist(d, e)) swap(ans[i], ans[j]);
            } else if (i > 0 && j == n - 1) {
                a = ans[i - 1];
                if (dist(d, a) < dist(a, b)) swap(ans[i], ans[j]);
            }
        }
}

void buildRec(int pos) {
    used[pos] = true;
    ans.push_back(p[pos]);
    for (int i = 0; i < n; i++)
        if (v[pos][i] != -1 && !used[i]) return buildRec(i);
}

inline void buildPath() {
    for (int i = 0; i < n; i++) used[i] = false;
    for (int i = 0; i < n; i++)
        if (vertexCount[i] == 1) return buildRec(i);
}

int main() {
    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>x>>y;
        p.push_back({x, y});
    }

    createAndDestruct();

    buildPath();

    float answer1, answer2 = 0;
    for (int i = 1; i < n; i++) answer1 += dist(ans[i], ans[i - 1]);

    relax();
    for (int i = 1; i < n; i++) answer2 += dist(ans[i], ans[i - 1]);

    cout<<min(answer1, answer2);
}

/*


*/