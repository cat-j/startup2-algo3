#include "topdown.h"

int main() {
    int n;
    cin >> n;
    MatrizCosto data(n + 1);

//    cout << "Cantidad de trabajos: " << n << endl;

    for (int i = 1; i < n + 1; ++i) {
        data[i] = vector<int>(i);
        for (int j = 0; j < i; ++j) {
            int dato;
            cin >> dato;
            data[i][j] = dato;
        }
    }

    TallerDeImpresiones taller(n, data);

    int res = taller.costoOptimo();
    stack<int> solucion = taller.dameSolucionOptima();
    cout << res << " " << solucion.size();

    while (!solucion.empty()) {
        cout << " " << solucion.top();
        solucion.pop();
    }

    cout << endl;

    return 0;
}
