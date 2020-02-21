#include <bits/stdc++.h>

#define inputFile  "b_read_on.txt"

using namespace std;

int B, L, D; // num All Books, Libraries, Days
int S[100005]; // Score of B books

struct Lib {
    int ID, N, T, M; // num Books, Times to process, Max ship per day of a library

    int Nnorm, Tnorm, Mnorm;

    vector<pair<int, int> > Books; //Book ID of a library
    int key;
};

Lib lib[100005];

void inputData() {
    ifstream fin;
    fin.open(inputFile);
    fin >> B >> L >> D;
    for (int i = 0; i < B; ++i) {
        fin >> S[i];
    }
    for (int i = 0; i < L; ++i) {
        lib[i].ID = i;
        fin >> lib[i].N >> lib[i].T >> lib[i].M;
        for (int j = 0; j < lib[i].N; ++j) {
            int id;
            fin >> id;
            lib[i].Books.push_back(make_pair(S[id], id));
        }
    }
}

void normalizeData() {
    int minN = INT_MAX, minT = INT_MAX, minM = INT_MAX;
    int maxN =INT_MIN, maxT = INT_MIN, maxM = INT_MIN;

    for (int i = 0; i < L; ++i) {
        if (lib[i].N <= minN) minN = lib[i].N;
        if (lib[i].T <= minT) minT = lib[i].T;
        if (lib[i].M <= minM) minM = lib[i].M;

        if (lib[i].N >= maxN) maxN = lib[i].N;
        if (lib[i].T >= maxT) maxT = lib[i].T;
        if (lib[i].M >= maxM) maxM = lib[i].M;

    }

    for (int i = 0; i < L; ++i) {
        lib[i].Nnorm = 100 * float(lib[i].N - minN) / (maxN - minN);
        lib[i].Tnorm = 100 * float(lib[i].T - minT) / (maxT - minT);
        lib[i].Mnorm = 100 * float(lib[i].M - minM) / (maxM - minM);
        
        sort(lib[i].Books.begin(), lib[i].Books.end(), greater<pair<int, int> >());
    }
}

void computeGreedyKey() {
    for (int i = 0; i < L; ++i) {
        lib[i].key = round(0.3 * lib[i].Nnorm - 0.35 * lib[i].Tnorm + 0.3 * lib[i].Mnorm);
    }
}

bool compareLib(Lib lib1, Lib lib2) {
    return lib1.key > lib2.key;
}


int main() {
    inputData();
    normalizeData();
    computeGreedyKey();

    sort(lib, lib + L, compareLib);

    cout << L << endl;
    for (int i = 0; i < L; ++i) {
        cout << lib[i].ID << " " << lib[i].N << endl;
        for(int j = 0; j < lib[i].N; ++j) {
            cout << lib[i].Books[j].second << " ";
        }
        cout << endl;
    }
}