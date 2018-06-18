#include <iostream>

using namespace std;

int n, s, x, y, *dp1, *dp2, mx;

int main() {
    cin>>s>>n;
    dp1 = new int[s + 1];
    dp2 = new int[s + 1];

    for (int i = 0; i <= s; i++) dp1[i] = -INT_MAX;

    mx = 0;
    dp1[0] = 0;
    for (int i = 0; i < n; i++) {
        cin>>x>>y;
        mx += y;
        for (int j = 0; j <= min(mx, s); j++)
            if (j >= y) dp2[j] = max(dp1[j], dp1[j - y] + x); else dp2[j] = dp1[j];
        for (int j = 0; j <= s; j++) dp1[j] = dp2[j];
    }
    int mx = -INT_MAX;
    for (int i = 0; i <= s; i++)
        mx = max(mx, dp1[i]);
    cout<<mx;
}