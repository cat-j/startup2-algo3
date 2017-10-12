#include "topdown.h"
#include <chrono>


using namespace std::chrono;
int main() {
    int n;
    cin >> n;
    cerr << "Cantidad de trabajos;Tiempo de ejecucion"<< endl;
    while(n>0){
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

        high_resolution_clock::time_point beginSolution = high_resolution_clock::now();
        
            // cerr << "costo_minimo_bottom_up: " << resultado << endl;
        int res = taller.costoOptimo();
        stack<int> solucion = taller.dameSolucionOptima();

        high_resolution_clock::time_point endSolution = high_resolution_clock::now();

        duration<double> elapsedSecsFindingSol = duration_cast<duration<double>>(endSolution - beginSolution);

        cerr << n <<"; "<< elapsedSecsFindingSol.count() << endl;

        cout << res << " " << solucion.size();

        while (!solucion.empty()) {
            cout << " " << solucion.top();
            solucion.pop();
        }

        cout << endl;
        cin >> n;
    }
    return 0;
}
