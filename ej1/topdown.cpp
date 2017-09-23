#include "topdown.h"

void mostrarMatriz(MatrizCostoAcumulado &m) {
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            cout << "(" << m[i][j].valor << ", " << m[i][j].def << ") ";
        }
        cout << endl;
    }
}

TallerDeImpresiones::TallerDeImpresiones(int n, MatrizCosto &c) : cantTrabajos(n), costosFijos(c) {
    costosAcumulados = MatrizCostoAcumulado(n+1);
    for (int i = 0; i < n+1; ++i) {
        // Inicializa las filas de la matriz. Para cada 0 <= i <= n, crea un vector de i posiciones
        // que almacenará los costos óptimos cuando t_i es el último trabajo en una máquina y t_j es el
        // último en la otra, con 0 <= j < i.
        for (int j = 0; j < i; ++j) {
            CostoAcumulado costo(0,0);
            costosAcumulados[i].push_back(costo);
        }
    }

    cout << "Costos fijos: " << endl;

    for (int i = 0; i < n+1; ++i) {
        for (int j = 0; j < i; ++j) {
            cout << costosFijos[i][j] << " ";
        }
        cout << endl << endl;
    }
}

int TallerDeImpresiones::costoOptimo() {
    cout << "Calculando el costo optimo con " << cantTrabajos << " trabajos." << endl;
    if (cantTrabajos == 1) { return costosFijos[1][0]; }
    else {
        int minimo = costoOptimoAux(cantTrabajos, cantTrabajos-1);
        cout << "Minimo: " << minimo << endl;
        for (int k = 0; k < cantTrabajos-1; ++k) {
            int costoActual = costoOptimoAux(cantTrabajos, k);
            costosAcumulados[cantTrabajos][k] = CostoAcumulado(costoActual, 1);
            if (actual < minimo) { minimo = actual; }
        }
        return minimo; 
    }
}

int TallerDeImpresiones::costoOptimoAux(int i, int j) {
    assert(j >= 0 && i > j);

    cout << "i: " << i << ", j: " << j << endl;
    mostrarMatriz(costosAcumulados);

    if ( costosAcumulados[i][j].def ) { 
//        cout << "Caimos en el caso boludo con i = " << i << " y j = " << j << endl;
        return costosAcumulados[i][j].valor;
    }
    else {
        cout << "No caimos en el caso boludo" << endl;
        if (i == 1) {
            costosAcumulados[1][0] = CostoAcumulado(costosFijos[1][0], 1);
            mostrarMatriz(costosAcumulados);
            return costosFijos[1][0];
        } else {
            if (j < i-1) {
                int sumaCostos = 0;
                for (int l = j+2; l < i+1; ++j) {
                    sumaCostos += costosFijos[l][l-1];
                }
                cout << "sumaCostos: " << sumaCostos << endl;
                costosAcumulados[i][j] = CostoAcumulado(costoOptimoAux(j+1, j) + sumaCostos, 1);
                return costosAcumulados[i][j].valor;
            } else { // j = i-1
                int minimo = costosAcumulados[i-1][0].valor + costosFijos[i][0];
                for (int k = 1; k < i-1; ++k) {
                    int actual = costosAcumulados[i-1][k].valor + costosFijos[i][k];
                    if (actual < minimo) {
                        minimo = actual;
                    }
                }
                costosAcumulados[i][j] = CostoAcumulado(minimo, 1);
                return costosAcumulados[i][j].valor;
            }
        }
    }
}
