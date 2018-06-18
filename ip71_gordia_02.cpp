#include <algorithm>
#include <iostream>

using namespace std;

int sz, pt1, pt2, len1, len2, ans, cnt;

int line_inverse(int *arr, int l1, int r1, int l2, int r2, int *temp) {
    len1 = r1 - l1 + 1;
    len2 = r2 - l2 + 1;
    sz = len1 + len2;

    pt1 = pt2 = ans = cnt = 0;
    for (int i = 0; i < sz; i++) {
        if (pt1 == len1) {
            temp[i] = arr[l2 + pt2++];
            cnt++;
        } else {
            if (pt2 == len2) {
                temp[i] = arr[l1 + pt1++];
                ans += cnt;
            } else {
                if (arr[l1 + pt1] < arr[l2 + pt2]) {
                    temp[i] = arr[l1 + pt1++];
                    ans += cnt;
                } else {
                    temp[i] = arr[l2 + pt2++];
                    cnt++;
                }
            }
        }
    }

    for (int i = l1; i <= r2; i++) arr[i] = temp[i - l1];

    return ans;
}

int inverse(int *arr, int ll, int rr, int *temp) {
    if (ll == rr) return 0;
    int md = (ll + rr) / 2;
    return inverse(arr, ll, md, temp) + inverse(arr, md + 1, rr, temp) + line_inverse(arr, ll, md, md + 1, rr, temp);
}

int main() {
    int n, m, x, y, sel_pos;
    cin>>x>>n>>m;
    vector< pair<int, int> > res;
    int **arr = new int*[n], *temp = new int[n], *id = new int[n];
    for (int i = 0; i < n; i++) arr[i] = new int[m];

    for (int i = 0; i < n; i++) {
        cin>>id[i];
        if (id[i] == x) sel_pos = i;
        for (int j = 0; j < m; j++)
            cin>>arr[i][j];
    }


    int *a;
    pair<int, int> p;

    for (int i = 0; i < n; i++)
        if (id[i] != x) {
            a = new int[m];
            for (int j = 0; j < m; j++)
                a[arr[sel_pos][j] - 1] = arr[i][j];
            p.first = inverse(a, 0, m - 1, temp);
            p.second = id[i];
            res.push_back(p);
        }
    sort(res.begin(), res.end());

    cout<<x<<endl;
    for (int i = 0; i < res.size(); i++)
        cout<<res[i].second<<" "<<res[i].first<<endl;
}
/*

6 10 5
1 5 2 1 3 4
2 3 2 4 1 5
3 4 5 3 2 1
4 5 1 4 3 2
5 1 2 5 4 3
6 2 5 4 1 3
7 2 4 5 3 1
8 5 3 1 4 2
9 4 5 2 3 1
10 3 1 2 4 5


 */
