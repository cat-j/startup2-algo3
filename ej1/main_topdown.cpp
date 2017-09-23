#include "topdown.h"

int main() {
    int n;
    cin >> n;
    MatrizCosto data(n + 1);

    cout << "Cantidad de trabajos: " << n << endl;

    for (int i = 1; i < n + 1; ++i) {
        data[i] = vector<int>(i);
        for (int j = 0; j < i; ++j) {
            int dato;
            cin >> dato;
            data[i][j] = dato;
        }
    }

    TallerDeImpresiones taller(n, data);
    cout << "No segfaultea cuando declara el taller" << endl;

    int res = taller.costoOptimo();
    cout << "No segfaultea cuando calcula el costo optimo" << endl;

    cout << res << endl;

    return 0;
}
