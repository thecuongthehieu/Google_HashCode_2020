#include <bits/stdc++.h>

using namespace std;

#define inputFile "c_medium.in"

typedef long long ll;

ll m, n;
ll a[100005];

int main() {
    ifstream fin;
    fin.open(inputFile);
    fin >> m >> n;
    for (int i = 0; i < n; ++i) {
        fin >> a[n - 1 - i];
    }

    ll maxV = m;
    ll **dp;
    dp = new ll*[maxV + 1];
    for (ll i = 0; i <= maxV; ++i) {
        dp[i] = new ll[n + 1];
    }

    for (int j = 0; j <= n; ++j) {
        dp[0][j] = 0;
    }
    for (ll i = 0; i <= maxV; ++i) {
        dp[i][0] = 0;
    }

    for (ll i = 1; i <= maxV; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = dp[i][j - 1];
            if (i >= a[j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - a[j - 1]][j - 1] + a[j - 1]);
            }
        }
    }

    ll tmp = maxV;
    int j = n;
    int count = 0;
    queue<ll> ans;

    while (dp[tmp][j] != 0) {
        if (tmp >= a[j - 1]) {
            if (dp[tmp][j] == dp[tmp - a[j - 1]][j - 1] + a[j - 1]) {
                ans.push(n - j);
                tmp -= a[j - 1];
                count += 1;
            } 
        } 

        j -= 1;
    }

    cout << count << endl;
    while (!ans.empty()) {
        cout << ans.front() << " ";
        ans.pop();
    }
}