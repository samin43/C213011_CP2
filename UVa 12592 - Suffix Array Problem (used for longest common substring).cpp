#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;

int SA[MAXN], tempSA[MAXN];
int RA[MAXN], tempRA[MAXN];
int c[MAXN];
int Phi[MAXN], PLCP[MAXN], LCP[MAXN];
string T;
int n;

void countingSort(int k) {
    int i, sum, maxi = max(300, n);
    memset(c, 0, sizeof c);

    for (i = 0; i < n; ++i)
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; ++i) {
        int t = c[i]; c[i] = sum; sum += t;
    }
    for (i = 0; i < n; ++i)
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; ++i)
        SA[i] = tempSA[i];
}

void constructSA() {
    int i, k, r;
    for (i = 0; i < n; ++i) RA[i] = T[i], SA[i] = i;
    for (k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; ++i)
            tempRA[SA[i]] =
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k])
                    ? r : ++r;
        for (i = 0; i < n; ++i)
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1) break;
    }
}

void computeLCP() {
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; ++i)
        Phi[SA[i]] = SA[i - 1];

    for (i = L = 0; i < n; ++i) {
        if (Phi[i] == -1) { PLCP[i] = 0; continue; }
        while (T[i + L] == T[Phi[i] + L]) L++;
        PLCP[i] = L;
        L = max(L - 1, 0);
    }
    for (i = 0; i < n; ++i)
        LCP[i] = PLCP[SA[i]];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string A, B;
    while (getline(cin, A)) {
        getline(cin, B);
        T = A + '$' + B + '#';
        n = T.size();

        constructSA();
        computeLCP();

        int maxLCP = 0;
        int lenA = A.size();
        for (int i = 1; i < n; ++i) {
            bool cond1 = SA[i] < lenA;
            bool cond2 = SA[i - 1] < lenA;
            if (cond1 != cond2) {
                maxLCP = max(maxLCP, LCP[i]);
            }
        }
        cout << maxLCP << "\n";
    }
    return 0;
}
