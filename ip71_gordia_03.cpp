#include <iostream>

using namespace std;

struct seg {
    int x, y, z, comp;
    seg(): comp(0) {};
};

int getMid(int x, int y, int z, int xx, int yy, int zz) {
    if ((x >= y && x <= z) || (x <= y && x >= z)) return xx;
    if ((y >= x && y <= z) || (y <= x && y >= z)) return yy;
    return zz;
}

int find_pos(int *arr, int l, int r, int val) {
    for (int i = l; i <= r; i++)
        if (arr[i] == val) return i;
}

pair<int, int> partLast(int *arr, int l, int r) {
    pair<int, int> res = make_pair(0, 0);
    int pos = l - 1;
    for (int i = l; i < r; i++) {
        if (arr[i] <= arr[r])
            swap(arr[i], arr[++pos]);
        res.second++;
    }
    swap(arr[r], arr[pos + 1]);
    res.first = pos + 1;
    return res;
};

pair<int, int> partMid(int *arr, int l, int r) {
    int mid = (l + r) >> 1;
    int pos = getMid(arr[l], arr[mid], arr[r], l, mid, r);
    swap(arr[pos], arr[r]);
    return partLast(arr, l, r);
};

seg partThree(int *arr, int l, int r) {
    seg ans;
    pair<int, int> res;
    int a = arr[l], b = arr[l + 1], c = arr[r];

    if (a > b) swap(a, b);
    if (b > c) swap(b, c);
    if (a > b) swap(a, b);

    swap(arr[find_pos(arr, l, r, a)], arr[r]);
    res = partLast(arr, l, r);
    ans.comp += res.second;
    ans.x = res.first;
    l = res.first + 1;

    swap(arr[find_pos(arr, l, r, b)], arr[r]);
     res = partLast(arr, l, r);
    ans.comp += res.second;
    ans.y = res.first;
    l = res.first + 1;

    swap(arr[find_pos(arr, l, r, c)], arr[r]);
    ans.comp += res.second;
    ans.z = res.first;

    return ans;
};

int sort1(int *arr, int l, int r) {
    if (l >= r) return 0;
    pair<int, int> res = partLast(arr, l, r);
    return res.second + sort1(arr, l, res.first - 1)
                      + sort1(arr, res.first + 1, r);
}

int sort2(int *arr, int l, int r) {
    if (l >= r) return 0;
    pair<int, int> res = partMid(arr, l, r);
    return res.second + sort2(arr, l, res.first - 1)
                      + sort2(arr, res.first + 1, r);
}

int sort3(int *arr, int l, int r) {
    if (l == r - 1) {
        if (arr[l] > arr[r]) swap(arr[l], arr[r]);
        return 1;
    } else if (l >= r) return 0;
    seg res = partThree(arr, l, r);
    return res.comp + sort3(arr, l, res.x - 1)
                    + sort3(arr, res.x + 1, res.y - 1)
                    + sort3(arr, res.y + 1, res.z - 1)
                    + sort3(arr, res.z + 1, r);
}

int main() {
    int *a = new int[10005], *b = new int[10005], *c = new int[10005], n;
    cin>>n;
    for (int i = 0; i < n; i++) {
        cin>>a[i];
        b[i] = c[i] = a[i];
    }
    cout<<sort1(a, 0, n - 1)<<" "<<sort2(b, 0, n - 1)<<" "<<sort3(c, 0, n - 1);
}
