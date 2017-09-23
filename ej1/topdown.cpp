// include utils
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <functional>
#include <numeric>
// include data structures
#include <deque>
#include <set>
#include <vector>

using namespace std;

struct CostoAcumulado {
    int valor;
    int def;
};

typedef vector< vector<int> > MatrizCosto;
typedef vector< vector<CostoAcumulado> > MatrizCostoAcumulado;

class TallerDeImpresiones {
public:
    int costoOptimo();
    TallerDeImpresiones(int n, MatrizCosto &c);

private:
    MatrizCosto costosFijos;
    MatrizCostoAcumulado costosAcumulados;
    int cantTrabajos;
    int costoOptimoAux(int i, int j);
};

TallerDeImpresiones::TallerDeImpresiones(int n, MatrizCosto &c) : cantTrabajos(n), costosFijos(c) {
    costosAcumulados = MatrizCostoAcumulado(n+1);
    for (int i = 0; i < n+1; ++i) {
        // Inicializa las filas de la matriz. Para cada 0 <= i <= n, crea un vector de i posiciones
        // que almacenará los costos óptimos cuando t_i es el último trabajo en una máquina y t_j es el
        // último en la otra, con 0 <= j < i.
        for (int j = 0, j < i, ++j) {
            CostoAcumulado costo { .valor = 0, .def = 0 };
            costosAcumulados[i][j] = costo;
        }
    }
}

int TallerDeImpresiones::costoOptimo() {
    return costoOptimoAux(cantTrabajos, cantTrabajos-1);
}

int TallerDeImpresiones::costoOptimoAux(int i, int j) {
    assert(j >= 0 && i > j);

    if ( costosAcumulados.[i][j].def ) { return costosAcumulados.[i][j].valor; }
    else {
        if (i == 1) {
            costosAcumulados.[1][0] = { .valor = costosFijos[1][0], .def = 1 };
            return costosFijos[1][0];
        } else {
            if (j < n-1) {
                int sumaCostos = 0;
                for (int l = j+2, l < i+1, ++j) { sumaCostos += costosFijos[l][l-1]; }
                costoOptimo[i][j] = { .valor = costoOptimoAux(j+1, j) + sumaCostos, .def = 1 };
                return costosAcumulados[i][j].valor;
            } else { // j = i+1
                int minimo = costosAcumulados[i-1][0].valor + costosFijos[i][0];
                for (int k = 1; k < i-1; ++k) {
                    int actual = costosAcumulados[i-1][k].valor + costosFijos[i][k];
                    if (actual < minimo) {
                        minimo = actual;
                    }
                }
                costosAcumulados[i][j] = minimo;
                return costosAcumulados[i][j].valor;
            }
        }
    }
}