#include "topdown.cpp"

int main() {
    int n;
    cin >> n;
    MatrizCosto data(n + 1);

    for (int i = 1; i < n + 1; ++i) {
        data[i] = vector<int>(i);
        for (int j = 0; j < i; ++j) {
            int dato;
            input >> dato;
            data[i][j] = dato;
        }
    }

    TallerDeImpresiones taller(n, data);

    int res = taller.costoOptimo();

    cout << res;

    return 0;
}